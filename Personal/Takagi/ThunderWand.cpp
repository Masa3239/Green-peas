#include "ThunderWand.h"
#include"../Asai/Thunder.h"
#include"../../System/InputManager.h"
#include"../Osawa/Enemy/EnemyManager.h"
#include"../../Utility/Time.h"
#include"../../Utility/Mymath.h"
namespace {
	const char* const kHandlePath = "Resource\\Topaz Staff.png";
	constexpr PlayerStatus kStatus = { 0,0,2,0,0,0,11,2 };
	constexpr float kDrawRadian = -45 * MyMath::ToRadian;
	constexpr Vector3 kOffsetPos = { 20,0,0 };
	constexpr float kSwingSpeed = 600;
	constexpr float kSwingPower = -60;
}

ThunderWand::ThunderWand(ObjectManager* objManager) :
	Weapon(objManager),
	m_pThunders(),
	m_drawTransform()
{
	m_scale = 1;
	m_graphHandle = -1;
	m_graphHandle = LoadGraph(kHandlePath);
	m_weaponStatus = kStatus;
	m_active = true;
	m_drawTransform.Reset();
	m_chargeFlag = false;
	m_camUpdate = true;

}

ThunderWand::~ThunderWand()
{
	DeleteGraph(m_graphHandle);
}

void ThunderWand::Init()
{

	for (auto& thunders : m_pThunders) {
		thunders = nullptr;
		thunders = new Thunder(GetObjectManager());
		thunders->Init();
		thunders->SetEnemyManager(m_pEnemyMgr);
	}
	m_swingState = Swing::Normal;
}

void ThunderWand::End()
{
}

void ThunderWand::Update()
{
	m_drawTransform = GetTransform();
	if (!m_active)return;
	float time = Time::GetInstance().GetDeltaTime();
	m_swing.position.y += m_verticalSpeed;
	m_verticalSpeed += kSwingSpeed*time;
	if (m_swing.position.y > 0) {
		m_swing.position.y = 0;
		m_swingState = Swing::Normal;
	}

	m_drawTransform.position.y += m_swing.position.y * time;
}

void ThunderWand::Draw()
{
	if (!m_active)return;
	Vector3 pos= m_drawTransform.position;
	if (MyMath::Direction(GetTransform().rotation.z) == MyMath::FourDirection::Front) {
		pos += kOffsetPos;
	}
	else if(MyMath::Direction(GetTransform().rotation.z) == MyMath::FourDirection::Back){
		pos -= kOffsetPos;
	}
	DrawRotaGraph(pos.x, pos.y, 1, kDrawRadian, m_graphHandle, TRUE);
	
}

bool ThunderWand::Attack()
{
	if (m_swingState != Swing::Normal)return false;
	if (!InputManager::GetInstance().IsReleased(Input::Action::Attack))return false;
	Transform shot = m_drawTransform;
	Shot(shot);
	m_swing.Reset();
	m_verticalSpeed = kSwingPower;
	m_swingState = Swing::Up;
	return true;
}

bool ThunderWand::CheckAttack()
{
    return true;
}

void ThunderWand::CheckCollision()
{
	if (!m_pEnemyMgr)return;
	float damage = 0;
	damage = m_playerStatus.Attack * m_weaponStatus.Attack;
	float criticalRate = m_playerStatus.CriticalRate + m_weaponStatus.CriticalRate;
	float criticalDamage = m_weaponStatus.CriticalDamage * m_playerStatus.CriticalDamage;
	for (int i = 0;i < kBulletNum;i++) {
		if (!m_pThunders[i]->GetIsActive())continue;
		if (m_pEnemyMgr->CheckHitEnemies(m_pThunders[i]->GetCollision(), damage, criticalRate, criticalDamage, Weapon::Bow, i)) {
			m_pThunders[i]->ChangeStateInfection();
		}
	}
}

void ThunderWand::Shot(const Transform& transform)
{
	for (int i = 0;i < kBulletNum;i++) {
		if (m_pThunders[i]->GetIsActive())continue;

		m_pThunders[i]->Shot(transform);
		m_pEnemyMgr->ResetEnemyDamageFlag(Weapon::Volt, i);
		break;
	}
}
