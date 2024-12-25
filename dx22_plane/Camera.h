#pragma once
//#include <vector>
#include	<SimpleMath.h>

//-----------------------------------------------------------------------------
//CameraƒNƒ‰ƒX
//-----------------------------------------------------------------------------
class Camera {
private:
	DirectX::SimpleMath::Vector3	m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3	m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3	m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	DirectX::SimpleMath::Vector3	m_Target{};
	DirectX::SimpleMath::Matrix		m_ViewMatrix{};

	float m_CameraDirection = 0;	//ƒJƒƒ‰‚Ì•ûŒü

	int cameraState = 0;

	std::vector<DirectX::SimpleMath::Vector3> posLapse;
	std::vector<DirectX::SimpleMath::Vector3> rotLapse;

public:

	void Init();
	void Update();
	void Draw();
	void Uninit();

	void SetCamera(int mode);
	int GetCameraState();
	void SetCameraState(int state);
};