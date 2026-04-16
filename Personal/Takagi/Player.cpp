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
#include"../../Object/GameObject.h"
#include"../../System/ObjectManager.h"
#include"Weapon.h"
#include"Sword.h"

namespace {
	// ゲージの種類をキャスト(いちいちキャストするのが面倒なので用意)
	//constexpr int kHpNum = static_cast<int>(Hp);
	//constexpr int kStaminaNum = static_cast<int>(Stamina);
	//constexpr int kAngerNum = static_cast<int>(Anger);
	
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
	// プレイヤー画像のグラフィックハンドル
	const char* const kGraphPath = "Personal\\Takagi\\Resource\\pipo-charachip_otaku01.png";
	constexpr float kPlayerScale = 1.5f;
}

Player::Player(ObjectManager* objManager) :
	GameObject(objManager),
	m_directionX(1),
	m_speed (kMoveSpeed),
	m_accel(1),
	m_deltaTime(0)
{
	GetTransform().position = {300,300,0};
	m_camera = new Camera();
	m_camera->Init();
	for (auto& gauge : m_gauges) {
		gauge = std::make_unique<Gauge>();
	}
	m_gauges[Anger]->Reset(Gauge::Min);

	m_box = Collision::AABB(GetTransform().position, kBoxSize);
	m_circle = Collision::Circle(GetTransform().position, kCircleSize);

	//for (auto& weapon : m_weapons) {
	//	weapon = nullptr;
	//}
	m_weapons = new Sword(objManager);
	m_weapons->Init();
	for (int i = 0;i < static_cast<int>(Pad::Direction::Max);i++) {
		for (int& handle : m_graphHandle[i])
			handle = -1;
	}
	int graph[12];
	LoadDivGraph(kGraphPath, 12, 3, 4, 32, 32, graph);
	int num = 0;
	for (int i = 0;i < static_cast<int>(Pad::Direction::Max);i++) {
		for (int j = 0;j < 3;j++) {
			m_graphHandle[i][j] = graph[num];
		num++;
		}
	}
	m_direction = Pad::Direction::Front;

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
	m_weapons->End();
}

void Player::Update()
{
	m_camera->Update(GetTransform());
	m_deltaTime = Time::GetInstance().GetDeltaTime();
	// 時間が止まっていなければ移動処理を呼ぶ
	if (Time::GetInstance().GetDeltaTime()) {
		Move();
	}
	m_box.SetPosition(GetTransform().position);
	m_circle.SetPosition(GetTransform().position);
	printfDx("deltatime : %f\n", m_deltaTime);
	printfDx("移動量 : %f\n", m_moveVector.GetLength());
		Time::GetInstance().SetTimeScale(1);
	
	if (Pad::IsDown(Pad::Button::LB)) {
	}

	printfDx("m_direction : %d\n", static_cast<int>(m_direction));
}

void Player::Move()
{

	MoveAmount();
	SpeedUpdate();

	// 座標の移動
	GetTransform().position += m_moveVector;
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
		GetTransform().rotation.y = angle * MyMath::ToRadian;

		m_gauges[Stamina]->Increase(kStaminaHealValue * m_deltaTime);
		if (angle > 0) {
			m_directionX = 1;
		}
		else
		{
			m_directionX = -1;
		}
		m_weapons->GetTransform().rotation.y = GetTransform().rotation.y;
	}
	// 武器の座標を設定
	m_weapons->GetTransform().position = GetTransform().position ;
	// 武器の更新処理
	m_weapons->Update();
	
	if (Pad::IsPressed(Pad::Button::Y)) {
		m_weapons->Attack();
	}

	printfDx("m_direction : %d\n",m_directionX);
	// 移動量の初期化
	m_moveVector = { 0,0,0 };
	// 入力角度からX,Y方向の移動量を計算
	m_moveVector.x = sinf(GetTransform().rotation.y);
	m_moveVector.y = -cosf(GetTransform().rotation.y);
	// 正規化
	m_moveVector = m_moveVector.GetNormalize();
	// 移動速度を求める(入力量×移動速度×速度割合×時間)
	float moveSpeed = inputAmount * m_speed * m_accel * Time::GetInstance().GetDeltaTime();
	// プレイヤーの移動量に入力量と移動速度と時間をかける
	m_moveVector *= moveSpeed;

	if (inputAmount) {
		m_direction = Pad::AnalogDirection(Pad::Joystick::Left);
	}

}

