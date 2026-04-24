#include "Katana.h"
#include"../../Utility/Time.h"
#include"RadToPos.h"
#include"../Osawa/Enemy/EnemyManager.h"
//#include"../../System/InputPad.h"
#include"../../System/InputManager.h"
namespace {
	const char* const kEffectPath = "Resource\\pipo-btleffect161.png";
	constexpr float kEffectDistance = 105;
	constexpr float kChargeDistance = 165;
	constexpr float kEffectScale = 0.3f;
	constexpr float kChargeScale = 0.7f;
	constexpr float kEffectAnimSpeed = 15;
	constexpr PlayerStatus kStatus = { 0,0,5,0,0,0,10,1.1f };
	constexpr PlayerStatus kChargeStatus = { 0,0,1,0,0,0,5,1.1f };

	constexpr float kAttackRadius = 150;
	constexpr int kEffectStart = 5;
	constexpr int kCameraUpdate = 4;
}

Katana::Katana(ObjectManager* objManager):
	Weapon(objManager),
	m_chaergeScale(1)
{
	for (int& handle : m_effectHandle) {
		handle = -1;
	}
	LoadDivGraph(kEffectPath, 10, 5, 2, 400, 400, m_effectHandle);
	for (int i = kEffectFrame - 1;i >= 0;i--) {
		if (i < kEffectStart) {
			m_effectHandle[i] = 0;
			continue;
		}
		m_effectHandle[i] = m_effectHandle[i - kEffectStart];
	}
	m_attack = false;
	m_effectFrame = kEffectFrame-1;
	m_weaponStatus = kStatus;
	m_scale = 1;
	m_active = true;
	m_chargeFlag = false;
	m_camUpdate = true;
}

Katana::~Katana()
{
}

void Katana::Init()
{
}

void Katana::End()
{
}

void Katana::Update()
{
	float time = Time::GetInstance().GetDeltaTime();
	int handle = m_effectHandle[static_cast<int>(m_effectFrame)];
	if (m_effectHandle[static_cast<int>(m_effectFrame)] == -1) {
		m_attack = false;
	}
	else {
		m_effectFrame += time * kEffectAnimSpeed;
	}
	if (m_effectHandle[static_cast<int>(m_effectFrame)] == -1 &&
		handle != -1) {
		m_charge = 0;
	}
	if (m_effectHandle[static_cast<int>(m_effectFrame)] != handle) {
		m_pEnemyMgr->ResetEnemyDamageFlag(Weapon::Katana, 0);
	}
	//m_effectTransform.position = RadToPos(m_effectTransform.rotation.z, kEffectDistance, GetTransform().position);
	m_circle.SetRadius(kAttackRadius * m_scale*kEffectScale);
	m_circle.SetPosition(m_effectTransform.position);
	m_chargeFlag = (m_charge >= kChargeTime);
	if (m_chargeFlag) {
		m_circle.SetRadius(kAttackRadius * m_scale * kChargeScale);
	}
	if (m_effectFrame >= kCameraUpdate) {
		m_camUpdate = true;
	}
}

void Katana::Draw()
{
	Vector3 effectPos = m_effectTransform.position;
	int effectHandle = m_effectHandle[static_cast<int>(m_effectFrame)];
	float scale = kEffectScale;
	if (m_chargeFlag) {
		scale = kChargeScale;
	}
	DrawRotaGraph(effectPos.x, effectPos.y, scale*m_scale, /*GetTransform().rotation.z*/0, effectHandle, TRUE);
	m_circle.DebugDraw();
	m_catchCol.DebugDraw();
}

bool Katana::Attack()
{
	if (m_attack)return false;
	if (InputManager::GetInstance().IsDown(Input::Action::Attack)) {
		m_weaponStatus = kStatus;
		m_charge += Time::GetInstance().GetDeltaTime();
	}
	if(!InputManager::GetInstance().IsReleased(Input::Action::Attack))return false;
	m_pEnemyMgr->ResetEnemyDamageFlag(Weapon::Katana, 0);
	m_attack = true;
	m_effectTransform.rotation = GetTransform().rotation;
	m_effectFrame = kEffectStart;
	m_effectTransform.position = RadToPos(m_effectTransform.rotation.z, kEffectDistance, GetTransform().position);
	m_circle.SetRadius(kAttackRadius * m_scale);
	m_circle.SetPosition(m_effectTransform.position);
	if (m_charge >= kChargeTime) {
		m_weaponStatus *= kChargeStatus;
		m_effectFrame = 0;
		m_effectTransform.position = RadToPos(m_effectTransform.rotation.z, kChargeDistance, GetTransform().position);
		m_camUpdate = false;
		return true;
	}
	return false;
}

bool Katana::CheckAttack()
{
	return m_attack;
}

void Katana::CheckCollision()
{
	if (!m_pEnemyMgr)return;
	if (m_effectFrame < kEffectStart)return;
	float damage = 0;
	damage = m_playerStatus.Attack * m_weaponStatus.Attack;
	float criticalRate = m_playerStatus.CriticalRate + m_weaponStatus.CriticalRate;
	float criticalDamage = m_weaponStatus.CriticalDamage + m_playerStatus.CriticalDamage;
	//m_pEnemyMgr->CheckHitEnemies(m_circle, damage, criticalRate, criticalDamage);
	m_pEnemyMgr->CheckHitEnemies(m_circle, damage, criticalRate, criticalDamage, Weapon::Katana, 0);
}
