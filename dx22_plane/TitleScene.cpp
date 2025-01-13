#include "TitleScene.h"
#include "Game.h"
#include "Texture2D.h"

// コンストラクタ
TitleScene::TitleScene()
{
	Init();
}

// デストラクタ
TitleScene::~TitleScene()
{
	Uninit();
}

// 初期化
void TitleScene::Init()
{
	//背景オブジェクトを作成
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

// 更新
void TitleScene::Update()
{
	Texture2D* tex = dynamic_cast<Texture2D*>(m_MySceneObjects[1]);
	if (state == 0) {
		auto position = tex->GetPosition();
		position.x += 10.0f; // X軸の位置を更新
		tex->SetPosition(position.x, 50.0f, 0.0f);

		if (position.x > 0.0f) {
			state = 1;
		}
	}
	// エンターキーを押してステージ1へ
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Game::GetInstance()->ChangeScene(STAGE1);
	}
}

// 終了処理
void TitleScene::Uninit()
{
	// このシーンのオブジェクトを削除する
	for (auto& o : m_MySceneObjects) {
		Game::GetInstance()->DeleteObject(o);
	}
}
