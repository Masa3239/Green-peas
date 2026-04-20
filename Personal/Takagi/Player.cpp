#include<DxLib.h>
#include "Player.h"
#include"Gauge.h"
#include"../Utility/Transform.h"
#include"../Utility/Vector3.h"
#include"../Utility/Time.h"
#include"../System/InputPad.h"
#include<math.h>
#include<memory>
#include<vector>
#include"../Asai/Camera.h"
#include"../Chara/Collision.h"
#include"../../Object/GameObject.h"
#include"../../System/ObjectManager.h"
#include"Weapon.h"
#include"Sword.h"
#include"JpSword.h"
#include"Bow.h"
#include"Boomerang.h"
#include"ExpGauge.h"
#include"../Syoguti/ItemManager.h"
#include"../Syoguti/ItemBase.h"
#include"../Osawa/Enemy/EnemyManager.h"
#include"PlayerStatus.h"
#include"PlayerBuff.h"

namespace {
	// ゲージの種類をキャスト(いちいちキャストするのが面倒なので用意)
	//constexpr int kHpNum = static_cast<int>(Hp);
	//constexpr int kStaminaNum = static_cast<int>(Stamina);
	//constexpr int kAngerNum = static_cast<int>(Anger);
	
	// 通常の移動速度
	constexpr float kMoveSpeed = 20000.0f;
	// ダッシュの移動速度
	constexpr float kDashSpeed = 10.0f;
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
	const char* const kGraphPath = "Resource\\pipo-charachip_otaku01.png";
	// 画像の表示倍率
	constexpr float kPlayerScale = 1.5f;
	// 初期ステータス
	constexpr PlayerStatus kInitStatus = PlayerStatus(1, 100, 1, 0.8f, kMoveSpeed, 100, 10, 2);
	// 成長倍率
	constexpr PlayerStatus kGrowStatus = PlayerStatus(1, 1.05f, 1.1f, 1.1f, 1, 1, 1, 1);
	// 怒り状態時のステータス
	constexpr PlayerStatus kAngerStatus = PlayerStatus(1, 1, 1.5f, 1, 2, 1, 1.5f, 2);
	// 初期座標
	constexpr Vector3 kInitPos = { 300,300,0 };
}

Player::Player(ObjectManager* objManager) :
	GameObject(objManager),
	m_directionX(1),
	m_speed (kMoveSpeed),
	m_accel(1),
	m_deltaTime(0),
	m_angerButton(),
	m_anger(false)
{
	m_angerButton[0] = false;
	m_angerButton[1] = false;
	// 初期座標の設定
	GetTransform().position = kInitPos;
	//m_camera = new Camera();
	//m_camera->Init();

	// 各ゲージの初期化
	for (auto& gauge : m_gauges) {
		gauge = std::make_unique<Gauge>();
	}
	// 経験値ゲージの初期化
	m_gauges[static_cast<int>(GaugeType::Exp)] = std::make_unique<ExpGauge>();
	// 怒りゲージを0に
	m_gauges[static_cast<int>(GaugeType::Anger)]->Reset(Gauge::Value::Min);

	//m_box = Collision::AABB(GetTransform().position, kBoxSize);
	// 円の当たり判定を初期化
	m_circle = Collision::Circle(GetTransform().position, kCircleSize);

	//for (auto& weapon : m_weapons) {
	//	weapon = nullptr;
	//}
	// 初期武器を設定
	
	//m_weapons.push_back(std::make_unique<JpSword>(objManager));
	m_weapons.push_back(std::make_unique<Sword>(objManager));
	m_weapons.push_back(std::make_unique<Boomerang>(objManager));
	//m_weapons.push_back(std::make_unique<Bow>(objManager));

	for (auto& weapons : m_weapons) {
		// 武器に敵マネージャーのポインタを設定
		weapons->SetEnemyManager(m_pEnemyMgr);
		// 武器の初期設定
		weapons->Init();
	}

	for (int i = 0;i < static_cast<int>(MyMath::FourDirection::Max);i++) {
		for (int& handle : m_graphHandle[i])
			handle = -1;
	}
	int graph[12];
	LoadDivGraph(kGraphPath, 12, 3, 4, 32, 32, graph);
	int num = 0;
	for (int i = 0;i < static_cast<int>(MyMath::FourDirection::Max);i++) {
		for (int j = 0;j < 3;j++) {
			m_graphHandle[i][j] = graph[num];
			num++;
		}
	}
	//for (int i = 0;i < static_cast<int>(Status::Max);i++) {
	//}
		m_status = kInitStatus;
	m_gauges[static_cast<int>(GaugeType::Hp)]->SetValue(m_status.HP, Gauge::Value::Max);
	m_gauges[static_cast<int>(GaugeType::Stamina)]->SetValue(m_status.Stamina, Gauge::Value::Max);
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
	for (auto& weapons : m_weapons) {
		weapons->End();
	}
	// アニメーションの破棄
	for (int i = 0;i < static_cast<int>(MyMath::FourDirection::Max);i++) {
		for (int& handle : m_graphHandle[i])
			DeleteGraph(handle);
	}
	m_pItemMgr = nullptr;
	delete m_pItemMgr;
}

