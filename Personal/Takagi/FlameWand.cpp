#include "FlameWand.h"
#include"../Asai/FireBall.h"
#include"../../Object/GameObject.h"
#include"../Osawa/Enemy/EnemyManager.h"
#include"RadToPos.h"
#include"../../System/InputManager.h"

namespace {
	const char* const kHandlePath = "Resource\\Ruby Staff.png";
	constexpr PlayerStatus kStatus = { 0,0,2,0,0,0,1,2 };
}

FlameWand::FlameWand(ObjectManager* objManager):
	Weapon(objManager),
	m_pFires(),
	m_drawTransform()
{
	for (auto& arrows : m_pFires) {
		arrows = nullptr;
		arrows = new FireBall(objManager);
		arrows->Init();
	}
	m_scale = 1;
	m_graphHandle = -1;
	m_graphHandle = LoadGraph(kHandlePath);
	m_weaponStatus = kStatus;
	m_active = true;
	m_drawTransform.Reset();
	m_chargeFlag = false;
	m_camUpdate = true;
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
}

void FlameWand::Draw()
{
}

bool FlameWand::Attack()
{
	if (!InputManager::GetInstance().IsReleased(Input::Action::Attack))return false;
	Transform shot = m_drawTransform;
	Shot(shot);
	return true;
	return false;
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
	float criticalRate = m_playerStatus.CriticalRate * m_weaponStatus.CriticalRate;
	float criticalDamage = m_weaponStatus.CriticalDamage * m_playerStatus.CriticalDamage;
	for (int i = 0;i < kFlameNum;i++) {
		if (!m_pFires[i]->GetIsActive())continue;
		m_pEnemyMgr->CheckHitEnemies(m_pFires[i]->GetCollision(), damage, criticalRate, criticalDamage, Weapon::Bow, i);
	}
}

void FlameWand::Shot(const Transform& transform)
{
	for (int i = 0;i < kFlameNum;i++) {
		if (m_pFires[i]->GetIsActive())continue;

		m_pFires[i]->Shot(transform);
		m_pEnemyMgr->ResetEnemyDamageFlag(Weapon::Flame, i);
		break;
	}
}
