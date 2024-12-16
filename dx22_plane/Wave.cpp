#include "Wave.h"
#include "stb_image.h"

using namespace DirectX::SimpleMath;

//=======================================
//初期化処理
//=======================================
void Ground::Init()
{
	// 頂点データ
	std::vector<VERTEX_3D>	vertices;

	m_SizeX = 30;
	m_SizeZ = 30;

	vertices.resize(6 * m_SizeX * m_SizeZ);

	// インデックスバッファ生成
	std::vector<unsigned int> indices;
	indices.resize(6 * m_SizeX * m_SizeZ);
	for (int z = 0; z < m_SizeZ; z++) {
		for (int x = 0; x < m_SizeX; x++) {
			int n = z * m_SizeZ * 6 + x * 6;

			vertices[n + 0].position = Vector3(-0.5 + x - m_SizeX / 2, 0, 0.5 - z + m_SizeZ / 2);
			vertices[n + 1].position = Vector3(0.5 + x - m_SizeX / 2, 0, 0.5 - z + m_SizeZ / 2);
			vertices[n + 2].position = Vector3(-0.5 + x - m_SizeX / 2, 0, -0.5 - z + m_SizeZ / 2);
			vertices[n + 3].position = Vector3(-0.5 + x - m_SizeX / 2, 0, -0.5 - z + m_SizeZ / 2);
			vertices[n + 4].position = Vector3(0.5 + x - m_SizeX / 2, 0, 0.5 - z + m_SizeZ / 2);
			vertices[n + 5].position = Vector3(0.5 + x - m_SizeX / 2, 0, -0.5 - z + m_SizeZ / 2);

			vertices[n + 0].color = Color(1, 1, 1, 1);
			vertices[n + 1].color = Color(1, 1, 1, 1);
			vertices[n + 2].color = Color(1, 1, 1, 1);
			vertices[n + 3].color = Color(1, 1, 1, 1);
			vertices[n + 4].color = Color(1, 1, 1, 1);
			vertices[n + 5].color = Color(1, 1, 1, 1);

			vertices[n + 0].uv = Vector2(0, 0);
			vertices[n + 1].uv = Vector2(1, 0);
			vertices[n + 2].uv = Vector2(0, 1);
			vertices[n + 3].uv = Vector2(0, 1);
			vertices[n + 4].uv = Vector2(1, 0);
			vertices[n + 5].uv = Vector2(1, 1);

			vertices[n + 0].normal = Vector3(0, 1, 0);
			vertices[n + 1].normal = Vector3(0, 1, 0);
			vertices[n + 2].normal = Vector3(0, 1, 0);
			vertices[n + 3].normal = Vector3(0, 1, 0);
			vertices[n + 4].normal = Vector3(0, 1, 0);
			vertices[n + 5].normal = Vector3(0, 1, 0);

			indices[n + 0] = n + 0;
			indices[n + 1] = n + 1;
			indices[n + 2] = n + 2;
			indices[n + 3] = n + 3;
			indices[n + 4] = n + 4;
			indices[n + 5] = n + 5;
		}
	}
	//読み込む画像ファイルのパス
	const char* filename = "assets/texture/terain.png";

	//画像データを格納するポインタ
	unsigned char* imageData = nullptr;
	int width, height, channels;

	//グレースケール(1チャネル)で画像を読み込む
	imageData = stbi_load(filename, &width, &height, &channels, 1);
	if (imageData) {
		for (int z = 0; z < m_SizeZ; z++) {
			for (int x = 0; x < m_SizeX; x++) {
				int picX = x * (float)width / m_SizeX;
				int picY = z * (float)height / m_SizeZ;
				unsigned char pixelValue = imageData[picY * width + picX];
				float h = (float)pixelValue / 10.0f;
				int n = z * m_SizeZ * 6 + x * 6;
				vertices[n + 0].position.y = h;
				if (x != 0)vertices[n - 2].position.y = h;
				if (x != 0)vertices[n - 5].position.y = h;
				if (z != 0)vertices[n - m_SizeX * 6 + 2].position.y = h;
				if (z != 0)vertices[n - m_SizeX * 6 + 3].position.y = h;
				if (x != 0 && z != 0)vertices[n - m_SizeX * 6 - 1].position.y = h;
			}
		}

		//法線ベクトルを更新
		for (int z = 0; z < m_SizeZ; z++) {
			for (int x = 0; x < m_SizeX; x++) {
				int n = z * m_SizeZ * 6 + x * 6;

				//2つのベクトルを計算
				Vector3 v1 = vertices[n + 1].position - vertices[n + 0].position;
				Vector3 v2 = vertices[n + 2].position - vertices[n + 0].position;
				Vector3 normal = v1.Cross(v2);	//外積を計算
				normal.Normalize();				//正規化
				vertices[n + 0].normal = normal;
				vertices[n + 1].normal = normal;
				vertices[n + 2].normal = normal;

				//2つのベクトルを計算
				v1 = vertices[n + 4].position - vertices[n + 3].position;
				v2 = vertices[n + 5].position - vertices[n + 3].position;
				normal = v1.Cross(v2);	//外積を計算
				normal.Normalize();				//正規化
				vertices[n + 3].normal = normal;
				vertices[n + 4].normal = normal;
				vertices[n + 5].normal = normal;
			}
		}

		//メモリを解放
		stbi_image_free(imageData);
	}

	// 頂点バッファ生成
	m_VertexBuffer.Create(vertices);

	// インデックスバッファ生成
	m_IndexBuffer.Create(indices);

	// シェーダオブジェクト生成
	m_Shader.Create("shader/litTextureVS.hlsl", "shader/litTexturePS.hlsl");

	//テクスチャロード
	bool sts = m_Texture.Load("assets/texture/field.jpg");
	assert(sts = true);

	//マテリアル情報取得
	m_Materiale = std::make_unique<Material>();
	MATERIAL mtrl;
	mtrl.Diffuse = Color(1, 1, 1, 1);
	mtrl.Shiness = 1;
	mtrl.TextureEnable = true;	//テクスチャを使うか否かのフラグ
	m_Materiale->Create(mtrl);
}


//=======================================
//更新処理
//=======================================
void Ground::Update()
{
	m_Position.y = -20;
	m_Scale.x = 3;
	m_Scale.z = 3;
}

//=======================================
//描画処理
//=======================================
void Ground::Draw()
{
	// SRT情報作成
	Matrix r = Matrix::CreateFromYawPitchRoll(
		m_Rotation.y,
		m_Rotation.x,
		m_Rotation.z);

	Matrix t = Matrix::CreateTranslation(
		m_Position.x,
		m_Position.y,
		m_Position.z);

	Matrix s = Matrix::CreateScale(
		m_Scale.x,
		m_Scale.y,
		m_Scale.z);

	Matrix worldmtx;
	worldmtx = s * r * t;
	Renderer::SetWorldMatrix(&worldmtx); // GPUにセット

	// 描画の処理
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();

	// トポロジーをセット（プリミティブタイプ）
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();

	m_Texture.SetGPU();
	m_Materiale->SetGPU();

	devicecontext->DrawIndexed(
		6 * m_SizeX * m_SizeZ,		// 描画するインデックス数
		0,							// 最初のインデックスバッファの位置
		0);
}

//=======================================
//終了処理
//=======================================
void Ground::Uninit()
{

}