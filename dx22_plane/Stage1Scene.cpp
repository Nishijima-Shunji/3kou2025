#include "Stage1Scene.h"
#include "Game.h"
#include "GolfBall.h"
#include "Ground.h"
#include "Arrow.h"
#include "Pole.h"
#include "Texture2D.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "Enemy.h"
#include "Map.h"
=======
>>>>>>> parent of 7158462 (カメラの視点変更と敵の描画切り替え実装)
=======
>>>>>>> parent of 7158462 (カメラの視点変更と敵の描画切り替え実装)

using namespace DirectX::SimpleMath;

// �R���X�g���N�^
Stage1Scene::Stage1Scene()
{
	Init();
}

// �f�X�g���N�^
Stage1Scene::~Stage1Scene()
{
	Uninit();
}

// ������
void Stage1Scene::Init()
{
	m_Par = 4;			//�p�[�̐ݒ�
	m_StrokeCount = 0;	//�Ő��̏�����

	// �I�u�W�F�N�g���쐬
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<GolfBall>());
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Ground>());
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Arrow>());
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Pole>());
<<<<<<< HEAD
<<<<<<< HEAD
	//m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Ground>());
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Enemy>());
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Map>());
=======
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Ground>());
>>>>>>> parent of 7158462 (カメラの視点変更と敵の描画切り替え実装)
=======
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Ground>());
>>>>>>> parent of 7158462 (カメラの視点変更と敵の描画切り替え実装)

	//UI�w�i
	Texture2D* pt1 = Game::GetInstance()->AddObject<Texture2D>();
	pt1->SetTexture("assets/texture/ui_back.png");
	pt1->SetPosition(-475.0f, -300.0f, 0.0f);
	pt1->SetScale(270.0f, 75.0f, 0.0f);
	m_MySceneObjects.emplace_back(pt1);

	//UI(�p�[)
	Texture2D* pt2 = Game::GetInstance()->AddObject<Texture2D>();
	pt2->SetTexture("assets/texture/ui_string.png");
	pt2->SetPosition(-575.0f, -245.0f, 0.0f);
	pt2->SetScale(60.0f, 45.0f, 0.0f);
	pt2->SetUV(1, 1, 2, 1);
	m_MySceneObjects.emplace_back(pt2);

	//UI(�Ŗ�)
	Texture2D* pt3 = Game::GetInstance()->AddObject<Texture2D>();
	pt3->SetTexture("assets/texture/ui_string.png");
	pt3->SetPosition(-400.0f, -305.f, 0.0f);
	pt3->SetScale(105.0f, 63.0f, 0.0f);
	pt3->SetUV(2, 1, 2, 1);
	m_MySceneObjects.emplace_back(pt3);

	//UI (�p�[�̐��l)
	Texture2D* pt4 = Game::GetInstance()->AddObject<Texture2D>();
	pt4->SetTexture("assets/texture/ui_number.png");
	pt4->SetPosition(-510.0f, -245.0f, 0.0f);
	pt4->SetScale(65.0f, 45.0f, 0.0f);
	pt4->SetUV(m_Par + 1, 1, 10, 1);
	m_MySceneObjects.emplace_back(pt4);

	//UI(���ݑŐ��̐��l�@1�̈�	)
	Texture2D* pt5 = Game::GetInstance()->AddObject<Texture2D>();
	pt5->SetTexture("assets/texture/ui_number.png");
	pt5->SetPosition(-485.0f, -300.0f, 0.0f);
	pt5->SetScale(95.0f, 72.0f, 0.0f);
	pt5->SetUV(2, 1, 10, 1);
	m_MySceneObjects.emplace_back(pt5);

	//UI(���ݑŐ��̐��l�@10�̈�	)
	Texture2D* pt6 = Game::GetInstance()->AddObject<Texture2D>();
	pt6->SetTexture("assets/texture/ui_number.png");
	pt6->SetPosition(-556.0f, -300.0f, 0.0f);
	pt6->SetScale(95.0f, 72.0f, 0.0f);
	pt6->SetUV(1, 1, 10, 1);
	m_MySceneObjects.emplace_back(pt6);

	GolfBall* ball = dynamic_cast<GolfBall*>(m_MySceneObjects[0]);	// �S���t�{�[��
	Arrow* arrow = dynamic_cast<Arrow*>(m_MySceneObjects[2]);		// ���
<<<<<<< HEAD
	Pole* pole = dynamic_cast<Pole*>(m_MySceneObjects[3]);			// �S�[��
	Enemy* enemy = dynamic_cast<Enemy*>(m_MySceneObjects[4]);		// �G
	Map* map = dynamic_cast<Map*>(m_MySceneObjects[5]);		// �G
=======
	Pole* pole = dynamic_cast<Pole*>(m_MySceneObjects[3]);			// 
<<<<<<< HEAD
>>>>>>> parent of 7158462 (カメラの視点変更と敵の描画切り替え実装)
=======
>>>>>>> parent of 7158462 (カメラの視点変更と敵の描画切り替え実装)
	ball->SetState(0);	//�{�[���𕨗�����������
	arrow->SetState(0);	//�����\��
	pole->SetPosition(0.0f, 0.0f, -3.0f);	//�|�[���̈ʒu

	//m_MySceneObjects[4]->SetPosition();
}

//�X�V
void Stage1Scene::Update()
{
	GolfBall* ball = dynamic_cast<GolfBall*>(m_MySceneObjects[0]);	//�S���t�{�[��
	Arrow* arrow = dynamic_cast<Arrow*>(m_MySceneObjects[2]);	//���

	//��Ԃ��Ƃɏ���
	switch (m_State) {
		//�{�[���ړ���
	case 0:
		if (ball && ball->GetState() == 1) {
			m_State = 1;
			arrow->SetState(m_State);
			m_StrokeCount++;	//�Ő����J�E���g

		}
		//�Ő����X�V
		Texture2D* count[2];
		count[0] = dynamic_cast<Texture2D*>(m_MySceneObjects[8]);
		count[1] = dynamic_cast<Texture2D*>(m_MySceneObjects[9]);


		//�e������납��擾
		for (int i = 0; i < 2; i++) {
			int cnt = m_StrokeCount % (int)pow(10, i + 1) / (int)pow(10, i);	//1�P�^���o��
			count[i]->SetUV(cnt + 1, 1, 10, 1);	//UV
		}
		//�{�[�����J�b�v�C�������烊�U���g��
		if (ball->GetState() == 2) {
			Game::GetInstance()->ChangeScene(RESULT);
		}
		break;
	case 1:
		if (Input::GetKeyTrigger(VK_SPACE)) {
			m_State = 2;
			arrow->SetState(m_State);
		}
		break;
	case 2:
		if (Input::GetKeyTrigger(VK_SPACE)) {
			m_State = 0;
			ball->SetState(m_State);
			arrow->SetState(m_State);

			Vector3 v = arrow->GetVector();
			ball->Shot(v* 0.25f);
		}
		break;
	}
	//// �G���^�[�L�[�������ă��U���g��
	//if (Input::GetKeyTrigger(VK_RETURN))
	//{
	//	Game::GetInstance()->ChangeScene(RESULT);
	//}

}

// �I������
void Stage1Scene::Uninit()
{
	// ���̃V�[���̃I�u�W�F�N�g���폜����
	for (auto& o : m_MySceneObjects) {
		Game::GetInstance()->DeleteObject(o);
	}
}

int Stage1Scene::GetScore() {
	//���ݑŐ�����v�Z
	return (m_StrokeCount - m_Par);
}