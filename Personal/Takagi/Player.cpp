#include<DxLib.h>
#include "Player.h"
#include"Gauge.h"
#include"../Utility/Transform.h"
#include"../Utility/Vector3.h"
#include"../Utility/Time.h"
#include<math.h>
#include<memory>
#include<vector>
#include"../Asai/Camera.h"
#include"../Chara/Collision.h"
#include"../../Object/GameObject.h"
#include"../../System/ObjectManager.h"
#include"Weapon.h"
#include"ExpGauge.h"
#include"../Syoguti/ItemManager.h"
#include"../Syoguti/ItemBase.h"
#include"../Osawa/Enemy/EnemyManager.h"
#include"PlayerStatus.h"
#include"PlayerBuff.h"
#include"../../System/InputManager.h"
#include"../../System/Input/Keyboard.h"
#include"../../System/Input/Gamepad.h"
#include"BuffManager.h"
namespace {
	
	// 通常の移動速度
	constexpr float kSpeed = 20000.0f;
	// ダッシュの移動速度
	constexpr float kDashSpeed = 7.0f;
	// ダッシュの減速量
	constexpr float kDeccel = kDashSpeed * 3.0f;
	// ダッシュ時のスタミナ消費量
	constexpr float kDashStaimina = 30;
	// スタミナの自動回復量
	constexpr float kStaminaHealValue = 10;
	// 怒りゲージの上昇倍率
	constexpr float kAngerValue = 2.0f;
	// 怒りゲージの減少量
	constexpr float kAngerDecValue = 3.3f;
	// 円の当たり判定の大きさ
	constexpr float kCircleSize = 15;
	// プレイヤー画像のグラフィックハンドル
	const char* const kGraphPath[static_cast<int>(Character::Job::Max)] = {
		"Resource\\pipo-charachip_otaku01.png" ,
		"Resource\\pipo-halloweenchara2016_01.png" ,
		"Resource\\pipo-xmaschara02.png" 
	};
	// カメラを振動させる時間
	constexpr float kCameraShake = 0.3f;
	// 初期座標
	constexpr Vector3 kAcrossInitPos = { 5000,9640,0 };


	// 画像の表示倍率
	constexpr float kPlayerScale = 1.5f;
	// 初期ステータス
	constexpr PlayerStatus kInitStatus = PlayerStatus(1, 5, 1, 5, kSpeed, 100, 5, 1.5f);
	// 成長倍率
	constexpr PlayerStatus kGrowStatus = PlayerStatus(1, 1.05f, 1.02f, 1.02f, 1, 1, 1, 1);
	// 怒り状態時のステータス
	constexpr PlayerStatus kAngerStatus = PlayerStatus(1, 1, 3, 1, 2, 1, 1.5f, 2);
}

Player::Player(ObjectManager* objManager) :
	GameObject(objManager),
	m_directionX(1),
	m_moveAmount(0),
	m_accel(1),
	m_deltaTime(0),
	m_moveVector({ 0,0,0 }),
	m_direction(MyMath::FourDirection::Front),
	m_animFrame(0),
	m_camera(nullptr),
	m_cameraTransform(),
	m_circle(),
	m_pEnemyMgr(nullptr),
	m_pItemMgr(nullptr),
	m_angerButton(),
	m_anger(false)
{

}

Player::~Player()
{
}

