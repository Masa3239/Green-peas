#include "Bow.h"
#include "Weapon.h"
#include"../../Object/GameObject.h"
#include"../Asai/Arrow.h"
#include"../../System/InputPad.h"
#include"../Osawa/Enemy/EnemyManager.h"

namespace {
	constexpr float kShowRadian = -45 * MyMath::ToRadian;
	const char* const kHandlePath = "Image\\Bow.png";
	constexpr PlayerStatus kStatus = { 0,0,15,0,0,0,10,2 };
}

Bow::Bow(ObjectManager* objManager) :
	Weapon(objManager)
{
	for (auto& arrows : m_pArrows) {
		arrows = nullptr;
		arrows = new Arrow(objManager);
	}
	m_graphHandle = LoadGraph(kHandlePath);
}

Bow::~Bow()
{
	DeleteGraph(m_graphHandle);
}

void Bow::Init()
{
}

void Bow::End()
{
}

void Bow::Update()
{
}

void Bow::Draw()
{
	float radian = GetTransform().rotation.y+kShowRadian /*+ (kShowRadian)*MyMath::Sign(GetTransform().rotation.y)*/;
	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y, 1, radian, m_graphHandle, TRUE);
}

void Bow::Attack()
{
	if (!Pad::IsReleased(Pad::Button::X))return;
	m_pArrows[0]->Shot(GetTransform());
}

bool Bow::CheckAttack()
{
    return false;
}

Collision::Circle Bow::GetCollision()
{
	return Collision::Circle();
}

void Bow::CheckCollision()
{
	if (!m_pEnemyMgr)return;
	float damage = 0;
	damage = m_playerStatus.Attack + m_weaponStatus.Attack;
	float criticalRate = m_playerStatus.CriticalRate + m_weaponStatus.CriticalRate;
	if (GetRand(100) < criticalRate) {
		damage *= m_weaponStatus.CriticalDamage;
	}
	for (auto& arrows : m_pArrows) {
		m_pEnemyMgr->CheckHitEnemies(arrows->GetCollision(),damage);
	}
}
