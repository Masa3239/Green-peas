#include<DxLib.h>
#include "Player.h"
#include"Gauge.h"
#include"../Utility/Transform.h"
#include"../Utility/Vector3.h"
#include"../Utility/Time.h"
#include"../System/InputPad.h"
#include<math.h>
#include<memory>
#include"../Asai/Camera.h"
#include"../Chara/Collision.h"

namespace {
	// ゲージの種類をキャスト(いちいちキャストするのが面倒なので用意)
	constexpr int kHpNum = static_cast<int>(GaugeType::Hp);
	constexpr int kStaminaNum = static_cast<int>(GaugeType::Stamina);
	constexpr int kAngerNum = static_cast<int>(GaugeType::Anger);
	
	// 通常の移動速度
	constexpr float kMoveSpeed = 100.0f;
	// ダッシュの移動速度
	constexpr float kDashSpeed = 15.0f;
	// ダッシュの減速量
	constexpr float kDeccel = kDashSpeed * 5.0f;
	// ダッシュ時のスタミナ消費量
	constexpr float kDashStaimina = 30;
	// スタミナの自動回復量
	constexpr float kStaminaHealValue = 10;
	// 怒りゲージの上昇倍率
	constexpr float kAngerValue = 2.0f;
	// 四角の当たり判定の大きさ
	constexpr Vector3 kBoxSize = { 30,70,0 };
	// 円の当たり判定の大きさ
	constexpr float kCircleSize = 15;
}

Player::Player() :
	m_direction(1),
	m_speed (kMoveSpeed),
	m_accel(1),
	m_deltaTime(0)
{
	m_transform.position = { 300,300,0 };
	m_camera = new Camera();
	m_camera->Init();
	for (auto& gauge : m_gauges) {
		gauge = std::make_unique<Gauge>();
	}
	m_gauges[kAngerNum]->Reset(Gauge::Min);

	m_box = Collision::AABB(m_transform.position, kBoxSize);
	m_circle = Collision::Circle(m_transform.position, kCircleSize);
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
	m_box.SetPosition(m_transform.position);
	m_circle.SetPosition(m_transform.position);
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
	// ダッシュ中なら
	if (CheckDashNow()) {
	}
	else {
		// スティック入力の角度
		float angle = Pad::AnalogAngle(Pad::Joystick::Left);
		// 向いている方向を更新
		m_transform.rotation.y = angle * MyMath::ToRadian;

		m_gauges[kStaminaNum]->Increase(kStaminaHealValue * m_deltaTime);
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
	// ダッシュしていないとき
	if (Pad::IsPressed(Pad::Button::A)&& CheckCanDash()) {
		m_accel = kDashSpeed;
		m_gauges[kStaminaNum]->Decrease(kDashStaimina);
	}
	if (CheckDashNow()) {
		m_accel -= kDeccel * m_deltaTime;
		m_accel = MyMath::Clamp(m_accel, 1.0f, 100.0f);
	}
}

void Player::Draw()
{
	// プレイヤー・カメラが移動していることがわかるよう一定の位置に円を描画
	DrawCircle(600, 400, 10, GetColor(0, 0, 255));
	// プレイヤー座標に円を描画
	DrawCircle(m_transform.position.x, m_transform.position.y, 30, GetColor(100, 100, 100));
	DrawCircle(m_transform.position.x, m_transform.position.y, 10, GetColor(255, 0, 0));

	// 現在向いている方向のデバッグ表示
	Vector3 angle = { 0,0,0 };
	angle.x = sinf(m_transform.rotation.y);
	angle.y = -cosf(m_transform.rotation.y);
	angle = angle.GetNormalize();
	angle *= 10;
	angle += m_transform.position;
	DrawCircle(angle.x, angle.y, 3, GetColor(0, 255, 0));
	Debug();
}

void Player::Debug()
{
	if (Pad::IsPressed(Pad::Button::X)) {
		Damage(5);
	}
	printfDx("現在HP       : %f\n", m_gauges[kHpNum]->GetValue(Gauge::Current));
	printfDx("最大HP       : %f\n", m_gauges[kHpNum]->GetValue(Gauge::Max));
	printfDx("最小HP       : %f\n", m_gauges[kHpNum]->GetValue(Gauge::Min));
	printfDx("割合HP       : %f\n", GetGaugeRate(GaugeType::Hp));
	printfDx("現在スタミナ : %f\n", m_gauges[kStaminaNum]->GetValue(Gauge::Current));
	printfDx("最大スタミナ : %f\n", m_gauges[kStaminaNum]->GetValue(Gauge::Max));
	printfDx("最小スタミナ : %f\n", m_gauges[kStaminaNum]->GetValue(Gauge::Min));
	printfDx("割合スタミナ : %f\n", GetGaugeRate(GaugeType::Stamina));
	printfDx("現在怒り     : %f\n", m_gauges[kAngerNum]->GetValue(Gauge::Current));
	printfDx("最大怒り     : %f\n", m_gauges[kAngerNum]->GetValue(Gauge::Max));
	printfDx("最小怒り     : %f\n", m_gauges[kAngerNum]->GetValue(Gauge::Min));
	printfDx("割合怒り     : %f\n", GetGaugeRate(GaugeType::Anger));
	m_box.DebugDraw();
	m_circle.DebugDraw();
}

void Player::Damage(float damage)
{
	if (CheckDashNow())return;
	m_gauges[kHpNum]->Decrease(damage);
	m_gauges[kAngerNum]->Increase(damage * kAngerValue);
}

bool Player::IsDead()
{
	return !m_gauges[kHpNum]->GetValue();
}

float Player::GetGaugeCurrentValue(GaugeType gauge)
{
	return m_gauges[static_cast<int>(gauge)]->GetValue(Gauge::Current);
}

float Player::GetGaugeMaxValue(GaugeType gauge)
{
	return m_gauges[static_cast<int>(gauge)]->GetValue(Gauge::Max);
}

float Player::GetGaugeRate(GaugeType gauge)
{
	return m_gauges[static_cast<int>(gauge)]->GetRate();
}

bool Player::CheckCanDash()
{
	// ダッシュ可能かどうかを調べる
	// ダッシュ中ならfalse
	if (CheckDashNow())return false;
	bool canDash = false;
	// 現在のスタミナがダッシュ時の消費スタミナより多いかどうか調べる
	canDash = m_gauges[kStaminaNum]->CheckValue(kDashStaimina);
	return canDash;
}

bool Player::CheckDashNow()
{
	return m_accel > 1;
}