void Player::Update()
{

	if (m_pItemMgr) {
		if (Pad::IsPressed(Pad::Button::B)) {
			m_pItemMgr->CheckHitCollision(GetCircle());
		}
		if (Pad::IsPressed(Pad::Button::Back)) {
			m_pItemMgr->Create(ItemBase::ItemType::Heal, GetTransform().position);
		}
		if (Pad::IsPressed(Pad::Button::Back)) {
			m_pItemMgr->Create(ItemBase::ItemType::Heal, GetTransform().position);
		}
	}
	m_camera->Update(GetTransform());
	m_deltaTime = Time::GetInstance().GetDeltaTime();
	// 時間が止まっていなければ移動処理を呼ぶ
	if (Time::GetInstance().GetDeltaTime()) {
		Move();
	}
	//m_box.SetPosition(GetTransform().position);
	m_circle.SetPosition(GetTransform().position);
	printfDx("deltatime : %f\n", m_deltaTime);
	printfDx("移動量 : %f\n", m_moveVector.GetLength());
	/*
	if (Pad::IsDown(Pad::Button::LB)) {
	}*/
		//m_gauges[static_cast<int>(GaugeType::Exp)]->Increase(10*m_deltaTime);

	printfDx("m_direction : %d\n", static_cast<int>(m_direction));
	frame += m_deltaTime * 2;
	if (frame > kPlayerFrame)frame = 0;
	m_direction = MyMath::Direction(GetTransform().rotation.z);
	if (m_gauges[static_cast<int>(GaugeType::Exp)]->CheckMax()) {
		LevelUp();
	}
	CheckHit();
	UpdateAngerButton();
	if (/*m_gauges[static_cast<int>(GaugeType::Anger)]->CheckMax() &&*/
		CheckAngerButton()) {
		m_anger = true;
	}
	if (m_gauges[static_cast<int>(GaugeType::Anger)]->CheckMin()) {
		m_anger = false;
	}if (m_anger) {
		m_gauges[static_cast<int>(GaugeType::Anger)]->Decrease(3.3f * m_deltaTime);
	}
}

void Player::Move()
{

	MoveAmount();
	SpeedUpdate();

	// 座標の移動
	GetTransform().position += m_moveVector*m_deltaTime;
}

