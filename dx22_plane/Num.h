#pragma once
#include "Object.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "Material.h"

//-----------------------------------------------------------------------------
// Poleクラス
//-----------------------------------------------------------------------------
class Num :public Object
{
private:

	// 描画の為の情報（メッシュに関わる情報）
	MeshRenderer m_MeshRenderer; // 頂点バッファ・インデックスバッファ・インデックス数

	// 描画の為の情報（見た目に関わる部分）
	std::vector<std::unique_ptr<Material>> m_Materiales;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // テクスチャ

	DirectX::XMFLOAT4X4 worldMatrix; // ワールド行列の保存用変数
	DirectX::SimpleMath::Vector3 forward;	// 前方ベクトルの格納
	int m_State = 0; // 0:非表示・1:方向選択・2:パワー選択
	int m_num = 0;

public:

	Num(Camera* cam); // コンストラクタ
	~Num(); // デストラクタ

	void Init();
	void Init(const char8_t*);
	void Update();
	void Draw();
	void Uninit();

	// 位置の設定
	void SetPosition(float x, float y, float z);
	void SetPosition(DirectX::SimpleMath::Vector3 pos);

	void Setnum(int);
};

