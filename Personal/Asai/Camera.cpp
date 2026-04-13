#include "Camera.h"
#include"../Utility/Transform.h"
#include"../../Utility/Game.h"

#include<DxLib.h>

namespace {

	//カメラの補間
	constexpr float kFollowLatency = 0.1f;

}

Camera::Camera():
	m_state(),
	m_transform(),
	m_worldScreen(-1)
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

	default:

		break;
	}

}

void Camera::Draw()
{

	printfDx("Camera x %f\n", m_transform.position.x);
	printfDx("Camera y %f\n", m_transform.position.y);
	printfDx("Camera z %f\n", m_transform.position.z);

	DrawRectGraph(
		0, 0,
		m_transform.position.x - Game::kScreenWidth / 2,
		m_transform.position.y - Game::kScreenHeight / 2,
		Game::kScreenWidth, Game::kScreenHeight,
		m_worldScreen, FALSE
	);

}

void Camera::End()
{

	//作成したワールドスクリーンを削除
	DeleteGraph(m_worldScreen);

}

void Camera::UpdateFollow(Transform cameraPos)
{
	//カメラの移動
	m_transform.position = (cameraPos.position - m_transform.position) * kFollowLatency + m_transform.position;

}
