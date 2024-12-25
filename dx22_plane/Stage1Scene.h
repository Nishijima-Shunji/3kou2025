#pragma once
#include "Scene.h"
#include "Object.h"

// Stage1Scen�N���X
class Stage1Scene : public Scene
{
private:
	std::vector<Object*> m_MySceneObjects; // ���̃V�[���̃I�u�W�F�N�g

	int m_State = 0;	//��ԁ@0:�{�[���ړ���, 1:�����I��, 2:�p���[�I��

	void Init(); // ������
	void Uninit(); // �I������

	int m_Par;	//�p�[
	int m_StrokeCount;	// ���݂̑Ő�
public:
	Stage1Scene(); // �R���X�g���N�^
	~Stage1Scene(); // �f�X�g���N�^

	void Update(); // �X�V

	int GetScore();	//�X�R�A���擾
};

