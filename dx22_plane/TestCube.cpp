#include	"TestCube.h"

using namespace DirectX::SimpleMath;

//=======================================
//初期化処理
//=======================================
void TestCube::Init(int a)
{
	// 頂点データ
	std::vector<VERTEX_3D>	vertices;

	vertices.resize(24);

	/*vertices[0].position = Vector3(-10,  10,  10);
	vertices[1].position = Vector3( 10,  10,  10);
	vertices[2].position = Vector3(-10,  10, -10);
	vertices[3].position = Vector3( 10,  10, -10);
	vertices[4].position = Vector3(-10, -10, -10);
	vertices[5].position = Vector3( 10, -10, -10);
	vertices[6].position = Vector3( 10, -10,  10);
	vertices[7].position = Vector3(-10, -10,  10);*/

	vertices[0].position = Vector3(-10 + a,  10,  10);
	vertices[1].position = Vector3( 10 + a,  10,  10);
	vertices[2].position = Vector3(-10 + a,  10, -10);
	vertices[3].position = Vector3( 10 + a,  10, -10);

	vertices[4].position = Vector3(-10 + a,  10, -10);
	vertices[5].position = Vector3( 10 + a,  10, -10);
	vertices[6].position = Vector3(-10 + a, -10, -10);
	vertices[7].position = Vector3( 10 + a, -10, -10);

	vertices[8].position = Vector3( -10 + a,  10,  10);
	vertices[9].position = Vector3( -10 + a, 10, -10);
	vertices[10].position = Vector3(-10 + a, -10, 10);
	vertices[11].position = Vector3(-10 + a, -10, -10);

	vertices[12].position = Vector3( 10 + a,  10,  10);
	vertices[13].position = Vector3(-10 + a,  10,  10);
	vertices[14].position = Vector3( 10 + a, -10,  10);
	vertices[15].position = Vector3(-10 + a, -10,  10);

	vertices[16].position = Vector3(10 + a, 10, -10);
	vertices[17].position = Vector3(10 + a, 10, 10);
	vertices[18].position = Vector3(10 + a, -10, -10);
	vertices[19].position = Vector3(10 + a, -10, 10);

	vertices[20].position = Vector3(-10 + a, -10, -10);
	vertices[21].position = Vector3( 10 + a, -10, -10);
	vertices[22].position = Vector3(-10 + a, -10,  10);
	vertices[23].position = Vector3( 10 + a, -10,  10);


	vertices[0].color = Color(1, 1, 1, 1);
	vertices[1].color = Color(1, 1, 1, 1);
	vertices[2].color = Color(1, 1, 1, 1);
	vertices[3].color = Color(1, 1, 1, 1);
	vertices[4].color = Color(1, 1, 1, 1);
	vertices[5].color = Color(1, 1, 1, 1);
	vertices[6].color = Color(1, 1, 1, 1);
	vertices[7].color = Color(1, 1, 1, 1);
	vertices[8].color = Color(1, 1, 1, 1);
	vertices[9].color = Color(1, 1, 1, 1);
	vertices[10].color = Color(1, 1, 1, 1);
	vertices[11].color = Color(1, 1, 1, 1);
	vertices[12].color = Color(1, 1, 1, 1);
	vertices[13].color = Color(1, 1, 1, 1);
	vertices[14].color = Color(1, 1, 1, 1);
	vertices[15].color = Color(1, 1, 1, 1);
	vertices[16].color = Color(1, 1, 1, 1);
	vertices[17].color = Color(1, 1, 1, 1);
	vertices[18].color = Color(1, 1, 1, 1);
	vertices[19].color = Color(1, 1, 1, 1);
	vertices[20].color = Color(1, 1, 1, 1);
	vertices[21].color = Color(1, 1, 1, 1);
	vertices[22].color = Color(1, 1, 1, 1);
	vertices[23].color = Color(1, 1, 1, 1);

	//上
	vertices[0].uv = Vector2(0, 0);
	vertices[1].uv = Vector2(0.33, 0);
	vertices[2].uv = Vector2(0, 0.5);
	vertices[3].uv = Vector2(0.33, 0.5);
	//手前
	vertices[4].uv = Vector2(0.33, 0);
	vertices[5].uv = Vector2(0.66, 0);
	vertices[6].uv = Vector2(0.33, 0.5);
	vertices[7].uv = Vector2(0.66, 0.5);
	//左
	vertices[8].uv = Vector2(0.66, 0);
	vertices[9].uv = Vector2(1, 0);
	vertices[10].uv = Vector2(0.66, 0.5);
	vertices[11].uv = Vector2(1, 0.5);
	//奥
	vertices[12].uv = Vector2(0.33, 0.5);
	vertices[13].uv = Vector2(0.66, 0.5);
	vertices[14].uv = Vector2(0.33, 1);
	vertices[15].uv = Vector2(0.66, 1);
	//右
	vertices[16].uv = Vector2(0, 0.5);
	vertices[17].uv = Vector2(0.33, 0.5);
	vertices[18].uv = Vector2(0, 1);
	vertices[19].uv = Vector2(0.33, 1);
	//下
	vertices[20].uv = Vector2(0.66, 0.5);
	vertices[21].uv = Vector2(1, 0.5);
	vertices[22].uv = Vector2(0.66, 1);
	vertices[23].uv = Vector2(1, 1);


	vertices[0].normal = Vector3(0, 1, 0);
	vertices[1].normal = Vector3(0, 1, 0);
	vertices[2].normal = Vector3(0, 1, 0);
	vertices[3].normal = Vector3(0, 1, 0);
	vertices[4].normal = Vector3(0, 0, -1);
	vertices[5].normal = Vector3(0, 0, -1);
	vertices[6].normal = Vector3(0, 0, -1);
	vertices[7].normal = Vector3(0, 0, -1);
	vertices[8].normal = Vector3(-1, 0, 0);
	vertices[9].normal = Vector3(-1, 0, 0);
	vertices[10].normal = Vector3(-1, 0, 0);
	vertices[11].normal = Vector3(-1, 0, 0);
	vertices[12].normal = Vector3(0, 0, 1);
	vertices[13].normal = Vector3(0, 0, 1);
	vertices[14].normal = Vector3(0, 0, 1);
	vertices[15].normal = Vector3(0, 0, 1);
	vertices[16].normal = Vector3(1, 0, 0);
	vertices[17].normal = Vector3(1, 0, 0);
	vertices[18].normal = Vector3(1, 0, 0);
	vertices[19].normal = Vector3(1, 0, 0);
	vertices[20].normal = Vector3(0, -1, 0);
	vertices[21].normal = Vector3(0, -1, 0);
	vertices[22].normal = Vector3(0, -1, 0);
	vertices[23].normal = Vector3(0, -1, 0);


	// 頂点バッファ生成
	m_VertexBuffer.Create(vertices);

	// インデックスバッファ生成
	std::vector<unsigned int> indices;
	/*indices.resize(5);
	
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;
	indices[4] = 4;*/

	//indices.resize(36);
	//indices = {
	//	0,1,2,	//上
	//	1,3,2,

	//	2,3,4,	//手前
	//	3,5,4,

	//	0,2,4,	//左
	//	0,4,7,

	//	1,0,7,	//裏
	//	1,7,6,

	//	3,1,6,	//右
	//	3,6,5,

	//	4,5,6,	//下
	//	4,6,7,

	//};

	indices.resize(36);
	indices = {
		0,1,2,
		1,3,2,

		4,5,6,
		5,7,6,

		8,9,11,
		8,11,10,

		12,13,15,
		12,15,14,

		16,17,19,
		16,19,18,

		20,21,23,
		20,23,22
	};

	// インデックスバッファ生成
	m_IndexBuffer.Create(indices);

	// シェーダオブジェクト生成
	//m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");
	m_Shader.Create("shader/litTextureVS.hlsl", "shader/litTexturePS.hlsl");

	//テクスチャロード
	bool sts = m_Texture.Load("assets/texture/dice.png");
	assert(sts = true);
}


//=======================================
//更新処理
//=======================================
void TestCube::Update()
{
	m_Rotation.y -= 0.02f;
	m_Rotation.x += 0.02f;
}

//=======================================
//描画処理
//=======================================
void TestCube::Draw()
{
	// SRT情報作成
	Matrix r = Matrix::CreateFromYawPitchRoll( m_Rotation.y, m_Rotation.x, m_Rotation.z);
	Matrix t = Matrix::CreateTranslation( m_Position.x, m_Position.y, m_Position.z);
	Matrix s = Matrix::CreateScale( m_Scale.x, m_Scale.y, m_Scale.z);

	Matrix worldmtx;
	worldmtx = s * r * t;
	Renderer::SetWorldMatrix(&worldmtx); // GPUにセット

	// 描画の処理
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();

	// トポロジーをセット（プリミティブタイプ）
	//devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();

	m_Texture.SetGPU();

	devicecontext->DrawIndexed(
		//5,							// 描画するインデックス数（四角形なんで４）
		//36,							// 描画するインデックス数
		36,							// 描画するインデックス数
		0,							// 最初のインデックスバッファの位置
		0);
}

//=======================================
//終了処理
//=======================================
void TestCube::Uninit()
{

}