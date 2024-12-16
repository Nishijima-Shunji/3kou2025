#pragma once
#include "Object.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "Material.h"

//-----------------------------------------------------------------------------
// Pole�N���X
//-----------------------------------------------------------------------------
class Pole :public Object
{
private:

	// �`��ׂ̈̏��i���b�V���Ɋւ����j
	MeshRenderer m_MeshRenderer; // ���_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�E�C���f�b�N�X��

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	std::vector<std::unique_ptr<Material>> m_Materiales;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // �e�N�X�`��

	int m_State = 0; // 0:��\���E1:�����I���E2:�p���[�I��

public:

	Pole(Camera* cam); // �R���X�g���N�^
	~Pole(); // �f�X�g���N�^

	void Init();
	void Update();
	void Draw();
	void Uninit();

	// �ʒu�̐ݒ�
	void SetPosition(float x, float y, float z);
	void SetPosition(DirectX::SimpleMath::Vector3 pos);
};

