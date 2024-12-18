#include <memory>
#include "GolfBall.h"
#include "StaticMesh.h"
#include "utility.h"
#include "Collision.h"
#include "Game.h"
#include "Ground.h"
#include "Pole.h"

using namespace DirectX::SimpleMath;
using namespace std;

//�R���X�g���N�^
GolfBall::GolfBall(Camera* cam) : Object(cam) {

}

//�f�X�g���N�^
GolfBall::~GolfBall() {

}

void GolfBall::Init()
{
	// ���b�V���ǂݍ���
	StaticMesh staticmesh;

	//3D���f���f�[�^
	std::u8string modelFile = u8"assets/model/golfball2/golf_ball.obj";

	//�e�N�X�`���f�B���N�g��
	std::string texDirectory = "assets/model/";

	//Mesh��ǂݍ���
	std::string tmpStr1(reinterpret_cast<const char*>(modelFile.c_str()), modelFile.size());
	staticmesh.Load(tmpStr1, texDirectory);

	m_MeshRenderer.Init(staticmesh);

	// �V�F�[�_�I�u�W�F�N�g����
	m_Shader.Create("shader/litTextureVS.hlsl", "shader/litTexturePS.hlsl");

	// �T�u�Z�b�g���擾
	m_subsets = staticmesh.GetSubsets();

	// �e�N�X�`�����擾
	m_Textures = staticmesh.GetTextures();

	// �}�e���A�����擾	
	std::vector<MATERIAL> materials = staticmesh.GetMaterials();

	// �}�e���A���������[�v
	for (int i = 0; i < materials.size(); i++)
	{
		// �}�e���A���I�u�W�F�N�g����
		std::unique_ptr<Material> m = std::make_unique<Material>();

		// �}�e���A�������Z�b�g
		m->Create(materials[i]);

		// �}�e���A���I�u�W�F�N�g��z��ɒǉ�
		m_Materiales.push_back(std::move(m));
	}

	//���f���ɂ���ăX�P�[���𒲐�
	m_Scale.x = 0.5;
	m_Scale.y = 0.5;
	m_Scale.z = 0.5;

	m_Position.y = 3.0f;
}

void GolfBall::Update()
{
	Move();

	if (m_State != 0) return;	//�Î~��ԂȂ�return
	Vector3 oldPos = m_Position;

	// 10�t���[���A���łقƂ�Ǔ����Ă��Ȃ���ΐÎ~��Ԃ�
	if (m_StopCount > 10) {
		m_Velocity = Vector3(0.0f, 0.0f, 0.0f);
		m_State = 1; //�Î~���
	}
	float radius = 0.5f;	//�{�[���̒��a

	//Ground�̒��_�f�[�^���擾
	vector<Ground*>grounds = Game::GetInstance()->GetObjects<Ground>();
	vector<VERTEX_3D> vertices;
	for (auto& g : grounds) {
		vector<VERTEX_3D> vecs = g->GetVertices();
		for (auto& v : vecs) {
			vertices.emplace_back(v);
		}
	}

	float moveDistance = 9999;	//�ړ�����
	Vector3 contactPoint;		//�ڐG�_
	Vector3 normal;

	//�����ƃ|���S���̓����蔻��
	bool senbunFg = false;
	for (int i = 0; i < vertices.size(); i += 3) {
		//�O�p�`�|���S��
		Collision::Polygon CollisionPolygon = {
			vertices[i + 0].position,
			vertices[i + 1].position,
			vertices[i + 2].position
		};
		Vector3 cp;	//�ڐG�_
		Collision::Segment collisionSegment = { oldPos, m_Position };
		if (Collision::CheckHit(collisionSegment, CollisionPolygon, cp)) {
			float md = 0;
			Vector3 np = Collision::moveSphere(collisionSegment, radius, CollisionPolygon, cp, md);
			if (moveDistance > md) {
				moveDistance = md;
				m_Position = np;
				contactPoint = cp;
				normal = Collision::GetNormal(CollisionPolygon);
			}
			senbunFg = true;
		}
	}

	//���̂ƃ|���S���̓����蔻��
	if (!senbunFg) {
		for (int i = 0; i < vertices.size(); i += 3) {
			//�O�p�`�|���S��
			Collision::Polygon CollisionPolygon = {
				vertices[i + 0].position,
				vertices[i + 1].position,
				vertices[i + 2].position
			};
			Vector3 cp;	//�ڐG�_
			Collision::Sphere collisionSphere = { m_Position,radius };
			if (Collision::CheckHit(collisionSphere, CollisionPolygon, cp)) {
				float md = 0;
				Vector3 np = Collision::moveSphere(collisionSphere, CollisionPolygon, cp);
				md = (np - oldPos).Length();
				if (moveDistance > md) {
					moveDistance = md;
					m_Position = np;
					contactPoint = cp;
					normal = Collision::GetNormal(CollisionPolygon);
				}
			}
		}
	}
	if (moveDistance != 9999) {	//�����������Ă�����	
		m_Velocity.y = -gravity;
		//std::cout << "Hit" << std::endl;

		//�{�[���̑��x�x�N�g���̖@�����������𕪉�
		float velocityNormal = Collision::Dot(m_Velocity, normal);
		Vector3 v1 = velocityNormal * normal;	//�@����������
		Vector3 v2 = m_Velocity - v1;	//�ڐ���������

		//�����W��
		const float restitution = 0.55f;

		//���˃x�N�g�����v�Z
		Vector3 reflectedVelocity = v2 - restitution * v1;

		//�{�[���̑��x���X�V
		m_Velocity = reflectedVelocity;
	}

	//���ɗ������烊�X�|�[��
	if (m_Position.y < -100) {
		m_Position = Vector3(0.0f, 50.0f, 0.0f);
		m_Velocity = Vector3(0.0f, 0.0f, 0.0f);
	}

	//Pole�̈ʒu���擾
	vector<Pole*> pole = Game::GetInstance()->GetObjects<Pole>();
	if (pole.size() > 0) {
		Vector3 polePos = pole[0]->GetPosition();

		Collision::Sphere balCollision = { m_Position, radius };
		Collision::Sphere poleCollision = { polePos, 0.5f };

		if (Collision::CheckHit(balCollision, poleCollision)) {
			m_State = 2;	//�J�b�v�C��
		}
	}
}