void Player::MoveAmount()
{
	// 入力量を取得
	m_moveAmount = Pad::PadAnalogAmount(Pad::Joystick::Left);
	printfDx("入力量 : %f\n", m_moveAmount);
	PlayerStatus status = m_status;
	if (m_anger) {
		status *= kAngerStatus;
	}
	// ダッシュ中なら
	if (CheckDashNow()) {
	}
	else {
		// スティック入力の角度
		float angle = Pad::AnalogAngle(Pad::Joystick::Left);
		// 向いている方向を更新
		GetTransform().rotation.z = angle * MyMath::ToRadian;

		m_gauges[static_cast<int>(GaugeType::Stamina)]->Increase(kStaminaHealValue * m_deltaTime);
		m_gauges[static_cast<int>(GaugeType::Stamina)]->Clamp();
		if (angle > 0) {
			m_directionX = 1;
		}
		else
		{
			m_directionX = -1;
		}
	}
	for (auto& weapons : m_weapons) {
		weapons->GetTransform().rotation.z = GetTransform().rotation.z;
		// 武器の座標を設定
		weapons->GetTransform().position = GetTransform().position;
		// 武器の更新処理
		//weapons->Update();
	
		weapons->SetPlayerStatus(status);
		if (m_anger) {
			weapons->SetScale(3);
		}
		else {
			weapons->SetScale(1);

		}
	}
	
	if (Pad::IsDown(Pad::Button::X)||Pad::IsReleased(Pad::Button::X)) {
		if(!CheckDashNow())
		m_weapons[0]->Attack();
	}
	if (Pad::IsPressed(Pad::Button::Y)) {
		std::unique_ptr<Weapon>change;
		change = std::move(m_weapons[1]);
		m_weapons[1] = std::move(m_weapons[0]);
		m_weapons[0] = std::move(change);
		change = nullptr;
	}
	int s = 0;
	for (int i = m_weapons.size() - 1; i >= 0; i--) {
		m_weapons[i]->SetActive(false);
		s++;
	}
	m_weapons[0]->SetActive(true);
	for (auto& gauge : m_gauges) {
		gauge->Update();
	}

	printfDx("m_direction : %d\n",m_directionX);
	// 移動量の初期化
	m_moveVector = { 0,0,0 };
	// 入力角度からX,Y方向の移動量を計算
	m_moveVector.x = sinf(GetTransform().rotation.z);
	m_moveVector.y = -cosf(GetTransform().rotation.z);
	// 正規化
	m_moveVector = m_moveVector.GetNormalize();
	// 移動速度を求める(入力量×移動速度×速度割合×時間)
	float moveSpeed = m_moveAmount * status.Speed * m_accel * m_deltaTime;
	// プレイヤーの移動量に入力量と移動速度と時間をかける
	m_moveVector *= moveSpeed;

	if (m_moveAmount) {
		m_direction = Pad::AnalogDirection(Pad::Joystick::Left);
	}
	
	printfDx("moveSpeed : %f\n",moveSpeed);
}

void Player::SpeedUpdate()
{
	// ダッシュしていないとき
	if (Pad::IsPressed(Pad::Button::A)&& CheckCanDash()) {
		m_accel = kDashSpeed;
		m_gauges[static_cast<int>(GaugeType::Stamina)]->Decrease(kDashStaimina);
		m_gauges[static_cast<int>(GaugeType::Stamina)]->Clamp();
	}
	if (CheckDashNow()) {
		m_moveAmount = 1;
		m_accel -= kDeccel * m_deltaTime;
		m_accel = MyMath::Clamp(m_accel, 1.0f, 100.0f);
	}
}

void Player::Draw()
{
	// プレイヤー・カメラが移動していることがわかるよう一定の位置に円を描画
	DrawCircle(600, 400, 10, GetColor(0, 0, 255));
	// プレイヤー座標に円を描画
	DrawCircle(GetTransform().position.x, GetTransform().position.y, 10, GetColor(255, 0, 0));
	// プレイヤー画像の表示
	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y, kPlayerScale, 0, m_graphHandle[static_cast<int>(m_direction)][kFrame[static_cast<int>(frame)]], TRUE);
	// 現在向いている方向のデバッグ表示
	Vector3 angle = { 0,0,0 };
	angle.x = sinf(GetTransform().rotation.z);
	angle.y = -cosf(GetTransform().rotation.z);
	angle = angle.GetNormalize();
	angle *= 10 * Pad::PadAnalogAmount(Pad::Joystick::Left);
	angle += GetTransform().position;
	DrawCircle(angle.x, angle.y, 3, GetColor(0, 255, 0));
	Debug();
	printfDx("x : %f\n", GetTransform().position.x);
	printfDx("y : %f\n", GetTransform().position.y);
	printfDx("z : %f\n", GetTransform().position.z);
	printfDx("weaponSize : %d\n", m_weapons.size());
}

