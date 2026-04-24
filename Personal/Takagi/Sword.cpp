#include "Sword.h"
#include "Weapon.h"
#include"../../Object/GameObject.h"
#include"../../Utility/MyMath.h"
#include"../../Utility/Transform.h"
#include"../../Utility/Vector3.h"
#include"../../Utility/Time.h"
//#include"../../System/InputPad.h"
#include"../Osawa/Enemy/EnemyManager.h"
#include<DxLib.h>
#include<math.h>
#include"PlayerStatus.h"
#include"RadToPos.h"
#include"../../System/InputManager.h"
namespace {
	const char* const kGraphPath = "Resource\\Golden Sword.png";
	const char* const kSlashPath = "Resource\\pipo-btleffect001.png";
	/// <summary>
	/// 武器の表示座標
	/// </summary>
	constexpr Vector3 kOffset = { -13.0f,15.0,0.0f };
	constexpr float kLerpSwing = 24.0f;
	constexpr float kLerpPos =50.0f;
	//constexpr Transform kSwingUp = {
	//	{0,0,0},
	//	{0,60 * MyMath::ToRadian,0},
	//	{0,0,0}
	//};
	constexpr float kDrawRadian = 45 * MyMath::ToRadian;
	constexpr float kSwingRadian = 60 * MyMath::ToRadian;
	constexpr float kColRadius = 10;
	constexpr float kInitRadian = 150*MyMath::ToRadian;
	constexpr PlayerStatus kStatus = { 0,0,15,0,0,0,1,1.2f };
	constexpr PlayerStatus kChargeStatus = { 0,0,3,0,0,0,3,1.3f };
	// 剣を振る際の距離
	constexpr float kAttackDistance = 60;
	constexpr float kEffectDistance = 80;

	constexpr float kEffectScale = 1.3f;
	constexpr float kEffectAnimSpeed =30;
	constexpr float kEffectDrawRadian = 150 * MyMath::ToRadian;

}

Sword::Sword(ObjectManager* objManager) :
	Weapon(objManager),
	m_attack(false)
{
	// グラフィックハンドルの読み込み
	m_graphHandle = -1;
	m_graphHandle = LoadGraph(kGraphPath);

	// トランスフォームの初期設定
	GetTransform().Reset();
	
	// 武器を振る際のTransformを初期化
	m_swing.Reset();
	m_desireRadian = 0;
	m_swingState = Swing::Normal;
	m_cupsule = Collision::Capsule(Vector3(),Vector3(), kColRadius);
	m_active = true;
	m_effectFrame = kEffectFrame -1;
	for (int& handle : m_effectHandle) {
		handle = -1;
	}
	LoadDivGraph(kSlashPath, 5, 5, 1, 120, 120, m_effectHandle);
	m_effectTransform.Reset();
	m_scale = 1;
	m_chargeFlag = false;
	m_camUpdate = true;
}

Sword::~Sword()
{
	DeleteGraph(m_graphHandle);
}

void Sword::Init()
{
	m_weaponStatus = kStatus;
}

void Sword::End()
{
}

void Sword::Update()
{
	m_scaleEx = 1;
	if (m_chargeFlag)m_scaleEx = 2;
	if (!m_catch) {
		m_swing.position = GetTransform().position;
		m_swing.rotation.z = GetTransform().rotation.z;
		return;
	}
	float time = Time::GetInstance().GetDeltaTime();
	float differ = m_desireRadian - m_swing.rotation.z;
	differ = MyMath::NormalizeAngle(differ * MyMath::ToDegree) * MyMath::ToRadian;
	m_swing.rotation.z += differ*kLerpSwing * time;
	if (differ * differ < 0.1f * 0.1f) {
		if (m_swingState == Swing::Up) {
			m_desireRadian = m_attackRadian - kSwingRadian;
			m_swingState = Swing::Down;
		}
		else if (m_swingState == Swing::Down && m_effectHandle[static_cast<int>(m_effectFrame)]==-1) {
			m_desireRadian = m_attackRadian;
			m_attack = false;
			m_swingState = Swing::Normal;
			m_charge = 0;

		}
	}

	Vector3 drawPos = GetTransform().position;
	switch (MyMath::Direction(GetTransform().rotation.z)) {
	case MyMath::FourDirection::Right:
		drawPos.x += kOffset.x;
		//drawPos.y += kOffset.y;
		break;
	case MyMath::FourDirection::Left:
		drawPos.x -= kOffset.x;
		//drawPos.y += kOffset.y;
		break;
	case MyMath::FourDirection::Back:
		drawPos.y += kOffset.y;
		break;
	case MyMath::FourDirection::Front:
		drawPos.y -= kOffset.y;
			break;
	}

	if (m_attack) {
		drawPos = RadToPos(m_swing.rotation.z, kAttackDistance*m_scale, GetTransform().position);
	}
	else {
		int dir = 1;
		if (GetTransform().rotation.z * MyMath::Sign(GetTransform().rotation.z) < 90*MyMath::ToRadian) {
			dir = 2;
		}
		m_swing.rotation.z = 60 * MyMath::ToRadian*dir;
		if (GetTransform().rotation.z >= 0) {
		m_desireRadian = -kInitRadian;
		}
		else {
		m_desireRadian = kInitRadian;
		}
		m_attackRadian= GetTransform().rotation.z;
	}
	m_swing.position += (drawPos - m_swing.position) * kLerpPos * time;
	m_cupsule.SetPosition(drawPos);
	//Vector3 pos = GetTransform().position;
	//pos.y -= 50;
	//m_effectTransform.position = pos;
	m_effectFrame += time * kEffectAnimSpeed;
	m_effectFrame = MyMath::Clamp(m_effectFrame, 0.0f, static_cast<float>(kEffectFrame - 1));
	m_effectTransform.position = RadToPos(m_effectTransform.rotation.z, kEffectDistance*m_scale, GetTransform().position);


	m_cupsule.SetStartPos(GetTransform().position);
	Vector3 colEnd = RadToPos(m_swing.rotation.z, kEffectDistance*1.6f*m_scale, GetTransform().position);
	m_cupsule.SetEndPos(colEnd);
	m_cupsule.SetRadius(kColRadius * m_scale);
	m_chargeFlag = (m_charge >= kChargeTime);
}

