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

	m_Position.y = 15.0f;
}

void GolfBall::Update()
{
	// ���[���h�s�񂩂�O���x�N�g�����擾�����
	// �I�u�W�F�N�g�̕ϊ����i�X�P�[�����O�A��]�A���s�ړ��Ȃǁj�����ƂɃ��[���h�s��𐶐�
	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMStoreFloat4x4(&worldMatrix, DirectX::XMMatrixIdentity()); // ��̏�������
	DirectX::SimpleMath::Vector3 forward = DirectX::XMVectorSet(worldMatrix._31, worldMatrix._32, worldMatrix._33, 0.0f);
	//lookDirection = m_Position * DirectX::SimpleMath::Vector3{ 1.0f,0.0f,1.0f };
	lookDirection = m_Position * forward;



	if (m_State != 0) return;	//�Î~��ԂȂ�return
	Vector3 oldPos = m_Position;

	//���x��0�ɋ߂��ƒ�~������
	if (m_Velocity.LengthSquared() < 0.03f) {
		m_StopCount++;

		if (Input::GetKeyTrigger(VK_A)) {
			m_Velocity.x -= 0.5f;
			m_Velocity.y += 2.0f;
		}
		if (Input::GetKeyTrigger(VK_D)) {
			m_Velocity.x += 0.5f;
			m_Velocity.y += 2.0f;
		}
		if (Input::GetKeyTrigger(VK_W)) {
			m_Velocity.z += 0.5f;
			m_Velocity.y += 2.0f;
		}
		if (Input::GetKeyTrigger(VK_S)) {
			m_Velocity.z -= 0.5f;
			m_Velocity.y += 2.0f;
		}
	}
	else {
		m_StopCount = 0;
		//�����x(1�t���[��������̌�����)
		float decelerationPower = 0.003f;

		Vector3 deceleration = -m_Velocity;	//���x�̋t�x�N�g�����v�Z
		deceleration.Normalize();
		m_Acceralation = deceleration * decelerationPower;

		//�����x�𑬓x�ɉ��Z
		m_Velocity += m_Acceralation;
		m_Rotation.z += 0.1f;
	}

	// 10�t���[���A���łقƂ�Ǔ����Ă��Ȃ���ΐÎ~��Ԃ�
	if (m_StopCount > 10) {
		m_Velocity = Vector3(0.0f, 0.0f, 0.0f);
		m_State = 1; //�Î~���
	}

	//�d��
	const float gravity = 0.05f;
	m_Velocity.y -= gravity;

	//���x�����W�ɉ��Z
	m_Position += m_Velocity;

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

DirectX::SimpleMath::Vector3 GolfBall::GetlookDirection() {
	return lookDirection;
}