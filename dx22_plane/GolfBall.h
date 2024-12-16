#pragma once
#include "Object.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "Material.h"
#include "input.h"

class GolfBall :public Object
{
private:
	//速度
	DirectX::SimpleMath::Vector3 m_Velocity = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	//加速度
	DirectX::SimpleMath::Vector3 m_Acceralation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	// 描画の為の情報（メッシュに関わる情報）
	MeshRenderer m_MeshRenderer; // 頂点バッファ・インデックスバッファ・インデックス数

	// 描画の為の情報（見た目に関わる部分）
	std::vector<std::unique_ptr<Material>> m_Materiales;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // テクスチャ

	int m_State = 0;		//状態	0:物理挙動,　1:停止　2:カップイン
	int m_StopCount = 0;	//静止カウント
	DirectX::SimpleMath::Vector3 lookDirection;

	DirectX::XMFLOAT4X4 worldMatrix; // ワールド行列の保存用変数
	DirectX::SimpleMath::Vector3 forward;	// 前方ベクトルの格納

	Input input;

public:
	GolfBall(Camera* cam);	//コンストラクタ
	~GolfBall();			//デストラクタ

	void Init();
	void Update();
	void Draw();
	void Uninit();

	//状態の設定・取得
	void SetState(int s);
	int GetState();
	DirectX::SimpleMath::Vector3 Getforward();

	//ショット
	void Shot(DirectX::SimpleMath::Vector3 v);
};

