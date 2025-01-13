#pragma once
#include "Object.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "Material.h"

//-----------------------------------------------------------------------------
// Pole�N���X
//-----------------------------------------------------------------------------
class Num :public Object
{
private:

	// �`��ׂ̈̏��i���b�V���Ɋւ����j
	MeshRenderer m_MeshRenderer; // ���_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�E�C���f�b�N�X��

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	std::vector<std::unique_ptr<Material>> m_Materiales;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // �e�N�X�`��

	DirectX::XMFLOAT4X4 worldMatrix; // ���[���h�s��̕ۑ��p�ϐ�
	DirectX::SimpleMath::Vector3 forward;	// �O���x�N�g���̊i�[
	int m_State = 0; // 0:��\���E1:�����I���E2:�p���[�I��
	int m_num = 0;

public:

	Num(Camera* cam); // �R���X�g���N�^
	~Num(); // �f�X�g���N�^

	void Init();
	void Init(const char8_t*);
	void Update();
	void Draw();
	void Uninit();

	// �ʒu�̐ݒ�
	void SetPosition(float x, float y, float z);
	void SetPosition(DirectX::SimpleMath::Vector3 pos);

	void Setnum(int);
};

