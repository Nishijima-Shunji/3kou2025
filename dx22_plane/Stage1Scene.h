#pragma once
#include "Scene.h"
#include "Object.h"

// Stage1Scenクラス
class Stage1Scene : public Scene
{
private:
	std::vector<Object*> m_MySceneObjects; // このシーンのオブジェクト

	int m_State = 0;	//状態　0:ボール移動中, 1:方向選択中, 2:パワー選択中

	void Init(); // 初期化
	void Uninit(); // 終了処理

	int m_Par;	//パー
	int m_StrokeCount;	// 現在の打数
public:
	Stage1Scene(); // コンストラクタ
	~Stage1Scene(); // デストラクタ

	void Update(); // 更新

	int GetScore();	//スコアを取得
};

