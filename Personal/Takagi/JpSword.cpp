#include "JpSword.h"
#include"../../Utility/Time.h"
#include"RadToPos.h"
#include"../Osawa/Enemy/EnemyManager.h"

namespace {
	const char* const kEffectPath = "Resource\\pipo-btleffect161.png";
	constexpr float kEffectDistance = 130;
	constexpr float kEffectScale = 0.6f;
	constexpr float kEffectAnimSpeed = 15;
	constexpr PlayerStatus kStatus = { 0,0,15,0,0,0,10,1.1f };
	constexpr PlayerStatus kChargeStatus = { 0,0,3,0,0,0,3,1.1f };

	constexpr float kAttackRadius = 80;
}

JpSword::JpSword(ObjectManager* objManager):
	Weapon(objManager)
{
	for (int& handle : m_effectHandle) {
		handle = -1;
	}
	LoadDivGraph(kEffectPath, 10, 5, 2, 400, 400, m_effectHandle);
	m_attack = false;
	m_effectFrame = 11;
	m_weaponStatus = kStatus;
	m_scale = 1;
}

JpSword::~JpSword()
{
}

void JpSword::Init()
{
}

void JpSword::End()
{
}

void JpSword::Update()
{
	float time = Time::GetInstance().GetDeltaTime();
	if (m_effectHandle[static_cast<int>(m_effectFrame)] == -1) {
		m_attack = false;
	}
	else {
		m_effectFrame += time * kEffectAnimSpeed;
	}
	m_effectTransform.position = RadToPos(m_effectTransform.rotation.z, kEffectDistance, GetTransform().position);
	m_circle.SetRadius(kAttackRadius * m_scale);
	m_circle.SetPosition(m_effectTransform.position);
}

void JpSword::Draw()
{
	Vector3 effectPos = m_effectTransform.position;
	int effectHandle = m_effectHandle[static_cast<int>(m_effectFrame)];
	DrawRotaGraph(effectPos.x, effectPos.y, kEffectScale*m_scale, /*GetTransform().rotation.z*/0, effectHandle, TRUE);
	m_circle.DebugDraw();
}

void JpSword::Attack()
{
	if (m_attack)return;
	m_attack = true;
	m_effectTransform.rotation = GetTransform().rotation;
	m_effectFrame = 0;
	m_effectTransform.position = RadToPos(m_effectTransform.rotation.z, kEffectDistance, GetTransform().position);
	m_circle.SetRadius(kAttackRadius * m_scale);
	m_circle.SetPosition(m_effectTransform.position);
}

bool JpSword::CheckAttack()
{
	return m_attack;
}

void JpSword::CheckCollision()
{
	if (!m_pEnemyMgr)return;

	float damage = 0;
	damage = m_playerStatus.Attack * m_weaponStatus.Attack;
	float criticalRate = m_playerStatus.CriticalRate + m_weaponStatus.CriticalRate;
	float criticalDamage = m_weaponStatus.CriticalDamage + m_playerStatus.CriticalDamage;
	m_pEnemyMgr->CheckHitEnemies(m_circle, damage, criticalRate, criticalDamage);
}
