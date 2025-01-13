#include "Renderer.h"
#include "Camera.h"
#include "Application.h"
#include "input.h"
#include "Game.h"
#include "GolfBall.h"

using namespace DirectX::SimpleMath;
using namespace std;


//=======================================
//����������
//=======================================
void Camera::Init()
{
	m_Position = Vector3(0.0f, 5.0f, -50.0f);
	m_Target = Vector3(0.0f, 0.0f, 0.0f);
	m_CameraDirection = 3.14f;
}


//=======================================
//�X�V����
//=======================================
void Camera::Update()
{
	//�S���t�{�[���̈ʒu���擾
	//vector<GolfBall*> ballpt = Game::GetInstance()->GetObjects<GolfBall>();
	//if (ballpt.size() > 0) {
	//	Vector3 ballPos = ballpt[0]->GetPosition();

	//	//�J�����̈ʒu���X�V
	//	/*m_Position.x = ballPos.x + sin(m_CameraDirection) * 50;
	//	m_Position.y = ballPos.y + 20;
	//	m_Position.z = ballPos.z + cos(m_CameraDirection) * 50;*/

	//	/*m_Position.x = ballPos.x;
	//	m_Position.y = ballPos.y + 1.0f;
	//	m_Position.z = ballPos.z;*/

	//	float distance = 10.0f; // �J�����̃{�[������̋���
	//	m_Position.x = ballPos.x - ballpt[0]->Getforward().x * distance;
	//	m_Position.y = ballPos.y + 5.0f; // �����������グ��
	//	m_Position.z = ballPos.z - ballpt[0]->Getforward().z * distance;


	//	//�J�����̒����_���X�V
	//	m_Target = ballPos + ballpt[0]->Getforward();
	//}

	if (cameraState == 0) {
		vector<GolfBall*> ballpt = Game::GetInstance()->GetObjects<GolfBall>();
		if (ballpt.size() > 0) {
			Vector3 ballPos = ballpt[0]->GetPosition();

			float distance = 10.0f; 
			m_Position.x = ballPos.x - ballpt[0]->Getforward().x * distance;
			m_Position.y = ballPos.y + 2.5f; 
			m_Position.z = ballPos.z - ballpt[0]->Getforward().z * distance;


			
			m_Target = ballPos + ballpt[0]->Getforward();
		}
	}
	
	if (cameraState == 1) {
		//if (posLapse.size() < 200) {
		//	vector<GolfBall*> ballpt = Game::GetInstance()->GetObjects<GolfBall>();
		//	posLapse.emplace_back(ballpt[0]->GetPosition());
		
		//	DirectX::SimpleMath::Vector3 forward = -ballpt[0]->Getforward();

		//	DirectX::SimpleMath::Matrix lookAtMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(
		//		DirectX::SimpleMath::Vector3::Zero,  
		//		forward,                            
		//		DirectX::SimpleMath::Vector3::UnitY 
		//	);

		//	DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(lookAtMatrix);
		//	rotLapse.emplace_back(rotation);
		//}
		//else if (posLapse.size() >= 200) {
		//	cameraState = 2;
		//}
	}
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
//�`�揈��
//=======================================
void Camera::Draw()
{

}


//=======================================
//�I������
//=======================================
void Camera::Uninit()
{
	
}

//=======================================
//�I������
//=======================================
void Camera::SetCamera(int mode) {
	//3D
	if (mode == 0) {

		// �r���[�ϊ����쐬
		Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
		m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up); // ����n�ɂ����@20230511 by suzuki.tomoki
		// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
		// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
		// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
		// m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);					

		Renderer::SetViewMatrix(&m_ViewMatrix);

		//�v���W�F�N�V�����s��̐���
		constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);    // ����p

		float aspectRatio = static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());	// �A�X�y�N�g��	
		float nearPlane = 1.0f;       // �j�A�N���b�v
		float farPlane = 1000.0f;      // �t�@�[�N���b�v

		//�v���W�F�N�V�����s��̐���
		Matrix projectionMatrix;
		projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);	// ����n�ɂ����@20230511 by suzuki.tomoki
		// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
		// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
		// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
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

		//�v���W�F�N�V�����s�񐶐�
		float nearPlane = 1.0f;	//�j�A�N���b�v
		float farPlane = 1000.0f;	//�t�@�[�N���b�v
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