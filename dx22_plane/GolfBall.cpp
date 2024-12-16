#include <memory>
#include "GolfBall.h"
#include "StaticMesh.h"
#include "utility.h"
#include "Collision.h"
#include "Game.h"
#include "Ground.h"
#include "Pole.h"

using namespace DirectX::SimpleMath;
using namespace std;

//コンストラクタ
GolfBall::GolfBall(Camera* cam) : Object(cam) {

}

//デストラクタ
GolfBall::~GolfBall() {

}

void GolfBall::Init()
{
	// メッシュ読み込み
	StaticMesh staticmesh;

	//3Dモデルデータ
	std::u8string modelFile = u8"assets/model/golfball2/golf_ball.obj";

	//テクスチャディレクトリ
	std::string texDirectory = "assets/model/";

	//Meshを読み込む
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
	std::vector<MATERIAL> materials = staticmesh.GetMaterials();

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

	//モデルによってスケールを調整
	m_Scale.x = 0.5;
	m_Scale.y = 0.5;
	m_Scale.z = 0.5;

	m_Position.y = 15.0f;
}

void GolfBall::Update()
{
	// ワールド行列から前方ベクトルを取得する例
	// オブジェクトの変換情報（スケーリング、回転、平行移動など）をもとにワールド行列を生成
	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMStoreFloat4x4(&worldMatrix, DirectX::XMMatrixIdentity()); // 空の初期化例
	DirectX::SimpleMath::Vector3 forward = DirectX::XMVectorSet(worldMatrix._31, worldMatrix._32, worldMatrix._33, 0.0f);
	//lookDirection = m_Position * DirectX::SimpleMath::Vector3{ 1.0f,0.0f,1.0f };
	lookDirection = m_Position * forward;



	if (m_State != 0) return;	//静止状態ならreturn
	Vector3 oldPos = m_Position;

	//速度が0に近いと停止させる
	if (m_Velocity.LengthSquared() < 0.03f) {
		m_StopCount++;

		if (Input::GetKeyTrigger(VK_A)) {
			m_Velocity.x -= 0.5f;
			m_Velocity.y += 2.0f;
		}
		if (Input::GetKeyTrigger(VK_D)) {
			m_Velocity.x += 0.5f;
			m_Velocity.y += 2.0f;
		}
		if (Input::GetKeyTrigger(VK_W)) {
			m_Velocity.z += 0.5f;
			m_Velocity.y += 2.0f;
		}
		if (Input::GetKeyTrigger(VK_S)) {
			m_Velocity.z -= 0.5f;
			m_Velocity.y += 2.0f;
		}
	}
	else {
		m_StopCount = 0;
		//減速度(1フレームあたりの減速量)
		float decelerationPower = 0.003f;

		Vector3 deceleration = -m_Velocity;	//速度の逆ベクトルを計算
		deceleration.Normalize();
		m_Acceralation = deceleration * decelerationPower;

		//加速度を速度に加算
		m_Velocity += m_Acceralation;
		m_Rotation.z += 0.1f;
	}

	// 10フレーム連続でほとんど動いていなければ静止状態へ
	if (m_StopCount > 10) {
		m_Velocity = Vector3(0.0f, 0.0f, 0.0f);
		m_State = 1; //静止状態
	}

	//重力
	const float gravity = 0.05f;
	m_Velocity.y -= gravity;

	//速度を座標に加算
	m_Position += m_Velocity;

	float radius = 0.5f;	//ボールの直径

	//Groundの頂点データを取得
	vector<Ground*>grounds = Game::GetInstance()->GetObjects<Ground>();
	vector<VERTEX_3D> vertices;
	for (auto& g : grounds) {
		vector<VERTEX_3D> vecs = g->GetVertices();
		for (auto& v : vecs) {
			vertices.emplace_back(v);
		}
	}

	float moveDistance = 9999;	//移動距離
	Vector3 contactPoint;		//接触点
	Vector3 normal;

	//線分とポリゴンの当たり判定
	bool senbunFg = false;
	for (int i = 0; i < vertices.size(); i += 3) {
		//三角形ポリゴン
		Collision::Polygon CollisionPolygon = {
			vertices[i + 0].position,
			vertices[i + 1].position,
			vertices[i + 2].position
		};
		Vector3 cp;	//接触点
		Collision::Segment collisionSegment = { oldPos, m_Position };
		if (Collision::CheckHit(collisionSegment, CollisionPolygon, cp)) {
			float md = 0;
			Vector3 np = Collision::moveSphere(collisionSegment, radius, CollisionPolygon, cp, md);
			if (moveDistance > md) {
				moveDistance = md;
				m_Position = np;
				contactPoint = cp;
				normal = Collision::GetNormal(CollisionPolygon);
			}
			senbunFg = true;
		}
	}

	//球体とポリゴンの当たり判定
	if (!senbunFg) {
		for (int i = 0; i < vertices.size(); i += 3) {
			//三角形ポリゴン
			Collision::Polygon CollisionPolygon = {
				vertices[i + 0].position,
				vertices[i + 1].position,
				vertices[i + 2].position
			};
			Vector3 cp;	//接触点
			Collision::Sphere collisionSphere = { m_Position,radius };
			if (Collision::CheckHit(collisionSphere, CollisionPolygon, cp)) {
				float md = 0;
				Vector3 np = Collision::moveSphere(collisionSphere, CollisionPolygon, cp);
				md = (np - oldPos).Length();
				if (moveDistance > md) {
					moveDistance = md;
					m_Position = np;
					contactPoint = cp;
					normal = Collision::GetNormal(CollisionPolygon);
				}
			}
		}
	}
		if (moveDistance != 9999) {	//もし当たっていたら	
			m_Velocity.y = -gravity;
			//std::cout << "Hit" << std::endl;

			//ボールの速度ベクトルの法線方向成分を分解
			float velocityNormal = Collision::Dot(m_Velocity, normal);
			Vector3 v1 = velocityNormal * normal;	//法線方向成分
			Vector3 v2 = m_Velocity - v1;	//接線方向成分

			//反発係数
			const float restitution = 0.55f;

			//反射ベクトルを計算
			Vector3 reflectedVelocity = v2 - restitution * v1;

			//ボールの速度を更新
			m_Velocity = reflectedVelocity;
		}

	//下に落ちたらリスポーン
	if (m_Position.y < -100) {
		m_Position = Vector3(0.0f, 50.0f, 0.0f);
		m_Velocity = Vector3(0.0f, 0.0f, 0.0f);
	}

	//Poleの位置を取得
	vector<Pole*> pole = Game::GetInstance()->GetObjects<Pole>();
	if (pole.size() > 0) {
		Vector3 polePos = pole[0]->GetPosition();

		Collision::Sphere balCollision = { m_Position, radius };
		Collision::Sphere poleCollision = { polePos, 0.5f };

		if (Collision::CheckHit(balCollision, poleCollision)) {
			m_State = 2;	//カップイン
		}
	}
}

void GolfBall::Draw()
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

	//カメラの設定を指定
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
			m_subsets[i].IndexNum,		// 描画するインデックス数
			m_subsets[i].IndexBase,		// 最初のインデックスバッファの位置	
			m_subsets[i].VertexBase);	// 頂点バッファの最初から使用
	}
}

void GolfBall::Uninit()
{

}

//状態の設定・取得
void GolfBall::SetState(int s) {
	m_State = s;
}

int GolfBall::GetState() {
	return m_State;
}

//ショット
void GolfBall::Shot(Vector3 v) {
	m_Velocity = v;
}

DirectX::SimpleMath::Vector3 GolfBall::GetlookDirection() {
	return lookDirection;
}