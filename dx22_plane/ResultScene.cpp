#include "ResultScene.h"
#include "Game.h"
#include "Texture2D.h"

// コンストラクタ
ResultScene::ResultScene()
{
	Init();
}

// デストラクタ
ResultScene::~ResultScene()
{
	Uninit();
}

// 初期化
void ResultScene::Init()
{
	//背景オブジェクトを作成
	Texture2D* pt = Game::GetInstance()->AddObject<Texture2D>();
	pt->SetTexture("assets/texture/background2.png");
	pt->SetPosition(0.0f, 0.0f, 0.0f);
	pt->SetScale(1280.0f, 720.0f, 0.0f);
	m_MySceneObjects.emplace_back(pt);

	// 背景オブジェクトを作成
	Texture2D* pt2 = Game::GetInstance()->AddObject<Texture2D>();
	pt2->SetTexture("assets/texture/resultString.png");
	pt2->SetPosition(300.0f, 0.0f, 0.0f);
	//pt2->SetScale(700.0f, 100.0f, 0.0f);
	pt2->SetScale(0.0f, 0.0f, 0.0f);
	pt2->SetUV(1, 1, 1, 13);
	m_MySceneObjects.emplace_back(pt2);

	Texture2D* pt3 = Game::GetInstance()->AddObject<Texture2D>();
	pt3->SetTexture("assets/texture/gameclear.png");
	pt3->SetPosition(0.0f, 0.0f, 0.0f);
	pt3->SetScale(600.0f, 600.0f, 0.0f);
	m_MySceneObjects.emplace_back(pt3);
}

// 更新
void ResultScene::Update()
{
	// エンターキーを押してタイトルへ
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Game::GetInstance()->ChangeScene(TITLE);
	}
}

// 終了処理
void ResultScene::Uninit()
{
	// このシーンのオブジェクトを削除する
	for (auto& o : m_MySceneObjects) {
		Game::GetInstance()->DeleteObject(o);
	}
}

void ResultScene::SetScore(int c) {
	//リザルト文字列オブジェクト
	Texture2D* stringObj = dynamic_cast<Texture2D*>(m_MySceneObjects[1]);

	switch (c) {
	case -4:
		stringObj->SetUV(1, 2, 1, 13);	// -4
		break;
	case -3:
		stringObj->SetUV(1, 3, 1, 13);	// -3
		break;
	case -2:
		stringObj->SetUV(1, 4, 1, 13);	// -2
		break;
	case -1:
		stringObj->SetUV(1, 5, 1, 13);	// -1
		break;
	case 0:
		stringObj->SetUV(1, 6, 1, 13);	// 0
		break;
	case 1:
		stringObj->SetUV(1, 7, 1, 13);	// 1
		break;
	case 2:
		stringObj->SetUV(1, 8, 1, 13);	// 2
		break;
	case 3:
		stringObj->SetUV(1, 9, 1, 13);	// 3
		break;
	case 4:
		stringObj->SetUV(1, 10, 1, 13);	// 4
		break;
	case 5:
		stringObj->SetUV(1, 11, 1, 13);	// 5
		break;
	case 6:
		stringObj->SetUV(1, 12, 1, 13);	// 6
		break;
	default:
		stringObj->SetUV(1, 13, 1, 13);	// 6
		break;
	}
}