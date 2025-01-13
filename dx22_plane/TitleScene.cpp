#include "TitleScene.h"
#include "Game.h"
#include "Texture2D.h"

// �R���X�g���N�^
TitleScene::TitleScene()
{
	Init();
}

// �f�X�g���N�^
TitleScene::~TitleScene()
{
	Uninit();
}

// ������
void TitleScene::Init()
{
	//�w�i�I�u�W�F�N�g���쐬
	Texture2D* pt = Game::GetInstance()->AddObject<Texture2D>();
	pt->SetTexture("assets/texture/background1.png");
	pt->SetPosition(0.0f,0.0f,0.0f);
	pt->SetRotation(0.0f,0.0f,0.0f);
	pt->SetScale(1280.0f,720.0f,0.0f);
	m_MySceneObjects.emplace_back(pt);

	Texture2D* pt2 = Game::GetInstance()->AddObject<Texture2D>();
	pt2->SetTexture("assets/texture/title.png");
	pt2->SetPosition(-1000.0f, 50.0f, 0.0f);
	pt2->SetRotation(0.0f, 0.0f, 0.0f);
	pt2->SetScale(600.0f, 600.0f, 0.0f);
	m_MySceneObjects.emplace_back(pt2);

	state = 0;
}

// �X�V
void TitleScene::Update()
{
	Texture2D* tex = dynamic_cast<Texture2D*>(m_MySceneObjects[1]);
	if (state == 0) {
		auto position = tex->GetPosition();
		position.x += 10.0f; // X���̈ʒu���X�V
		tex->SetPosition(position.x, 50.0f, 0.0f);

		if (position.x > 0.0f) {
			state = 1;
		}
	}
	// �G���^�[�L�[�������ăX�e�[�W1��
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Game::GetInstance()->ChangeScene(STAGE1);
	}
}

// �I������
void TitleScene::Uninit()
{
	// ���̃V�[���̃I�u�W�F�N�g���폜����
	for (auto& o : m_MySceneObjects) {
		Game::GetInstance()->DeleteObject(o);
	}
}