void Player::Debug()
{
	//printfDx("現在HP       : %f\n", m_gauges[static_cast<int>(GaugeType::Hp)]->GetValue(Gauge::Value::Current));
	//printfDx("最大HP       : %f\n", m_gauges[static_cast<int>(GaugeType::Hp)]->GetValue(Gauge::Value::Max));
	//printfDx("最大HP       : %f\n", m_status.HP);
	//printfDx("最小HP       : %f\n", m_gauges[static_cast<int>(GaugeType::Hp)]->GetValue(Gauge::Value::Min));
	//printfDx("割合HP       : %f\n", GetGaugeRate(GaugeType::Hp));
	//printfDx("現在スタミナ : %f\n", m_gauges[static_cast<int>(GaugeType::Stamina)]->GetValue(Gauge::Value::Current));
	//printfDx("最大スタミナ : %f\n", m_gauges[static_cast<int>(GaugeType::Stamina)]->GetValue(Gauge::Value::Max));
	//printfDx("最小スタミナ : %f\n", m_gauges[static_cast<int>(GaugeType::Stamina)]->GetValue(Gauge::Value::Min));
	//printfDx("割合スタミナ : %f\n", GetGaugeRate(GaugeType::Stamina));
	//printfDx("現在怒り     : %f\n", m_gauges[static_cast<int>(GaugeType::Anger)]->GetValue(Gauge::Value::Current));
	//printfDx("最大怒り     : %f\n", m_gauges[static_cast<int>(GaugeType::Anger)]->GetValue(Gauge::Value::Max));
	//printfDx("最小怒り     : %f\n", m_gauges[static_cast<int>(GaugeType::Anger)]->GetValue(Gauge::Value::Min));
	//printfDx("割合怒り     : %f\n", GetGaugeRate(GaugeType::Anger));
	//printfDx("現在経験     : %f\n", m_gauges[static_cast<int>(GaugeType::Exp)]->GetValue(Gauge::Value::Current));
	//printfDx("最大経験     : %f\n", m_gauges[static_cast<int>(GaugeType::Exp)]->GetValue(Gauge::Value::Max));
	//printfDx("最小経験     : %f\n", m_gauges[static_cast<int>(GaugeType::Exp)]->GetValue(Gauge::Value::Min));
	//printfDx("割合経験     : %f\n", GetGaugeRate(GaugeType::Exp));

	printfDx("m_angerButton : %d\n", CheckAngerButton());
	printfDx("Level          : %d\n", m_status.Level);
	printfDx("Attack         : %f\n", m_status.Attack);
	printfDx("Defence        : %f\n", m_status.Defence);
	printfDx("Speed          : %f\n", m_status.Speed);
	printfDx("stamina        : %f\n", m_status.Stamina);
	printfDx("CriticalRate   : %f\n", m_status.CriticalRate);
	printfDx("CriticalDamage : %f\n", m_status.CriticalDamage);

	m_gauges[static_cast<int>(GaugeType::Exp)]->Debug();
	//m_box.DebugDraw();
	m_circle.DebugDraw();
	//printfDx("timeScale : %f\n", Time::GetInstance().GetTimeScale());
}

void Player::Damage(float value)
{
	// ダッシュ中なら処理しない
	if (CheckDashNow())return;
	if (m_anger)return;
	// ダメージ処理を行う
	m_gauges[static_cast<int>(GaugeType::Hp)]->Decrease(value);
	// 最大・最小値よりも大ききくならないようにする
	m_gauges[static_cast<int>(GaugeType::Hp)]->Clamp();
	// 怒りゲージを上昇させる
	m_gauges[static_cast<int>(GaugeType::Anger)]->Increase(value * kAngerValue);
	// 最大・最小値よりも大ききくならないようにする
	m_gauges[static_cast<int>(GaugeType::Anger)]->Clamp();
}

