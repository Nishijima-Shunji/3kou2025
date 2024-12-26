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
>>>>>>> parent of 7158462 (ã‚«ãƒ¡ãƒ©ã®è¦–ç‚¹å¤‰æ›´ã¨æ•µã®æç”»åˆ‡ã‚Šæ›¿ãˆå®Ÿè£…)
=======
>>>>>>> parent of 7158462 (ã‚«ãƒ¡ãƒ©ã®è¦–ç‚¹å¤‰æ›´ã¨æ•µã®æç”»åˆ‡ã‚Šæ›¿ãˆå®Ÿè£…)

using namespace DirectX::SimpleMath;

// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
Stage1Scene::Stage1Scene()
{
	Init();
}

// ƒfƒXƒgƒ‰ƒNƒ^
Stage1Scene::~Stage1Scene()
{
	Uninit();
}

// ‰Šú‰»
void Stage1Scene::Init()
{
	m_Par = 4;			//ƒp[‚ÌÝ’è
	m_StrokeCount = 0;	//‘Å”‚Ì‰Šú‰»

	// ƒIƒuƒWƒFƒNƒg‚ðì¬
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
>>>>>>> parent of 7158462 (ã‚«ãƒ¡ãƒ©ã®è¦–ç‚¹å¤‰æ›´ã¨æ•µã®æç”»åˆ‡ã‚Šæ›¿ãˆå®Ÿè£…)
=======
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Ground>());
>>>>>>> parent of 7158462 (ã‚«ãƒ¡ãƒ©ã®è¦–ç‚¹å¤‰æ›´ã¨æ•µã®æç”»åˆ‡ã‚Šæ›¿ãˆå®Ÿè£…)

	//UI”wŒi
	Texture2D* pt1 = Game::GetInstance()->AddObject<Texture2D>();
	pt1->SetTexture("assets/texture/ui_back.png");
	pt1->SetPosition(-475.0f, -300.0f, 0.0f);
	pt1->SetScale(270.0f, 75.0f, 0.0f);
	m_MySceneObjects.emplace_back(pt1);

	//UI(ƒp[)
	Texture2D* pt2 = Game::GetInstance()->AddObject<Texture2D>();
	pt2->SetTexture("assets/texture/ui_string.png");
	pt2->SetPosition(-575.0f, -245.0f, 0.0f);
	pt2->SetScale(60.0f, 45.0f, 0.0f);
	pt2->SetUV(1, 1, 2, 1);
	m_MySceneObjects.emplace_back(pt2);

	//UI(‘Å–Ú)
	Texture2D* pt3 = Game::GetInstance()->AddObject<Texture2D>();
	pt3->SetTexture("assets/texture/ui_string.png");
	pt3->SetPosition(-400.0f, -305.f, 0.0f);
	pt3->SetScale(105.0f, 63.0f, 0.0f);
	pt3->SetUV(2, 1, 2, 1);
	m_MySceneObjects.emplace_back(pt3);

	//UI (ƒp[‚Ì”’l)
	Texture2D* pt4 = Game::GetInstance()->AddObject<Texture2D>();
	pt4->SetTexture("assets/texture/ui_number.png");
	pt4->SetPosition(-510.0f, -245.0f, 0.0f);
	pt4->SetScale(65.0f, 45.0f, 0.0f);
	pt4->SetUV(m_Par + 1, 1, 10, 1);
	m_MySceneObjects.emplace_back(pt4);

	//UI(Œ»Ý‘Å”‚Ì”’l@1‚ÌˆÊ	)
	Texture2D* pt5 = Game::GetInstance()->AddObject<Texture2D>();
	pt5->SetTexture("assets/texture/ui_number.png");
	pt5->SetPosition(-485.0f, -300.0f, 0.0f);
	pt5->SetScale(95.0f, 72.0f, 0.0f);
	pt5->SetUV(2, 1, 10, 1);
	m_MySceneObjects.emplace_back(pt5);

	//UI(Œ»Ý‘Å”‚Ì”’l@10‚ÌˆÊ	)
	Texture2D* pt6 = Game::GetInstance()->AddObject<Texture2D>();
	pt6->SetTexture("assets/texture/ui_number.png");
	pt6->SetPosition(-556.0f, -300.0f, 0.0f);
	pt6->SetScale(95.0f, 72.0f, 0.0f);
	pt6->SetUV(1, 1, 10, 1);
	m_MySceneObjects.emplace_back(pt6);

	GolfBall* ball = dynamic_cast<GolfBall*>(m_MySceneObjects[0]);	// ƒSƒ‹ƒtƒ{[ƒ‹
	Arrow* arrow = dynamic_cast<Arrow*>(m_MySceneObjects[2]);		// –îˆó
