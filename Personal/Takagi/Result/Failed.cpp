#include "Failed.h"
#include"../../../Utility/Game.h"
#include"../../../Utility/Time.h"
#include"../../../Utility/MyMath.h"
#include"../../../System/InputManager.h"
namespace
{
	// スクリーンの中心座標
	constexpr Vector3 kScreenHalf = { Game::kScreenWidth * 0.5f,Game::kScreenHeight * 0.5f,0 };
	// 画像の大きさが1となるZ座標
	constexpr float kDefaoultPosZ = 100;
	// 初期座標
	constexpr Vector3 kInitPos = { kScreenHalf.x,Game::kScreenWidth + 400,kDefaoultPosZ * 2 };
	constexpr Vector3 kEndPos = { kScreenHalf.x,kScreenHalf.y - 200,kDefaoultPosZ * 0.25f };
	const char* const kGraphPath = "Resource\\Result\\FAILED.png";
	constexpr float kRotateSpeed = -1440 * MyMath::ToRadian;
	constexpr Vector3 kSpeed{ 0,-1000 ,-100 };
	constexpr float kFinishRad = -10 * MyMath::ToRadian;
	constexpr float kInteval = 1.5f;
}

Failed::Failed():
	m_phase(0),
	m_interval(0)
{
	m_graphHandle = LoadGraph(kGraphPath);
	m_transform.position = kInitPos;
	m_isFinish = false;
}

Failed::~Failed()
{
}

void Failed::Init()
{
}

void Failed::End()
{
}

void Failed::Update()
{
	bool skip = InputManager::GetInstance().IsPressed(Input::Action::Confirm);
	if (skip) {
		m_phase = Max;
		m_transform.rotation.z = kFinishRad;
		m_transform.position = kEndPos;
		m_isFinish = true;
		return;
	}
	float time = Time::GetInstance().GetUnscaledDeltaTime();
	if (m_phase < Stop) {
		m_transform.rotation.z += kRotateSpeed * time;
		float angle = m_transform.rotation.z * MyMath::ToDegree;
		m_transform.rotation.z = MyMath::NormalizeAngle(angle) * MyMath::ToRadian;
	}
	switch (m_phase)
	{
	case Up:
		m_transform.position.y += kSpeed.y * time;
		if (m_transform.position.y > kEndPos.y)break;
			m_transform.position.y = kEndPos.y;
			m_phase = Narrow;
		break;
		
	case Narrow:
		m_transform.position.z += kSpeed.z*time;
		if (m_transform.position.z > kEndPos.z)break;
		m_transform.position.z = kEndPos.z;
		m_phase = Stop;
		break;
	case Stop:
		m_transform.rotation.z *= time;
		m_interval += time;
		if (m_interval < kInteval)break;
		m_phase = Max;
		break;
	case Max:
		m_transform.rotation.z += kRotateSpeed * time * 0.1f;
		if (m_transform.rotation.z > kFinishRad)break;
		m_transform.rotation.z = kFinishRad;
		m_isFinish = true;

		break;
	default:
		break;
	}

}

void Failed::Draw()
{
	float scale = m_transform.position.z / kDefaoultPosZ;
	DrawRotaGraph(m_transform.position.x, m_transform.position.y, scale, m_transform.rotation.z, m_graphHandle,TRUE);
}
