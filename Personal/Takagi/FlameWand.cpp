#include "FlameWand.h"
#include"../Asai/FireBall.h"
#include"../../Object/GameObject.h"
#include"../Osawa/Enemy/EnemyManager.h"
#include"RadToPos.h"
#include"../../System/InputManager.h"
#include"../../Utility/Time.h"
namespace {
	const char* const kHandlePath = "Resource\\Ruby Staff.png";
	constexpr PlayerStatus kStatus = { 0,0,8,0,0,0,3,2 };
	constexpr float kDrawRadian = -45 * MyMath::ToRadian;
	constexpr float kSwingDistance = 30;
	constexpr Vector3 kOffsetPos = { 20,0,0 };
}

FlameWand::FlameWand(ObjectManager* objManager):
	Weapon(objManager),
	m_pFires(),
	m_desireTransform()
{
	for (auto& fires : m_pFires) {
		fires = nullptr;
		fires = new FireBall(objManager);
		fires->Init();
	}
	m_scale = 1;
	m_graphHandle = -1;
	m_graphHandle = LoadGraph(kHandlePath);
	m_weaponStatus = kStatus;
	m_active = true;
	m_desireTransform.Reset();
	m_chargeFlag = false;
	m_camUpdate = true;
	m_swingState = Swing::Normal;
}

FlameWand::~FlameWand()
{
	DeleteGraph(m_graphHandle);
}

void FlameWand::Init()
{
}

void FlameWand::End()
{
}

void FlameWand::Update()
{
	float time = Time::GetInstance().GetDeltaTime();
	if (m_swingState == Swing::Normal) {
		m_desireTransform.Reset();
	}
	for (int i = 0;i < kBulletNum;i++) {
		if (!m_pFires[i]->CanFieldDamage())continue;
		m_pEnemyMgr->ResetEnemyDamageFlag(Weapon::Flame, i);
		m_pFires[i]->ResetDamageInterval();
	}
	Vector3 lerpPos = m_desireTransform.position - m_swing.position;
	lerpPos *= time * 30;
	float lerpDeg = m_desireTransform.rotation.z - m_swing.rotation.z;
	lerpDeg *= time * 30;
	m_swing.position += lerpPos;
	m_swing.rotation.z += lerpDeg;
	if (lerpDeg < 0)lerpDeg *= -1;
	if (lerpDeg < 0.001f) {
		switch (m_swingState)
		{
		case Weapon::Swing::Normal:
			break;
		case Weapon::Swing::Up:
			m_swingState = Swing::Down;
			break;
		case Weapon::Swing::Down:
			m_swingState = Swing::Normal;
			break;
		case Weapon::Swing::Max:
			break;
		default:
			break;
		}
	}

}

void FlameWand::Draw()
{
	if (!m_active)return;
	Vector3 pos = m_swing .position+GetTransform().position;
	if (MyMath::Direction(GetTransform().rotation.z) == MyMath::FourDirection::Front) {
		pos += kOffsetPos;
	}
	else if (MyMath::Direction(GetTransform().rotation.z) == MyMath::FourDirection::Back) {
		pos -= kOffsetPos;
	}
	float radian = kDrawRadian + m_swing.rotation.z;
	DrawRotaGraph(pos.x, pos.y, 1, radian, m_graphHandle, TRUE);
	DrawCircle(m_desireTransform.position.x, m_desireTransform.position.y, 7, 0xff0000);
}

bool FlameWand::Attack()
{
	if (m_swingState != Swing::Normal)return false;
	if (!InputManager::GetInstance().IsReleased(Input::Action::Attack))return false;

	m_desireTransform.position = RadToPos(GetTransform().rotation.z, kSwingDistance);
	m_desireTransform.rotation.z = GetTransform().rotation.z+DX_PI_F/2;
	m_swingState = Swing::Up;
	Transform shot = GetTransform();
	Shot(shot);
	return true;
}

bool FlameWand::CheckAttack()
{
	return true;
}

void FlameWand::CheckCollision()
{
	if (!m_pEnemyMgr)return;
	float damage = 0;
	damage = m_playerStatus.Attack * m_weaponStatus.Attack;
	float criticalRate = m_playerStatus.CriticalRate + m_weaponStatus.CriticalRate;
	float criticalDamage = m_weaponStatus.CriticalDamage * m_playerStatus.CriticalDamage;
	for (int i = 0;i < kBulletNum;i++) {
		if (!m_pFires[i]->GetIsActive())continue;
		if (m_pEnemyMgr->CheckHitEnemies(m_pFires[i]->GetCollision(), damage, criticalRate, criticalDamage, Weapon::Flame, i)) {
			m_pFires[i]->ChangeStateField();
		}
	}
}

void FlameWand::Shot(const Transform& transform)
{
	for (int i = 0;i < kBulletNum;i++) {
		if (m_pFires[i]->GetIsActive())continue;

		m_pFires[i]->Shot(transform);
		m_pEnemyMgr->ResetEnemyDamageFlag(Weapon::Flame, i);
		break;
	}
}
