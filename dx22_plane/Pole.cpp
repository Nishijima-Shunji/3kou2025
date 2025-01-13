//#include <memory>
#include "Pole.h"
#include "StaticMesh.h"
#include "utility.h"
#include "Game.h"
#include "Ground.h"
#include "Collision.h"

using namespace std;
using namespace DirectX::SimpleMath;

// �R���X�g���N�^
Pole::Pole(Camera* cam) : Object(cam)
{

}

// �f�X�g���N�^
Pole::~Pole()
{

}

//=======================================
// ����������
//=======================================
void Pole::Init()
{
	// ���b�V���ǂݍ���
	StaticMesh staticmesh;

	// 3D���f���f�[�^
	std::u8string modelFile = u8"assets/model/golf_pole/golf_pole_NO_HOLE.obj";

	// �e�N�X�`���f�B���N�g��
	std::string texDirectory = "assets/model/golf_pole";

	// Mesh��ǂݍ���
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
	vector<MATERIAL> materials = staticmesh.GetMaterials();

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

	// ���f���ɂ���ăX�P�[���𒲐�
	m_Scale.x = 3;
	m_Scale.y = 3;
	m_Scale.z = 3;
}

//=======================================
// �X�V����
//=======================================
void Pole::Update()
{

}

//=======================================
// �`�揈��
//=======================================
void Pole::Draw()
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

	// �J�����̐ݒ���w��
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
			m_subsets[i].IndexNum, // �`�悷��C���f�b�N�X��
			m_subsets[i].IndexBase, // �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu	
			m_subsets[i].VertexBase); // ���_�o�b�t�@�̍ŏ�����g�p
	}
}

//=======================================
// �I������
//=======================================
void Pole::Uninit()
{

}


//�ʒu�̐ݒ�
void Pole::SetPosition(float x, float y, float z)
{
	Vector3 p = { x, y, z };
	SetPosition(p);
}
void Pole::SetPosition(Vector3 pos)
{
	m_Position = pos;

	// Y���W��n�`�ɍ��킹�ĕύX

	// Ground�̒��_�f�[�^���擾
	vector<Ground*> grounds = Game::GetInstance()->GetObjects<Ground>();
	vector<VERTEX_3D> vertices;
	for (auto& g : grounds) // Ground�I�u�W�F�N�g�̐����[�v
	{
		vector<VERTEX_3D> vecs = g->GetVertices();
		for (auto& v : vecs) // ���_�̐����[�v
		{
			vertices.emplace_back(v);
		}
	}

	// �����ƃ|���S���̓����蔻��
	for (int i = 0; i < vertices.size(); i += 3)
	{
		// �O�p�`�|���S��
		Collision::Polygon collisionPolygon = {
			vertices[i + 0].position,
			vertices[i + 1].position,
			vertices[i + 2].position };

		Vector3 cp; // �ڐG�_

		Collision::Line line = { m_Position , Vector3(0,1,0) };
		if (Collision::CheckHit(line, collisionPolygon, cp))
		{
			m_Position.y = cp.y; // �ڐG�_�̂�����Ƃ������Pole��Y���W�Ƃ���
		}


	}
}

int Pole::Getnum() {
	return m_num;
}

void Pole::Setnum(int num) {
	m_num = num;
}