void Sword::Draw()
{
	bool reverseX = false;
	//switch (MyMath::Direction(GetTransform().rotation.z))
	//{
	//case MyMath::FourDirection::Right:
	//case MyMath::FourDirection::Left:
	//	reverseX = false;
	//	break;
	//case MyMath::FourDirection::Back:
	//case MyMath::FourDirection::Front:
	//	reverseX = true;
	//	break;
	//default:
	//	break;
	//}
	float radZ = GetTransform().rotation.z;
	if (radZ < 0)radZ *= -1;
	if ( radZ>= 90) {
		reverseX = true;
	}
	else {
		reverseX = false;

	}

	//if (reverseX)radian *= -1;
	//if (attack) {
	//}
	//else {
	//	radian = 0;
	//}
	//m_cupsule.DebugDraw();
	Vector3 effectPos = m_effectTransform.position;
	float effectRadian = m_effectTransform.rotation.z + kEffectDrawRadian;
	int handle = m_effectHandle[static_cast<int>(m_effectFrame)];
	DrawRotaGraph(effectPos.x, effectPos.y, kEffectScale*m_scale, effectRadian, handle, TRUE);
	m_catchCol.DebugDraw();
	if (!m_active)return;
	float radian = /*GetTransform().rotation.z+*/m_swing.rotation.z;
	if (m_catch)radian += kDrawRadian;
	DrawRotaGraph(m_swing.position.x, m_swing.position.y, m_scale, radian, m_graphHandle, TRUE, reverseX);
	printfDx("角度 : %f\n", GetTransform().rotation.z);
	printfDx("attack : %d\n", m_attack);
}

bool Sword::Attack()
{
	if (m_swingState != Swing::Normal)return false;
	if (InputManager::GetInstance().IsDown(Input::Action::Attack)) {
		m_weaponStatus = kStatus;
		//if (!Pad::IsPressed(Pad::Button::X))return;
		m_charge += Time::GetInstance().GetDeltaTime();
	}
	if (!InputManager::GetInstance().IsReleased(Input::Action::Attack))return false;
	m_pEnemyMgr->ResetEnemyDamageFlag(Weapon::Sword, 0);
	m_desireRadian = m_attackRadian + kSwingRadian;
	m_swing.rotation.z = m_desireRadian;
	m_attack = true;
	m_swingState = Swing::Up;
	m_effectFrame = 0;

	float radian=GetTransform().rotation.z;

	m_effectTransform.rotation.z = radian;
	if (m_charge >= kChargeTime) {
		m_weaponStatus *= kChargeStatus;
	}
	return true;
}

bool Sword::CheckAttack()
{

	return m_attack;
}

void Sword::CheckCollision()
{
	if (!m_pEnemyMgr)return;

	float damage = 0;
	damage = m_playerStatus.Attack * m_weaponStatus.Attack;
	float criticalRate = m_playerStatus.CriticalRate + m_weaponStatus.CriticalRate;
	float criticalDamage = m_weaponStatus.CriticalDamage * m_playerStatus.CriticalDamage;
	m_pEnemyMgr->CheckHitEnemies(m_cupsule, damage, criticalRate, criticalDamage,Weapon::Sword,0);


}