void Player::SpeedUpdate()
{
	// ダッシュしていないとき
	if (Pad::IsPressed(Pad::Button::A)&& CheckCanDash()) {
		m_accel = kDashSpeed;
		m_gauges[Stamina]->Decrease(kDashStaimina);
	}
	if (CheckDashNow()) {
		m_accel -= kDeccel * m_deltaTime;
		m_accel = MyMath::Clamp(m_accel, 1.0f, 100.0f);
	}
}

void Player::Draw()
{
	m_weapons->Draw();
	// プレイヤー・カメラが移動していることがわかるよう一定の位置に円を描画
	DrawCircle(600, 400, 10, GetColor(0, 0, 255));
	// プレイヤー座標に円を描画
	DrawCircle(GetTransform().position.x, GetTransform().position.y, 30, GetColor(100, 100, 100));
	DrawCircle(GetTransform().position.x, GetTransform().position.y, 10, GetColor(255, 0, 0));
	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y, kPlayerScale, 0, m_graphHandle[static_cast<int>(m_direction)][0], TRUE);
	// 現在向いている方向のデバッグ表示
	Vector3 angle = { 0,0,0 };
	angle.x = sinf(GetTransform().rotation.y);
	angle.y = -cosf(GetTransform().rotation.y);
	angle = angle.GetNormalize();
	angle *= 10;
	angle += GetTransform().position;
	DrawCircle(angle.x, angle.y, 3, GetColor(0, 255, 0));
	Debug();
	printfDx("x : %f\n", GetTransform().position.x);
	printfDx("y : %f\n", GetTransform().position.y);
	printfDx("z : %f\n", GetTransform().position.z);
	printfDx("ni : %d\n", static_cast<int>(Pad::AnalogDirection(Pad::Joystick::Left)));
}

void Player::Debug()
{
	if (Pad::IsPressed(Pad::Button::X)) {
		Damage(5);
	}
	printfDx("現在HP       : %f\n", m_gauges[Hp]->GetValue(Gauge::Current));
	printfDx("最大HP       : %f\n", m_gauges[Hp]->GetValue(Gauge::Max));
	printfDx("最小HP       : %f\n", m_gauges[Hp]->GetValue(Gauge::Min));
	printfDx("割合HP       : %f\n", GetGaugeRate(Hp));
	printfDx("現在スタミナ : %f\n", m_gauges[Stamina]->GetValue(Gauge::Current));
	printfDx("最大スタミナ : %f\n", m_gauges[Stamina]->GetValue(Gauge::Max));
	printfDx("最小スタミナ : %f\n", m_gauges[Stamina]->GetValue(Gauge::Min));
	printfDx("割合スタミナ : %f\n", GetGaugeRate(Stamina));
	printfDx("現在怒り     : %f\n", m_gauges[Anger]->GetValue(Gauge::Current));
	printfDx("最大怒り     : %f\n", m_gauges[Anger]->GetValue(Gauge::Max));
	printfDx("最小怒り     : %f\n", m_gauges[Anger]->GetValue(Gauge::Min));
	printfDx("割合怒り     : %f\n", GetGaugeRate(Anger));
	m_box.DebugDraw();
	m_circle.DebugDraw();
}

void Player::Damage(float damage)
{
	if (CheckDashNow())return;
	m_gauges[Hp]->Decrease(damage);
	m_gauges[Anger]->Increase(damage * kAngerValue);
}

bool Player::IsDead()
{
	return !m_gauges[Hp]->GetValue();
}

float Player::GetGaugeCurrentValue(int gauge)
{
	return m_gauges[static_cast<int>(gauge)]->GetValue(Gauge::Current);
}

float Player::GetGaugeMaxValue(int gauge)
{
	return m_gauges[static_cast<int>(gauge)]->GetValue(Gauge::Max);
}

float Player::GetGaugeRate(int gauge)
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
	canDash = m_gauges[Stamina]->CheckValue(kDashStaimina);
	return canDash;
}

bool Player::CheckDashNow()
{
	return m_accel > 1;
}
