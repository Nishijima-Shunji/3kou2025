#pragma once
#include "Object.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "Material.h"
#include "input.h"

class Enemy :public Object
{
private:
	const float gravity = 0.05f;		// �d��
	const float basicSpeed = 1.0f;		// ��{���x
	const float basicMaxSpeed = 1.0f;	// ��{���x
	float maxSpeed = 1.0f;				// �ő呬�x
	float acceleration = 0.1f;			// �����x
	float deceleration = 0.2f;			// �����x
	float speed = 1.0f;					// �ړ����x

	//���x
	DirectX::SimpleMath::Vector3 m_Velocity = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	//�����x
	DirectX::SimpleMath::Vector3 m_Acceralation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	// �`��ׂ̈̏��i���b�V���Ɋւ����j
	MeshRenderer m_MeshRenderer; // ���_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�E�C���f�b�N�X��

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	std::vector<std::unique_ptr<Material>> m_Materiales;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // �e�N�X�`��

	int m_State = 0;		//���	0:��������,�@1:��~�@2:�J�b�v�C��
	int m_StopCount = 0;	//�Î~�J�E���g
	DirectX::SimpleMath::Vector3 lookDirection;

	DirectX::XMFLOAT4X4 worldMatrix; // ���[���h�s��̕ۑ��p�ϐ�
	DirectX::SimpleMath::Vector3 forward;	// �O���x�N�g���̊i�[

	Input input;

public:
	Enemy(Camera* cam);	//�R���X�g���N�^
	~Enemy();			//�f�X�g���N�^

	void Init();
	void Update();
	void Draw();
	void Uninit();

	//��Ԃ̐ݒ�E�擾
	void SetState(int s);
	int GetState();
	DirectX::SimpleMath::Vector3 Getforward();

	//�V���b�g
	void Shot(DirectX::SimpleMath::Vector3 v);
	// �ړ�
	void Move();
};