void Player::Heal(float value)
{
	// HPの回復処理を行う
	m_gauges[static_cast<int>(GaugeType::Hp)]->Increase(value);
	// 最大・最小値よりも大ききくならないようにする
	m_gauges[static_cast<int>(GaugeType::Hp)]->Clamp();
}

void Player::AddBuff(const PlayerBuff& playerBuff) const
{
	PlayerBuff buf = playerBuff;
	//m_buffs.push_back(buf);
		//m_grasses.push_back(std::move(grass));
	return;
}

bool Player::IsDead()
{
	return !m_gauges[static_cast<int>(GaugeType::Hp)]->GetValue();
}

float Player::GetGaugeCurrentValue(GaugeType gauge)
{
	return m_gauges[static_cast<int>(gauge)]->GetValue(Gauge::Value::Current);
}

float Player::GetGaugeMaxValue(GaugeType gauge)
{
	return m_gauges[static_cast<int>(gauge)]->GetValue(Gauge::Value::Max);
}

float Player::GetGaugeRate(GaugeType gauge)
{
	return m_gauges[static_cast<int>(gauge)]->GetRate();
}

void Player::SetEnemyManager(EnemyManager* enemyManager)
{
	m_pEnemyMgr = enemyManager;
	for (auto& weapons : m_weapons) {
		weapons->SetEnemyManager(m_pEnemyMgr);
	}
}

bool Player::CheckCanDash()
{
	// ダッシュ可能かどうかを調べる
	// ダッシュ中ならfalse
	if (CheckDashNow())return false;
	bool canDash = false;
	// 現在のスタミナがダッシュ時の消費スタミナより多いかどうか調べる
	canDash = m_gauges[static_cast<int>(GaugeType::Stamina)]->CheckValue(kDashStaimina);
	return canDash;
}

bool Player::CheckDashNow()
{
	return m_accel > 1;
}

void Player::CheckHit()
{
	if (!m_pEnemyMgr)return;
	for (auto& weapons : m_weapons) {
		if (!weapons)continue;
		if (!weapons->CheckAttack())continue;
		weapons->CheckCollision();
	}
	//m_pEnemyMgr->CheckHitEnemies(m_weapons->GetCollision(), static_cast<int>(1 * m_status.Attack));

}

void Player::LevelUp()
{
	// レベル上昇前の最大HPを取得
	float beforeMaxHp= m_status.HP;
	m_status.Level++;
	m_status = m_status*kGrowStatus;
	
	// レベル上昇後の最大HPを取得
	float maxHp = m_status.HP;
	// 最大値を更新
	m_gauges[static_cast<int>(GaugeType::Hp)]->SetValue(maxHp, Gauge::Value::Max);
	// 現在のHPを取得
	float currentHp= m_gauges[static_cast<int>(GaugeType::Hp)]->GetValue();
	// 最大HPが上昇した量だけ現在のHPに加算した値を求める
	currentHp += maxHp - beforeMaxHp;
	// 現在のHPの更新
	m_gauges[static_cast<int>(GaugeType::Hp)]->SetValue(currentHp, Gauge::Value::Current);

}

bool Player::CheckAngerButton()
{

	return (m_angerButton[0] && !m_angerButton[1]);
}

void Player::UpdateAngerButton()
{
	m_angerButton[1] = m_angerButton[0];
	if (Pad::IsDown(Pad::Button::RT) &&
		Pad::IsDown(Pad::Button::LT) &&
		Pad::IsDown(Pad::Button::RB) &&
		Pad::IsDown(Pad::Button::LB)) {
		m_angerButton[0] = true;
		//return true;
	}
	else {
		m_angerButton[0] = false;
	}
}
