#include<DxLib.h>
#include "Player.h"
#include"../Utility/Transform.h"
#include"../Utility/Vector3.h"
#include"../System/InputPad.h"
#include<math.h>


Player::Player()
{
	m_transform.position = { 300,300,0 };
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::End()
{
}

void Player::Update()
{
	Move();
}

void Player::Move()
{
	// 入力量を取得
	float inputAmount = Pad::PadAnalogAmount(Pad::Joystick::Left);
	printfDx("入力量 : %f\n", inputAmount);
	// 入力されていなければ処理しない
	if (!inputAmount)return;
	// スティック入力の角度
	float angle = Pad::AnalogAngle(Pad::Joystick::Left);
	// 移動量の初期化
	m_moveVector = { 0,0,0 };
	// 入力角度からX,Y方向の移動量を計算
	m_moveVector.x = sinf(angle);
	m_moveVector.y = -cosf(angle);

	// 正規化
	m_moveVector = m_moveVector.GetNormalize();
	// プレイヤーの移動速度をかける
	m_moveVector *= inputAmount;
	m_transform.position += m_moveVector;
}

void Player::Draw()
{
	DrawCircle(m_transform.position.x, m_transform.position.y, 10, GetColor(255, 0, 0));
}