<<<<<<< HEAD
	Pole* pole = dynamic_cast<Pole*>(m_MySceneObjects[3]);			// ƒS[ƒ‹
	Enemy* enemy = dynamic_cast<Enemy*>(m_MySceneObjects[4]);		// “G
	Map* map = dynamic_cast<Map*>(m_MySceneObjects[5]);		// “G
=======
	Pole* pole = dynamic_cast<Pole*>(m_MySceneObjects[3]);			// 
<<<<<<< HEAD
>>>>>>> parent of 7158462 (ã‚«ãƒ¡ãƒ©ã®è¦–ç‚¹å¤‰æ›´ã¨æ•µã®æç”»åˆ‡ã‚Šæ›¿ãˆå®Ÿè£…)
=======
>>>>>>> parent of 7158462 (ã‚«ãƒ¡ãƒ©ã®è¦–ç‚¹å¤‰æ›´ã¨æ•µã®æç”»åˆ‡ã‚Šæ›¿ãˆå®Ÿè£…)
	ball->SetState(0);	//ƒ{[ƒ‹‚ð•¨—‹““®·‚¹‚é
	arrow->SetState(0);	//–îˆó‚ð”ñ•\Ž¦
	pole->SetPosition(0.0f, 0.0f, -3.0f);	//ƒ|[ƒ‹‚ÌˆÊ’u

	//m_MySceneObjects[4]->SetPosition();
}

//XV
void Stage1Scene::Update()
{
	GolfBall* ball = dynamic_cast<GolfBall*>(m_MySceneObjects[0]);	//ƒSƒ‹ƒtƒ{[ƒ‹
	Arrow* arrow = dynamic_cast<Arrow*>(m_MySceneObjects[2]);	//–îˆó

	//ó‘Ô‚²‚Æ‚Éˆ—
	switch (m_State) {
		//ƒ{[ƒ‹ˆÚ“®’†
	case 0:
		if (ball && ball->GetState() == 1) {
			m_State = 1;
			arrow->SetState(m_State);
			m_StrokeCount++;	//‘Å”‚ðƒJƒEƒ“ƒg

		}
		//‘Å”‚ðXV
		Texture2D* count[2];
		count[0] = dynamic_cast<Texture2D*>(m_MySceneObjects[8]);
		count[1] = dynamic_cast<Texture2D*>(m_MySceneObjects[9]);


		//ŠeŒ…‚ðŒã‚ë‚©‚çŽæ“¾
		for (int i = 0; i < 2; i++) {
			int cnt = m_StrokeCount % (int)pow(10, i + 1) / (int)pow(10, i);	//1ƒPƒ^Žæ‚èo‚·
			count[i]->SetUV(cnt + 1, 1, 10, 1);	//UV
		}
		//ƒ{[ƒ‹‚ªƒJƒbƒvƒCƒ“‚µ‚½‚çƒŠƒUƒ‹ƒg‚Ö
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
	//// ƒGƒ“ƒ^[ƒL[‚ð‰Ÿ‚µ‚ÄƒŠƒUƒ‹ƒg‚Ö
	//if (Input::GetKeyTrigger(VK_RETURN))
	//{
	//	Game::GetInstance()->ChangeScene(RESULT);
	//}

}

// I—¹ˆ—
void Stage1Scene::Uninit()
{
	// ‚±‚ÌƒV[ƒ“‚ÌƒIƒuƒWƒFƒNƒg‚ðíœ‚·‚é
	for (auto& o : m_MySceneObjects) {
		Game::GetInstance()->DeleteObject(o);
	}
}

int Stage1Scene::GetScore() {
	//Œ»Ý‘Å”‚©‚çŒvŽZ
	return (m_StrokeCount - m_Par);
}