#include "Bow.h"
#include "Weapon.h"
#include"../../Object/GameObject.h"
#include"../Asai/Arrow.h"
#include"../../System/InputPad.h"
#include"../Osawa/Enemy/EnemyManager.h"

namespace {
	constexpr float kDrawRadian = -45 * MyMath::ToRadian;
	const char* const kHandlePath = "Image\\Bow.png";
	constexpr PlayerStatus kStatus = { 0,0,15,0,0,0,10,2 };
	// 複数同時発射する際の角度
	constexpr float kTriShotRadian = 40.0f * MyMath::ToRadian;
}

Bow::Bow(ObjectManager* objManager) :
	Weapon(objManager)
{
	for (auto& arrows : m_pArrows) {
		arrows = nullptr;
		arrows = new Arrow(objManager);
		arrows->Init();
	}
	m_graphHandle = LoadGraph(kHandlePath);
	m_weaponStatus = kStatus;
	m_active = true;
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
	if (!m_active)return;
	float radian = GetTransform().rotation.z+kDrawRadian /*+ (kShowRadian)*MyMath::Sign(GetTransform().rotation.z)*/;
	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y, 1, radian, m_graphHandle, TRUE);
}

void Bow::Attack()
{
	if (!Pad::IsReleased(Pad::Button::X))return;
	Shot(GetTransform());
	if (true) {
		Transform shot = GetTransform();
		shot.rotation.z += kTriShotRadian;
		Shot(shot);
		shot = GetTransform();
		shot.rotation.z -= kTriShotRadian;
		Shot(shot);
	}
}

bool Bow::CheckAttack()
{

	return true;
}
//
//Collision::Circle Bow::GetCollision()
//{
//	return Collision::Circle();
//}

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
		if (!arrows->GetIsActive())continue;
		m_pEnemyMgr->CheckHitEnemies(arrows->GetCollision(), damage);
	}
}

void Bow::Shot(const Transform& transform)
{
	for (auto& arrows : m_pArrows) {
		if (arrows->GetIsActive())continue;

		arrows->Shot(transform);
		break;
	}
}
