#include "ThunderWand.h"
#include"../Asai/Thunder.h"
#include"../../System/InputManager.h"
#include"../Osawa/Enemy/EnemyManager.h"
namespace {
	const char* const kHandlePath = "Resource\\Topaz Staff.png";
	constexpr PlayerStatus kStatus = { 0,0,2,0,0,0,1,2 };
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

	for (auto& arrows : m_pThunders) {
		arrows = nullptr;
		arrows = new Thunder(objManager);
		arrows->Init();
	}
}

ThunderWand::~ThunderWand()
{
	DeleteGraph(m_graphHandle);
}

void ThunderWand::Init()
{
}

void ThunderWand::End()
{
}

void ThunderWand::Update()
{
}

void ThunderWand::Draw()
{
	if (!m_active)return;
	Vector3 pos=GetTransform().position;
	DrawRotaGraph(pos.x, pos.y, 1, 0, m_graphHandle, TRUE);
}

bool ThunderWand::Attack()
{
	if (!InputManager::GetInstance().IsReleased(Input::Action::Attack))return false;
	Transform shot = m_drawTransform;
	Shot(shot);
	return true;
}

bool ThunderWand::CheckAttack()
{
    return false;
}

void ThunderWand::CheckCollision()
{
	if (!m_pEnemyMgr)return;
	float damage = 0;
	damage = m_playerStatus.Attack * m_weaponStatus.Attack;
	float criticalRate = m_playerStatus.CriticalRate * m_weaponStatus.CriticalRate;
	float criticalDamage = m_weaponStatus.CriticalDamage * m_playerStatus.CriticalDamage;
	for (int i = 0;i < kBulletNum;i++) {
		if (!m_pThunders[i]->GetIsActive())continue;
		m_pEnemyMgr->CheckHitEnemies(m_pThunders[i]->GetCollision(), damage, criticalRate, criticalDamage, Weapon::Bow, i);
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
