#include<DxLib.h>
#include "Player.h"
#include"../Utility/Transform.h"
#include"../Utility/Vector3.h"
#include"../Utility/Time.h"
#include"../System/InputPad.h"
#include<math.h>
#include<memory>
#include"../Asai/Camera.h"

namespace {
	
	constexpr float kMoveSpeed = 100.0f;
	constexpr float kDash = 15.0f;
	constexpr float kDeccel = kDash * 5.0f;
}

Player::Player() :
	m_speed (kMoveSpeed),
	m_accel(1)
{
	m_transform.position = { 300,300,0 };
	m_camera = new Camera();
	m_camera->Init();
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::End()
{
	m_camera->End();
	m_camera = nullptr;
	delete m_camera;
}

void Player::Update()
{
	m_camera->Update(m_transform);
	m_deltaTime = Time::GetInstance().GetDeltaTime();
	// 時間が止まっていなければ移動処理を呼ぶ
	if (Time::GetInstance().GetDeltaTime()) {
		Move();
	}
	printfDx("deltatime : %f\n", m_deltaTime);
	printfDx("移動量 : %f\n", m_moveVector.GetLength());
		Time::GetInstance().SetTimeScale(1);
	
	if (Pad::IsDown(Pad::Button::LB)) {
	}
}

void Player::Move()
{

	MoveAmount();
	SpeedUpdate();

	// 座標の移動
	m_transform.position += m_moveVector;
}

void Player::MoveAmount()
{
	// 入力量を取得
	float inputAmount = Pad::PadAnalogAmount(Pad::Joystick::Left);
	printfDx("入力量 : %f\n", inputAmount);
	// 入力されていなければ処理しない
	if (m_accel <= 1) {

		// スティック入力の角度
		float angle = Pad::AnalogAngle(Pad::Joystick::Left);
		// 向いている方向を更新
		m_transform.rotation.y = angle * MyMath::ToRadian;
	}

	// 移動量の初期化
	m_moveVector = { 0,0,0 };
	// 入力角度からX,Y方向の移動量を計算
	m_moveVector.x = sinf(m_transform.rotation.y);
	m_moveVector.y = -cosf(m_transform.rotation.y);
	// 正規化
	m_moveVector = m_moveVector.GetNormalize();
	// 移動速度を求める(入力量×移動速度×速度割合×時間)
	float moveSpeed = inputAmount * m_speed * m_accel * Time::GetInstance().GetDeltaTime();
	// プレイヤーの移動量に入力量と移動速度と時間をかける
	m_moveVector *= moveSpeed;
}

void Player::SpeedUpdate()
{
	if (Pad::IsPressed(Pad::Button::A)&&m_accel<=1) {
		m_accel = kDash;
	}
	if (m_accel > 1) {
		m_accel -= kDeccel * m_deltaTime;
		m_accel = MyMath::Clamp(m_accel, 1.0f, 100.0f);
	}
}

void Player::Draw()
{
	DrawCircle(600, 400, 10, GetColor(0, 0, 255));
	// プレイヤー座標に円を描画
	DrawCircle(m_transform.position.x, m_transform.position.y, 10, GetColor(255, 0, 0));

	// 現在向いている方向のデバッグ表示
	Vector3 angle = { 0,0,0 };
	angle.x = sinf(m_transform.rotation.y);
	angle.y = -cosf(m_transform.rotation.y);
	angle = angle.GetNormalize();
	angle *= 10;
	angle += m_transform.position;
	DrawCircle(angle.x, angle.y, 3, GetColor(0, 255, 0));
}