void Player::Init()
{
	m_circle = Collision::Circle(GetTransform().position, kCircleSize);

	m_angerButton[0] = false;
	m_angerButton[1] = false;
	// 初期座標の設定
	GetTransform().position = kAcrossInitPos;

	// 各ゲージの初期化
	for (auto& gauge : m_gauges) {
		gauge = std::make_unique<Gauge>();
	}
	// 経験値ゲージの初期化
	m_gauges[static_cast<int>(GaugeType::Exp)] = std::make_unique<ExpGauge>();
	// 怒りゲージを0に
	m_gauges[static_cast<int>(GaugeType::Anger)]->Reset(Gauge::Value::Min);
	m_gauges[static_cast<int>(GaugeType::Hp)]->SetValue(kInitStatus.HP,Gauge::Value::Max);
	m_gauges[static_cast<int>(GaugeType::Hp)]->Reset(Gauge::Value::Max);
	// 円の当たり判定を初期化
	m_circle = Collision::Circle(GetTransform().position, kCircleSize);

	for (auto& weapons : m_weapons) {
		if (!weapons)continue;
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
	LoadDivGraph(kGraphPath[static_cast<int>(m_playerType)], 12, 3, 4, 32, 32, graph);
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
	m_cameraTransform.Reset();
	m_exp = 1;
}

void Player::End()
{
	m_camera->End();
	m_camera = nullptr;
	delete m_camera;
	for (auto& weapons : m_weapons) {
		if (!weapons)continue;
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
	m_deltaTime = Time::GetInstance().GetDeltaTime();
	// 時間が止まっていたら処理しない
	if (!m_deltaTime)return;

	if (m_pItemMgr) {
		if (InputManager::GetInstance().IsPressed(Input::Action::PickUp)) {
			m_pItemMgr->CheckHitCollision(GetCircle());
		}
	}
	m_camera->Update(m_cameraTransform);
	// 時間が止まっていなければ移動処理を呼ぶ
	if (Time::GetInstance().GetDeltaTime()) {
		Move();
	}
	//m_box.SetPosition(GetTransform().position);
	m_circle.SetPosition(GetTransform().position);
	printfDx("deltatime : %f\n", m_deltaTime);
	printfDx("移動量 : %f\n", m_moveVector.GetLength());

		//m_gauges[static_cast<int>(GaugeType::Exp)]->Increase(10*m_deltaTime);

	printfDx("m_direction : %d\n", static_cast<int>(m_direction));
	m_animFrame += m_deltaTime * 2;
	if (m_animFrame > kPlayerFrame)m_animFrame = 0;
	m_direction = MyMath::Direction(GetTransform().rotation.z);
	if (m_gauges[static_cast<int>(GaugeType::Exp)]->CheckMax()) {
		LevelUp();
	}
	CheckHit();
	UpdateAngerButton();
	if (m_gauges[static_cast<int>(GaugeType::Anger)]->CheckMax() &&
		CheckAngerButton()) {
		m_anger = true;
		m_camera->ChangeAnger();
	}
	if (m_gauges[static_cast<int>(GaugeType::Anger)]->CheckMin()) {
		m_anger = false;
		m_camera->ChangeFollow();

	}if (m_anger) {
		m_gauges[static_cast<int>(GaugeType::Anger)]->Decrease(kAngerDecValue * m_deltaTime);
	}
	if (m_buffs.size() <= 0)return;
	// バフの更新処理
	for (int i = 0;i < m_buffs.size();i++) {
		if (!m_buffs[i])continue;
		m_buffs[i]->Update();
		// バフの効果が終了していたら
		if (m_buffs[i]->IsFinish()) {
			// バフを消去する
			m_buffs.erase(m_buffs.begin() + i);
		}
	}
	//for (auto& buffs : m_buffs) {
	//	if (buffs)continue;
	//	buffs.Update();
	//	// バフの効果が終了していたら
	//	if (buffs.IsFinish()) {
	//		// バフを消去する
	//		m_buffs.erase(m_buffs.begin() + i);
	//	}
	//}
	
	SetDrawOrder(GetTransform().position.y);
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
	printfDx("入力量 : %f\n", m_moveAmount);
	PlayerStatus status = CheckBuffValue();
	if (m_anger) {
		status *= kAngerStatus;
	}
	// ダッシュ中なら
	if (CheckDashNow()) {
	}
	else {
		// 入力量を取得
		m_moveAmount = InputManager::GetInstance().GetAnalog2DAmount(Input::Action::Move);
		if (m_moveAmount) {
			// スティック入力の角度
			float angle = InputManager::GetInstance().GetAnalog2DAngle(Input::Action::Move);
			// 向いている方向を更新
			GetTransform().rotation.z = angle * MyMath::ToRadian;
		}
	}
	if (!CheckDashNow()) {
		m_gauges[static_cast<int>(GaugeType::Stamina)]->Increase(kStaminaHealValue * m_deltaTime);
		m_gauges[static_cast<int>(GaugeType::Stamina)]->Clamp();
	}
	for (auto& weapons : m_weapons) {
		if (!weapons)continue;
		// 武器の座標・回転を設定
		weapons->GetTransform() = GetTransform();
		//weapons->GetTransform().position = GetTransform().position;
		// 武器の更新処理
		//weapons->Update();
	
		weapons->SetPlayerStatus(status);
		weapons->SetPlayerJob(GetPlayerJob());
		if (m_anger) {
			weapons->SetScale(3);
		}
		else {
			weapons->SetScale(1);

		}
	}
	
	if (InputManager::GetInstance().IsDown(Input::Action::Attack)||
		InputManager::GetInstance().IsReleased(Input::Action::Attack)) {
		if(!CheckDashNow())
		if (m_weapons[0]->Attack()&&m_weapons[0]->GetWeaponType() == Weapon::Katana) {
			Dash(false);
		}


	}
	if (!m_weapons[0]||m_weapons[0]->CheckCameraUpdate()) {
		m_cameraTransform = GetTransform();
	}
	// 指定のボタンを押したとき かつ 武器を複数持っているとき
	if (InputManager::GetInstance().IsPressed(Input::Action::Weapon) &&
		m_weapons[1]) {
		Weapon* change;
		change = m_weapons[1];
		m_weapons[1] = m_weapons[0];
		m_weapons[0] = change;
		change = nullptr;
	}
	for (int i = kWeaponMaxNum - 1; i >= 0; i--) {
		if (!m_weapons[i])continue;
		m_weapons[i]->SetActive(false);
	}
	if(m_weapons[0])
	m_weapons[0]->SetActive(true);
	for (auto& gauge : m_gauges) {
		gauge->Update();
	}

	// 移動量の初期化
	m_moveVector = { 0,0,0 };
	// 入力角度からX,Y方向の移動量を計算
	m_moveVector.x = cosf(GetTransform().rotation.z);
	m_moveVector.y = sinf(GetTransform().rotation.z);
	// 正規化
	m_moveVector = m_moveVector.GetNormalize();
	// 移動速度を求める(入力量×移動速度×速度割合×時間)
	float moveSpeed = m_moveAmount * status.Speed * m_accel * m_deltaTime;
	// プレイヤーの移動量に入力量と移動速度と時間をかける
	m_moveVector *= moveSpeed;

	if (m_moveAmount) {
		m_direction = MyMath::Direction(GetTransform().rotation.z);
	}
	
	printfDx("moveSpeed : %f\n",moveSpeed);
}

void Player::Dash(bool stamina)
{
	m_accel = kDashSpeed;
	if (!stamina)return;
	m_gauges[static_cast<int>(GaugeType::Stamina)]->Decrease(kDashStaimina);
	m_gauges[static_cast<int>(GaugeType::Stamina)]->Clamp();
}

void Player::SpeedUpdate()
{
	// ダッシュしていないとき
	if (InputManager::GetInstance().IsPressed(Input::Action::Dash) && 
		CheckCanDash()) {
		Dash();
	}
	if (CheckDashNow()) {
		m_moveAmount = 1;
		m_accel -= kDeccel * m_deltaTime;
		m_accel = MyMath::Clamp(m_accel, 1.0f, 100.0f);
	}
}

void Player::Draw()
{
	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y, kPlayerScale, 0, m_graphHandle[static_cast<int>(m_direction)][kFrame[static_cast<int>(m_animFrame)]], TRUE);
	
	Debug();
}

void Player::Debug()
{
	// プレイヤー座標に円を描画
	//DrawCircle(GetTransform().position.x, GetTransform().position.y, 10, GetColor(255, 0, 0));
	// プレイヤー画像の表示
	// 現在向いている方向のデバッグ表示
	Vector3 angle = { 0,0,0 };
	angle.x = sinf(GetTransform().rotation.z);
	angle.y = -cosf(GetTransform().rotation.z);
	angle = angle.GetNormalize();
	angle *= 10 * m_moveAmount;
	angle += GetTransform().position;
	//DrawCircle(angle.x, angle.y, 3, GetColor(0, 255, 0));

	printfDx("m_angerButton : %d\n", CheckAngerButton());
	printfDx("Level          : %d\n", m_status.Level);
	printfDx("Attack         : %f\n", m_status.Attack);
	printfDx("Defence        : %f\n", m_status.Defence);
	printfDx("Speed          : %f\n", m_status.Speed);
	printfDx("stamina        : %f\n", m_status.Stamina);
	printfDx("CriticalRate   : %f\n", m_status.CriticalRate);
	printfDx("CriticalDamage : %f\n", m_status.CriticalDamage);
	for (auto& weapons : m_weapons) {
		if (!weapons)continue;
		printfDx("　　　武器 　　: %d\n", weapons->GetWeaponType());
	}
	m_gauges[static_cast<int>(GaugeType::Exp)]->Debug();
	//m_box.DebugDraw();
	//m_circle.DebugDraw();
	for (auto& buffs : m_buffs) {
		printfDx("残り時間 : %f\n", buffs->Second());
	}
	float attack = CheckBuffValue().Attack;
	float speed = CheckBuffValue().Speed;
	printfDx("攻撃 : %f\n", attack);
	printfDx("攻撃 : %f\n", speed);
	//printfDx("timeScale : %f\n", Time::GetInstance().GetTimeScale());
}

void Player::Damage(float value)
{
	// ダッシュ中なら処理しない
	if (CheckDashNow())return;
	if (m_anger)return;
	float defence= CheckBuffValue().Defence;
	float damage = value - defence;
	damage = MyMath::Clamp(damage, 0.0f, value);
	float hpMax = GetGaugeMaxValue(GaugeType::Hp);
	float angerValue = damage / hpMax * 100;
	angerValue *= kAngerDecValue;
	// ダメージ処理を行う
	m_gauges[static_cast<int>(GaugeType::Hp)]->Decrease(damage);
	// 最大・最小値よりも大ききくならないようにする
	m_gauges[static_cast<int>(GaugeType::Hp)]->Clamp();
	// 怒りゲージを上昇させる
	m_gauges[static_cast<int>(GaugeType::Anger)]->Increase(angerValue);
	// 最大・最小値よりも大ききくならないようにする
	m_gauges[static_cast<int>(GaugeType::Anger)]->Clamp();
	// カメラを揺らす
	m_camera->StartDamage(kCameraShake);
}

void Player::Heal(float value)
{
	// HPの回復処理を行う
	m_gauges[static_cast<int>(GaugeType::Hp)]->Increase(value);
	// 最大・最小値よりも大ききくならないようにする
	m_gauges[static_cast<int>(GaugeType::Hp)]->Clamp();
}

void Player::AddBuff( PlayerBuff& playerBuff)
{
	std::unique_ptr< PlayerBuff> buf = std::make_unique<PlayerBuff>(playerBuff.GetBuffValue(), playerBuff.Second(), playerBuff.IsEternal());
	m_buffs.push_back(std::move(buf));
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
		if (!weapons)continue;
		weapons->SetEnemyManager(m_pEnemyMgr);
	}
}

