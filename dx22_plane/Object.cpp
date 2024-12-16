#include "Object.h"

using namespace DirectX::SimpleMath;

//コンストラクタ
Object::Object(Camera* cam) : m_Camera(cam) {

}

//デストラクタ
Object::~Object(){

}


void Object::SetPosition(const Vector3& pos) {
	m_Position.x = pos.x;
	m_Position.x = pos.y;
	m_Position.x = pos.z;
}

Vector3 Object::GetPosition() const {
	return m_Position;
}