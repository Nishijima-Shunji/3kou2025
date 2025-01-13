//#include <memory>
#include "Num.h"
#include "StaticMesh.h"
#include "utility.h"
#include "Game.h"
#include "Ground.h"
#include "Collision.h"
#include "Pole.h"
#include "GolfBall.h"

using namespace std;
using namespace DirectX::SimpleMath;

// コンストラクタ
Num::Num(Camera* cam) :Object(cam)
{

}

// デストラクタ
Num::~Num()
{

}

//=======================================
// 初期化処理
//=======================================
void Num::Init() {

}

void Num::Init(const char8_t* objname)
{
	// メッシュ読み込み
	StaticMesh staticmesh;

	// 3Dモデルデータ
	//std::u8string modelFile = u8"assets/model/golf_pole/golf_pole_NO_HOLE.obj";
	std::u8string modelFile = objname;

	// テクスチャディレクトリ
	std::string texDirectory = "assets/model/";

	// Meshを読み込む
	std::string tmpStr1(reinterpret_cast<const char*>(modelFile.c_str()), modelFile.size());
	staticmesh.Load(tmpStr1, texDirectory);

	m_MeshRenderer.Init(staticmesh);

	// シェーダオブジェクト生成
	m_Shader.Create("shader/litTextureVS.hlsl", "shader/litTexturePS.hlsl");

	// サブセット情報取得
	m_subsets = staticmesh.GetSubsets();

	// テクスチャ情報取得
	m_Textures = staticmesh.GetTextures();

	// マテリアル情報取得
	vector<MATERIAL> materials = staticmesh.GetMaterials();

	// マテリアル数分ループ
	for (int i = 0; i < materials.size(); i++)
	{
		// マテリアルオブジェクト生成
		std::unique_ptr<Material> m = std::make_unique<Material>();

		// マテリアル情報をセット
		m->Create(materials[i]);

		// マテリアルオブジェクトを配列に追加
		m_Materiales.push_back(std::move(m));
	}

	// モデルによってスケールを調整
	m_Scale.x = 3;
	m_Scale.y = 3;
	m_Scale.z = 3;
}

//=======================================
// 更新処理
//=======================================
void Num::Update()
{
	// ボールのスケーリング、回転、平行移動を組み合わせてワールド行列を作成
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);

	DirectX::XMMATRIX worldMatrixXM = scale * rotation * translation;
	DirectX::XMStoreFloat4x4(&worldMatrix, worldMatrixXM);
	// 前方ベクトルを計算
	forward = DirectX::SimpleMath::Vector3(worldMatrix._31, worldMatrix._32, worldMatrix._33);
	forward.Normalize(); // 正規化

	vector<GolfBall*> ballpt = Game::GetInstance()->GetObjects<GolfBall>();
	DirectX::SimpleMath::Vector3 ballpos = ballpt[0]->GetPosition();
	DirectX::SimpleMath::Vector3 direction = ballpos - m_Position;
	direction.y = 0.0f; // y軸の高さはそのままにする

	direction.Normalize(); // 正規化

	// プレイヤーの向きを設定
	float yaw = std::atan2(direction.x, direction.z);

	yaw += DirectX::XM_PI;
	// y軸回転をyawで設定し、他の回転をそのままに
	m_Rotation.y = yaw;

	std::vector<Pole*> polept = Game::GetInstance()->GetObjects<Pole>(
		[this](Pole* pole) { return pole->Getnum() == m_num; }
	);
	m_Position = polept[0]->GetPosition();
	m_Position.y = 10.0f;
}

//=======================================
// 描画処理
//=======================================
void Num::Draw()
{
	// SRT情報作成
	Matrix r = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	Matrix t = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	Matrix s = Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);

	Matrix worldmtx;
	worldmtx = s * r * t;
	Renderer::SetWorldMatrix(&worldmtx); // GPUにセット

	m_Shader.SetGPU();

	// インデックスバッファ・頂点バッファをセット
	m_MeshRenderer.BeforeDraw();

	// カメラの設定を指定
	m_Camera->SetCamera(0);

	//マテリアル数分ループ 
	for (int i = 0; i < m_subsets.size(); i++)
	{
		// マテリアルをセット(サブセット情報の中にあるマテリアルインデックスを使用)
		m_Materiales[m_subsets[i].MaterialIdx]->SetGPU();

		if (m_Materiales[m_subsets[i].MaterialIdx]->isTextureEnable())
		{
			m_Textures[m_subsets[i].MaterialIdx]->SetGPU();
		}

		m_MeshRenderer.DrawSubset(
			m_subsets[i].IndexNum, // 描画するインデックス数
			m_subsets[i].IndexBase, // 最初のインデックスバッファの位置	
			m_subsets[i].VertexBase); // 頂点バッファの最初から使用
	}
}

//=======================================
// 終了処理
//=======================================
void Num::Uninit()
{

}


//位置の設定
void Num::SetPosition(float x, float y, float z)
{
	Vector3 p = { x, y, z };
	SetPosition(p);
}
void Num::SetPosition(Vector3 pos)
{
	m_Position = pos;

	// Y座標を地形に合わせて変更

	// Groundの頂点データを取得
	vector<Ground*> grounds = Game::GetInstance()->GetObjects<Ground>();
	vector<VERTEX_3D> vertices;
	for (auto& g : grounds) // Groundオブジェクトの数ループ
	{
		vector<VERTEX_3D> vecs = g->GetVertices();
		for (auto& v : vecs) // 頂点の数ループ
		{
			vertices.emplace_back(v);
		}
	}

	// 線分とポリゴンの当たり判定
	for (int i = 0; i < vertices.size(); i += 3)
	{
		// 三角形ポリゴン
		Collision::Polygon collisionPolygon = {
			vertices[i + 0].position,
			vertices[i + 1].position,
			vertices[i + 2].position };

		Vector3 cp; // 接触点

		Collision::Line line = { m_Position , Vector3(0,1,0) };
		if (Collision::CheckHit(line, collisionPolygon, cp))
		{
			m_Position.y = cp.y; // 接触点のちょっとだけ上をNumのY座標とする
		}


	}
}

void Num::Setnum(int num) {
	m_num = num;
}