void Player::SetWeapon(Weapon* weapon)
{
	if (!m_weapons[1]) {
		m_weapons[1] = weapon;
	}
	if (m_weapons[0]) {
		m_weapons[0]->SetChatch(false);
	}
	m_weapons[0] = weapon;

}

void Player::ExpUp(float value)
{
	m_gauges[static_cast<int>(GaugeType::Exp)]->Increase(value);
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
	m_pBuffMgr->BuffSelectStart();
}

void Player::BufUpdate()
{
}

bool Player::CheckAngerButton()
{

	return (m_angerButton[0] && !m_angerButton[1]);
}

void Player::UpdateAngerButton()
{
	m_angerButton[1] = m_angerButton[0];
	if (InputManager::GetInstance().GetAsBool(Input::Action::Anger1)) {
		m_angerButton[0] = true;
	}
	else {
		m_angerButton[0] = false;
	}
}

const PlayerStatus Player::CheckBuffValue()
{
	PlayerStatus status = { 1,1,1,1,1,1,1,1 };
	for (auto& buff : m_buffs) {
		status += buff.get()->GetBuffValue();
	}
	status.Attack=m_status.Attack*status.Attack;
	status.Defence=m_status.Defence*status.Defence;
	status.Speed=m_status.Speed*status.Speed;
	status.CriticalRate=m_status.CriticalRate+status.CriticalRate;
	status.CriticalDamage=m_status.CriticalDamage+status.CriticalDamage;
	return status;
}
