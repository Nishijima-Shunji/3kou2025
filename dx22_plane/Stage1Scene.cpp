#include "Stage1Scene.h"
#include "Game.h"
#include "GolfBall.h"
#include "Ground.h"
#include "Arrow.h"
#include "Pole.h"
#include "Texture2D.h"
#include "Enemy.h"
#include "MAP.h"
#include "Num.h"


using namespace DirectX::SimpleMath;

// コンストラクタ
Stage1Scene::Stage1Scene()
{
	Init();
}

// デストラクタ
Stage1Scene::~Stage1Scene()
{
	Uninit();
}

// 初期化
void Stage1Scene::Init()
{
	m_Par = 4;			//パーの設定
	m_StrokeCount = 0;	//打数の初期化

	// オブジェクトを作成
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<GolfBall>());
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Ground>());
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Arrow>());
	//m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Enemy>());
	for (int i = 0; i < 6; i++) {
		m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Pole>());
	}
	for (int i = 1; i <= 6; i++) {
		std::u8string objname = u8"assets/model/num/";
		objname += std::u8string(reinterpret_cast<const char8_t*>(std::to_string(i).c_str()));
		objname += u8".obj";
		m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Num>(objname.c_str()));
	}
	//m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Map>());

	//UI背景
	Texture2D* pt1 = Game::GetInstance()->AddObject<Texture2D>();
	pt1->SetTexture("assets/texture/ui_back.png");
	pt1->SetPosition(-475.0f, -300.0f, 0.0f);
	pt1->SetScale(270.0f, 75.0f, 0.0f);
	m_MySceneObjects.emplace_back(pt1);

	//UI(next)
	Texture2D* pt2 = Game::GetInstance()->AddObject<Texture2D>();
	pt2->SetTexture("assets/texture/next.png");
	pt2->SetPosition(-545.0f, -225.0f, 0.0f);
	pt2->SetScale(250.0f, 250.0f, 0.0f);
	pt2->SetUV(1, 1, 1, 1);
	m_MySceneObjects.emplace_back(pt2);

	//UI(打目)
	Texture2D* pt3 = Game::GetInstance()->AddObject<Texture2D>();
	pt3->SetTexture("assets/texture/ui_string.png");
	pt3->SetPosition(-400.0f, -305.f, 0.0f);
	//pt3->SetScale(105.0f, 63.0f, 0.0f);
	pt3->SetScale(0.0f, 0.0f, 0.0f);
	pt3->SetUV(2, 1, 2, 1);
	m_MySceneObjects.emplace_back(pt3);

	//UI (パーの数値)
	Texture2D* pt4 = Game::GetInstance()->AddObject<Texture2D>();
	pt4->SetTexture("assets/texture/ui_number.png");
	pt4->SetPosition(-510.0f, -245.0f, 0.0f);
	//pt4->SetScale(65.0f, 45.0f, 0.0f);
	pt4->SetScale(0.0f, 0.0f, 0.0f);
	pt4->SetUV(m_Par + 1, 1, 10, 1);
	m_MySceneObjects.emplace_back(pt4);

	//UI(現在打数の数値　1の位	)
	Texture2D* pt5 = Game::GetInstance()->AddObject<Texture2D>();
	pt5->SetTexture("assets/texture/ui_number.png");
	pt5->SetPosition(-485.0f, -300.0f, 0.0f);
	pt5->SetScale(95.0f, 72.0f, 0.0f);
	pt5->SetUV(2, 1, 10, 1);
	m_MySceneObjects.emplace_back(pt5);

	//UI(現在打数の数値　10の位	)
	Texture2D* pt6 = Game::GetInstance()->AddObject<Texture2D>();
	pt6->SetTexture("assets/texture/ui_number.png");
	pt6->SetPosition(-556.0f, -300.0f, 0.0f);
	pt6->SetScale(95.0f, 72.0f, 0.0f);
	pt6->SetUV(1, 1, 10, 1);
	m_MySceneObjects.emplace_back(pt6);


	GolfBall* ball = dynamic_cast<GolfBall*>(m_MySceneObjects[0]);	// ゴルフボール
	Arrow* arrow = dynamic_cast<Arrow*>(m_MySceneObjects[2]);		// 矢印
	//Enemy* enemy = dynamic_cast<Enemy*>(m_MySceneObjects[3]);		// 敵

	ball->SetState(0);	//ボールを物理挙動差せる
	arrow->SetState(0);	//矢印を非表示

	// 位置を個別に設定
	std::vector<DirectX::SimpleMath::Vector3> positions = {
		{10.0f, 0.0f, 0.0f}, // pole1
		{-40.0f, 0.0f, 0.0f}, // pole2
		{0.0f, 0.0f, 70.0f}, // pole3
		{55.0f, 0.0f, -35.0f}, // pole4
		{-65.0f, 0.0f, 60.0f}, // pole5
		{70.0f, 0.0f, -55.0f}  // pole6
	};
	for (int i = 0; i < 6; ++i) {
		// ポールのインスタンスを取得
		Pole* pole = dynamic_cast<Pole*>(m_MySceneObjects[3 + i]);
		if (pole) {
			// 個別の位置を設定
			pole->SetPosition(positions[i]);
			pole->Setnum(i + 1);
		}
		Num* num = dynamic_cast<Num*>(m_MySceneObjects[9 + i]);
		if (num) {
			num->Setnum(i + 1);
		}
	}
	//map->SetPosition(DirectX::SimpleMath::Vector3(0.0f, -20.0f, 0.0f));
}

//更新
void Stage1Scene::Update()
{
	GolfBall* ball = dynamic_cast<GolfBall*>(m_MySceneObjects[0]);	//ゴルフボール
	Arrow* arrow = dynamic_cast<Arrow*>(m_MySceneObjects[2]);	//矢印
	//map->Update();
	//状態ごとに処理
	switch (m_State) {
		//ボール移動中
	case 0:
		if (ball && ball->GetState() == 1) {
			m_State = 1;
			arrow->SetState(m_State);
			m_StrokeCount++;	//打数をカウント

		}
		//打数を更新
		Texture2D* count[2];
		count[0] = dynamic_cast<Texture2D*>(m_MySceneObjects[19]);
		count[1] = dynamic_cast<Texture2D*>(m_MySceneObjects[20]);


		//各桁を後ろから取得
		for (int i = 0; i < 2; i++) {
			int cnt = (ball->Getnum() + 1) % (int)pow(10, i + 1) / (int)pow(10, i);	//1ケタ取り出す
			count[i]->SetUV(cnt + 1, 1, 10, 1);	//UV
		}
		//ボールがカップインしたらリザルトへ
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
			ball->Shot(v * 0.25f);
		}
		break;
	}
}

// 終了処理
void Stage1Scene::Uninit()
{
	// このシーンのオブジェクトを削除する
	for (auto& o : m_MySceneObjects) {
		Game::GetInstance()->DeleteObject(o);
	}
}

int Stage1Scene::GetScore() {
	//現在打数から計算
	return (m_StrokeCount - m_Par);
}