#include "Bow.h"
#include "Weapon.h"
#include"../../Object/GameObject.h"
#include"../Asai/Arrow.h"
//#include"../../System/InputPad.h"
#include"../Osawa/Enemy/EnemyManager.h"
#include"RadToPos.h"
#include"../../System/InputManager.h"
namespace {
	constexpr float kDrawRadian = 45 * MyMath::ToRadian;
	const char* const kHandlePath = "Resource\\Bow.png";
	constexpr PlayerStatus kStatus = { 0,0,15,0,0,0,10,2 };
	// 複数同時発射する際の角度
	constexpr float kTriShotRadian = 25.0f * MyMath::ToRadian;
	constexpr float kShotRadius = 10.0f;

}

Bow::Bow(ObjectManager* objManager) :
	Weapon(objManager),
	m_drawTransform()
{
	for (auto& arrows : m_pArrows) {
		arrows = nullptr;
		arrows = new Arrow(objManager);
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
	//if (!m_catch)return;
	if (!m_active)return;
	m_drawTransform = GetTransform();
	if (InputManager::GetInstance().IsDown(Input::Action::Attack)) {
	m_drawTransform.position = RadToPos(m_drawTransform.rotation.z, kShotRadius, m_drawTransform.position);
	}
}

void Bow::Draw()
{
	if (!m_active)return;
	float radian = m_drawTransform.rotation.z+kDrawRadian /*+ (kShowRadian)*MyMath::Sign(GetTransform().rotation.z)*/;
	DrawRotaGraph(m_drawTransform.position.x, m_drawTransform.position.y, m_scale, radian, m_graphHandle, TRUE);
	m_catchCol.DebugDraw();
}

bool Bow::Attack()
{
	if (!InputManager::GetInstance().IsReleased(Input::Action::Attack))return false;
	Transform shot = m_drawTransform;
	Shot(shot);
	if (true) {
		shot.rotation.z += kTriShotRadian;
		Shot(shot);
		shot = GetTransform();
		shot.rotation.z -= kTriShotRadian;
		Shot(shot);
	}
	return true;
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
	damage = m_playerStatus.Attack * m_weaponStatus.Attack;
	float criticalRate = m_playerStatus.CriticalRate * m_weaponStatus.CriticalRate;
	float criticalDamage = m_weaponStatus.CriticalDamage * m_playerStatus.CriticalDamage;
	//m_pEnemyMgr->CheckHitEnemies(m_circle, damage);
	for (int i = 0;i < kBulletNum;i++) {
		if (!m_pArrows[i]->GetIsActive())continue;
		//m_pEnemyMgr->CheckHitEnemies(m_pArrows[i]->GetCollision(), damage, criticalRate, criticalDamage);
		m_pEnemyMgr->CheckHitEnemies(m_pArrows[i]->GetCollision(), damage, criticalRate, criticalDamage, Weapon::Bow, i);
	}
}

void Bow::Shot(const Transform& transform)
{
	for (int i = 0;i < kBulletNum;i++) {
		if (m_pArrows[i]->GetIsActive())continue;

		m_pArrows[i]->Shot(transform);
		m_pEnemyMgr->ResetEnemyDamageFlag(Weapon::Bow, i);
		//arrows->SetScale(4);
		break;
	}
}
