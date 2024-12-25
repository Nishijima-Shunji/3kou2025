#include "Renderer.h"
#include "Camera.h"
#include "Application.h"
#include "input.h"
#include "Game.h"
#include "GolfBall.h"

using namespace DirectX::SimpleMath;
using namespace std;


//=======================================
//初期化処理
//=======================================
void Camera::Init()
{
	m_Position = Vector3(0.0f, 20.0f, -50.0f);
	m_Target = Vector3(0.0f, 0.0f, 0.0f);
	m_CameraDirection = 3.14f;
}


//=======================================
//更新処理
//=======================================
void Camera::Update()
{
	// カメラ追従
	if (cameraState == 0) {
		//ゴルフボールの位置を取得
		vector<GolfBall*> ballpt = Game::GetInstance()->GetObjects<GolfBall>();
		if (ballpt.size() > 0) {
			Vector3 ballPos = ballpt[0]->GetPosition();

			float distance = 10.0f; // カメラのボールからの距離
			m_Position.x = ballPos.x - ballpt[0]->Getforward().x * distance;
			m_Position.y = ballPos.y + 5.0f; // 高さを少し上げる
			m_Position.z = ballPos.z - ballpt[0]->Getforward().z * distance;


			//カメラの注視点を更新
			m_Target = ballPos + ballpt[0]->Getforward();
		}
	}
	// 固定カメラ
	if (cameraState == 1) {
		//if (posLapse.size() < 200) {
		//	vector<GolfBall*> ballpt = Game::GetInstance()->GetObjects<GolfBall>();
		//	posLapse.emplace_back(ballpt[0]->GetPosition());
		//	// ボールの forward を取得
		//	DirectX::SimpleMath::Vector3 forward = -ballpt[0]->Getforward();

		//	// カメラの回転を forward に基づいて計算
		//	DirectX::SimpleMath::Matrix lookAtMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(
		//		DirectX::SimpleMath::Vector3::Zero,  // 視点の原点
		//		forward,                             // 進行方向
		//		DirectX::SimpleMath::Vector3::UnitY // 上方向
		//	);

		//	// 回転をクォータニオンとして保存
		//	DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(lookAtMatrix);
		//	rotLapse.emplace_back(rotation);
		//}
		//else if (posLapse.size() >= 200) {
		//	cameraState = 2;
		//}
	}
	// カメラ戻る
	if (cameraState == 2) {
		/*if (!posLapse.empty()) {
			m_Position = posLapse[0];
			m_Rotation = rotLapse[0];
			posLapse.erase(posLapse.begin());
			rotLapse.erase(rotLapse.begin());
		}
		else {
			cameraState = 0;
		}*/
	}

}

//=======================================
//描画処理
//=======================================
void Camera::Draw()
{

}


//=======================================
//終了処理
//=======================================
void Camera::Uninit()
{

}

//=======================================
//終了処理
//=======================================
void Camera::SetCamera(int mode) {
	//3D
	if (mode == 0) {

		// ビュー変換後列作成
		Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
		m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up); // 左手系にした　20230511 by suzuki.tomoki
		// DIRECTXTKのメソッドは右手系　20230511 by suzuki.tomoki
		// 右手系にすると３角形頂点が反時計回りになるので描画されなくなるので注意
		// このコードは確認テストのために残す
		// m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);					

		Renderer::SetViewMatrix(&m_ViewMatrix);

		//プロジェクション行列の生成
		constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);    // 視野角

		float aspectRatio = static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());	// アスペクト比	
		float nearPlane = 1.0f;       // ニアクリップ
		float farPlane = 1000.0f;      // ファークリップ

		//プロジェクション行列の生成
		Matrix projectionMatrix;
		projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);	// 左手系にした　20230511 by suzuki.tomoki
		// DIRECTXTKのメソッドは右手系　20230511 by suzuki.tomoki
		// 右手系にすると３角形頂点が反時計回りになるので描画されなくなるので注意
		// このコードは確認テストのために残す
		// projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);

		Renderer::SetProjectionMatrix(&projectionMatrix);
	}

	//2D
	else if (mode == 1) {
		Vector3 pos = { 0.0f, 0.0f, -10.0f };
		Vector3 tgt = { 0.0f, 0.0f, 1.0f };
		Vector3 up = { 0.0f, 1.0f, 0.0f };
		m_ViewMatrix = DirectX::XMMatrixLookAtLH(pos, tgt, up);
		Renderer::SetViewMatrix(&m_ViewMatrix);

		//プロジェクション行列生成
		float nearPlane = 1.0f;	//ニアクリップ
		float farPlane = 1000.0f;	//ファークリップ
		Matrix projectionMatrix = DirectX::XMMatrixOrthographicLH(static_cast<float>(Application::GetWidth()), static_cast<float>(Application::GetHeight()), nearPlane, farPlane);
		projectionMatrix = DirectX::XMMatrixTranspose(projectionMatrix);
		Renderer::SetProjectionMatrix(&projectionMatrix);
	}
}

int Camera::GetCameraState() {
	return cameraState;
}

void Camera::SetCameraState(int state) {
	cameraState = state;
}

