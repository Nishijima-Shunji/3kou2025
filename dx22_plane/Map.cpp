#include	<SimpleMath.h>
#include	<memory>
#include	"Map.h"
#include	"MeshRenderer.h"
#include	"Shader.h"
#include	"Texture.h"
#include	"StaticMesh.h"
#include	"utility.h"
#include    "Game.h"


using namespace DirectX::SimpleMath;

Map::Map(Camera* cam) :Object(cam) {
	Init();
}

Map::~Map() {

}

void Map::Init()
{
	// ���b�V���ǂݍ���
	StaticMesh staticmesh;

	//3D���f���f�[�^
	std::u8string modelFile = u8"assets/model/map/map.obj";
		
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

	//�}�e���A�����擾
	std::vector<MATERIAL> materials = staticmesh.GetMaterials();
	m_Vertices = staticmesh.GetVertices();

	//�}�e���A���������[�v
	for (int i = 0; i < materials.size(); i++) {
		//�}�e���A���I�u�W�F�N�g����
		std::unique_ptr<Material> m = std::make_unique<Material>();

		//�}�e���A�������Z�b�g
		m->Create(materials[i]);

		//�}�e���A���I�u�W�F�N�g��z��ɒǉ�
		m_Materiales.push_back(std::move(m));
	}

	//���_����ϊ����Ă���
	Matrix r = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	Matrix t = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	Matrix s = Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);
	Matrix worldmtx = s * r * t;
	for (int i = 0; i < m_Vertices.size(); i++) {
		m_Vertices[i].position = Vector3::Transform(m_Vertices[i].position, worldmtx);
		m_Vertices[i].normal = Vector3::Transform(m_Vertices[i].normal, worldmtx);
	}
}
void Map::Update()
{
	//m_Rotation.x = 7.85f;
	//std::cout << m_Rotation.x << std::endl;
	m_Scale.x = 0.01f;
	m_Scale.y = 0.01f;
	m_Scale.z = 0.01f;
}


void Map::Draw()
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

	//�}�e���A���������[�v 
	for (int i = 0; i < m_subsets.size(); i++)
	{
		//�}�e���A�����Z�b�g(�T�u�Z�b�g���̒��ɂ���}�e���A���C���f�b�N�X���g�p)
		m_Materiales[m_subsets[i].MaterialIdx]->SetGPU();

		if (m_Materiales[m_subsets[i].MaterialIdx]->isTextureEnable()) {
			m_Textures[m_subsets[i].MaterialIdx]->SetGPU();
		}


		m_MeshRenderer.DrawSubset(
			m_subsets[i].IndexNum,    // �`�悷��C���f�b�N�X��
			m_subsets[i].IndexBase,   // �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
			m_subsets[i].VertexBase); // ���_�o�b�t�@�̍ŏ�����g�p
	}
}

void Map::Uninit()
{

}

std::vector<VERTEX_3D> Map::GetVertices() {
	return m_Vertices;
}