void GolfBall::Draw()
{
	// SRT���쐬
	Matrix r = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	Matrix t = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	Matrix s = Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);

	Matrix worldmtx;
	worldmtx = s * r * t;
	Renderer::SetWorldMatrix(&worldmtx); // GPU�ɃZ�b�g

	m_Shader.SetGPU();

	// �C���f�b�N�X�o�b�t�@�E���_�o�b�t�@���Z�b�g
	m_MeshRenderer.BeforeDraw();

	//�J�����̐ݒ���w��
	m_Camera->SetCamera(0);

	//�}�e���A���������[�v 
	for (int i = 0; i < m_subsets.size(); i++)
	{
		// �}�e���A�����Z�b�g(�T�u�Z�b�g���̒��ɂ���}�e���A���C���f�b�N�X���g�p)
		m_Materiales[m_subsets[i].MaterialIdx]->SetGPU();

		if (m_Materiales[m_subsets[i].MaterialIdx]->isTextureEnable())
		{
			m_Textures[m_subsets[i].MaterialIdx]->SetGPU();
		}

		m_MeshRenderer.DrawSubset(
			m_subsets[i].IndexNum,		// �`�悷��C���f�b�N�X��
			m_subsets[i].IndexBase,		// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu	
			m_subsets[i].VertexBase);	// ���_�o�b�t�@�̍ŏ�����g�p
	}
}

void GolfBall::Uninit()
{

}

//��Ԃ̐ݒ�E�擾
void GolfBall::SetState(int s) {
	m_State = s;
}

int GolfBall::GetState() {
	return m_State;
}

//�V���b�g
void GolfBall::Shot(Vector3 v) {
	m_Velocity = v;
}

DirectX::SimpleMath::Vector3 GolfBall::Getforward() {
	return forward;
}

void GolfBall::Move() {
	// �L�����ړ�
	// �O���x�N�g�����v�Z
	forward = DirectX::SimpleMath::Vector3(worldMatrix._31, worldMatrix._32, worldMatrix._33);
	forward.Normalize(); // ���K��
	Vector3 right = forward.Cross(Vector3::Up); // �E�����x�N�g��
	right.Normalize();

	// �{�[���̃X�P�[�����O�A��]�A���s�ړ���g�ݍ��킹�ă��[���h�s����쐬
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);

	DirectX::XMMATRIX worldMatrixXM = scale * rotation * translation;
	DirectX::XMStoreFloat4x4(&worldMatrix, worldMatrixXM);

	bool isKey = false;

	if (Input::GetKeyPress(VK_LEFT)) {
		m_Rotation.y -= 0.03f;
	}
	if (Input::GetKeyPress(VK_RIGHT)) {
		m_Rotation.y += 0.03f;
	}

	// ����
	if (Input::GetKeyPress(VK_SHIFT)) {
		speed = basicSpeed * 1.3f;
		maxSpeed = basicMaxSpeed * 2;
	}
	else {
		// ���x�ƍő呬�x����{�ɖ߂�
		speed = basicSpeed;
		maxSpeed = basicMaxSpeed;
	}

	// �ړ�
	if (Input::GetKeyPress(VK_A)) {
		m_Velocity += right * speed;
		isKey = true;
	}
	if (Input::GetKeyPress(VK_D)) {
		m_Velocity -= right * speed;
		isKey = true;
	}
	if (Input::GetKeyPress(VK_W)) {
		m_Velocity += forward * speed;
		isKey = true;
	}
	if (Input::GetKeyPress(VK_S)) {
		m_Velocity -= forward * speed;
		isKey = true;
	}

	// �ő呬�x�𒴂��Ȃ��悤�ɐ���
	float currentSpeed = sqrtf(m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y + m_Velocity.z * m_Velocity.z);
	if (currentSpeed > maxSpeed) {
		float scale = maxSpeed / currentSpeed;
		m_Velocity.x *= scale;
		m_Velocity.y *= scale;
		m_Velocity.z *= scale;
	}

	// �L�[���͂������ꍇ�̌�������
	if (!isKey) {
		float decay = exp(-deceleration);
		m_Velocity.x *= decay;
		m_Velocity.y *= decay;
		m_Velocity.z *= decay;
	}

	// �d��
	m_Velocity.y -= gravity;

	// ���x�����W�ɉ��Z
	m_Position += m_Velocity;
}