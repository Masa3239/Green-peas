#include "Camera.h"
#include"../Utility/Transform.h"
#include"../../Utility/Game.h"

#include<DxLib.h>
#include"../../Utility/Time.h"
#include"../../Utility/MyRandom.h"

#include"../Kimura/Map/Map.h"
#include"../Kimura/Map/MapManager.h"

namespace {

	//カメラの補間
	constexpr float kFollowLatency = 3.0f;
	//振動の大きさ
	constexpr float kShakeMoveMargin = 3;
	//怒り状態でのカメラの振動
	constexpr float kAngerShakeAmount = 1.0f;

}

Camera::Camera():
	m_state(CameraState::Type::Follow),
	m_transform(),
	m_worldScreen(-1),
	m_pMap(nullptr),
	m_shakeDuration(0),
	m_worldScreenLeft(0),
	m_worldScreenRight(0),
	m_worldScreenTop(0),
	m_worldScreenBottom(0)
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
}

void Camera::Update(Transform cameraPos)
{

	switch (m_state)
	{

	case CameraState::Type::Follow:
		UpdateFollow(cameraPos);
		break;

	case CameraState::Type::Damage:
		UpdateDamage(cameraPos);
		break;

	case CameraState::Type::Anger:
		UpdateAnger(cameraPos);
		break;

	default:

		break;
	}

	//画面の外を写さない
	KeepInWorldScreen();

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
	//printfDx("Camera z %f\n", m_transform.position.z);

	//printfDx("%d\n", m_worldScreen);

	printfDx("Camera m_state %d\n", static_cast<int>(m_state));

}

void Camera::End()
{

	//作成したワールドスクリーンを削除
	DeleteGraph(m_worldScreen);

	m_pMap = nullptr;

}

void Camera::StartDamage(float shakeDuration)
{
	//振動時間をセット
	m_shakeDuration = shakeDuration;
	//ステータスを変更
	m_state = CameraState::Type::Damage;

}

void Camera::GenerateWorldScreen()
{

	if (m_pMap == nullptr) {

		//ワールドスクリーンを作成
		m_worldScreen = MakeScreen(10000, 10000, TRUE);
		return;
	}

	//ワールドスクリーンを作成
	m_worldScreen = MakeScreen(m_pMap->GetMapBlockNumX() * kMapBlockSize, m_pMap->GetMapBlockNumY() * kMapBlockSize, TRUE);

	//ワールドスクリーンの左端の座標を設定する
	m_worldScreenLeft = 0;
	//ワールドスクリーンの右端の座標を設定する
	m_worldScreenRight = m_pMap->GetMapBlockNumX() * kMapBlockSize;
	//ワールドスクリーンの上端の座標を設定する
	m_worldScreenTop = 0;
	//ワールドスクリーンの下端の座標を設定する
	m_worldScreenBottom = m_pMap->GetMapBlockNumY() * kMapBlockSize;

}

void Camera::Lerp(Transform cameraPos)
{

	//カメラの移動
	m_transform.position = (cameraPos.position - m_transform.position) * kFollowLatency * Time::GetInstance().GetDeltaTime() + m_transform.position;

}

void Camera::UpdateFollow(Transform cameraPos)
{

	//カメラの移動
	Lerp(cameraPos);

}

void Camera::UpdateDamage(Transform cameraPos)
{

	//カメラの移動
	//m_transform.position = (cameraPos.position - m_transform.position) * kFollowLatency + m_transform.position;
	//m_transform.position = (cameraPos.position - m_transform.position) * kFollowLatency * Time::GetInstance().GetDeltaTime() + m_transform.position;
	Lerp(cameraPos);

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
		m_state = CameraState::Type::Follow;

	}

}

void Camera::UpdateAnger(Transform cameraPos)
{

	//カメラの移動
	Lerp(cameraPos);

	int direction = MyRandom::Int(0, 3);

	switch (direction)
	{

	case 0:

		m_transform.position.x -= kAngerShakeAmount;

		break;

	case 1:

		m_transform.position.x += kAngerShakeAmount;

		break;

	case 2:

		m_transform.position.y -= kAngerShakeAmount;

		break;

	case 3:

		m_transform.position.y += kAngerShakeAmount;

		break;

	}

}

void Camera::KeepInWorldScreen()
{

	//ワールドスクリーンの左端を描画していたら
	if (m_transform.position.x - Game::kScreenWidth / 2 < m_worldScreenLeft) {
		//ワールドスクリーンの左端を描画しないようにする
		m_transform.position.x = m_worldScreenLeft + Game::kScreenWidth / 2;

	}
	//ワールドスクリーンの右端を描画していたら
	if (m_transform.position.x + Game::kScreenWidth / 2 > m_worldScreenRight) {
		//ワールドスクリーンの右端を描画しないようにする
		m_transform.position.x = m_worldScreenRight - Game::kScreenWidth / 2;

	}
	//ワールドスクリーンの上端を描画していたら
	if (m_transform.position.y - Game::kScreenHeight / 2 < m_worldScreenTop) {
		//ワールドスクリーンの上端を描画しないようにする
		m_transform.position.y = m_worldScreenTop + Game::kScreenHeight / 2;

	}
	//ワールドスクリーンの下端を描画していたら
	if (m_transform.position.y + Game::kScreenHeight / 2 > m_worldScreenBottom) {
		//ワールドスクリーンの下端を描画しないようにする
		m_transform.position.y = m_worldScreenBottom - Game::kScreenHeight / 2;

	}

}
