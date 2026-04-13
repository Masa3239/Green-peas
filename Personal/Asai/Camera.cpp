#include "Camera.h"
#include"../Utility/Transform.h"
#include"../../Utility/Game.h"

#include<DxLib.h>
#include"../../Utility/Time.h"
#include"../../Utility/MyRandom.h"

namespace {

	//カメラの補間
	constexpr float kFollowLatency = 0.1f;
	//振動の大きさ
	constexpr float kShakeMoveMargin = 3;

}

Camera::Camera():
	m_state(),
	m_transform(),
	m_worldScreen(-1),
	m_shakeDuration(0)
{
}

Camera::~Camera()
{
}

void Camera::Init()
{

	//仮
	m_worldScreen = MakeScreen(5000, 5000, FALSE);

}

void Camera::Update(Transform cameraPos)
{

	switch (m_state)
	{

	case Camera::State::Follow:
		UpdateFollow(cameraPos);
		break;

	case Camera::State::Damege:
		UpdateDamege(cameraPos);
		break;

	default:

		break;
	}

}

void Camera::Draw()
{

	DrawRectGraph(
		0, 0,
		m_transform.position.x - Game::kScreenWidth / 2,
		m_transform.position.y - Game::kScreenHeight / 2,
		Game::kScreenWidth, Game::kScreenHeight,
		m_worldScreen, FALSE
	);

}

void Camera::DebugDraw()
{

	printfDx("Camera x %f\n", m_transform.position.x);
	printfDx("Camera y %f\n", m_transform.position.y);
	printfDx("Camera z %f\n", m_transform.position.z);

	printfDx("Camera m_state %d\n", static_cast<int>(m_state));

}

void Camera::End()
{

	//作成したワールドスクリーンを削除
	DeleteGraph(m_worldScreen);

}

void Camera::StartDamage(float shakeDuration)
{
	//振動時間をセット
	m_shakeDuration = shakeDuration;
	//ステータスを変更
	m_state = State::Damege;

}

void Camera::UpdateFollow(Transform cameraPos)
{
	//カメラの移動
	m_transform.position = (cameraPos.position - m_transform.position) * kFollowLatency + m_transform.position;

}

void Camera::UpdateDamege(Transform cameraPos)
{

	//カメラの移動
	m_transform.position = (cameraPos.position - m_transform.position) * kFollowLatency + m_transform.position;

	int direction = MyRandom::Int(0, 3);

	switch (direction)
	{

	case 0:

		m_transform.position.x -= kShakeMoveMargin;

		break;

	case 1:

		m_transform.position.x += kShakeMoveMargin;

		break;

	case 2:

		m_transform.position.y -= kShakeMoveMargin;

		break;

	case 3:

		m_transform.position.y += kShakeMoveMargin;

		break;

	}

	//タイマーを減らす
	m_shakeDuration -= Time::GetInstance().GetDeltaTime();
	//時間になったら
	if (m_shakeDuration < 0) {
		//タイマーをリセット
		m_shakeDuration = 0;
		//ステータスを変更
		m_state = State::Follow;

	}

}
