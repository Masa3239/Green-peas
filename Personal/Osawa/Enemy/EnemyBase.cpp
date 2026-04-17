#include "EnemyBase.h"
#include "../Chara/Collision.h"
#include "../Utility/Transform.h"
#include "../Utility/Time.h"
#include "../Personal/Takagi/Player.h"

namespace
{
	constexpr Vector3 kColliderSize{ 25, 40, 0 };

	constexpr int kMaxHp = 10;
}

EnemyBase::EnemyBase(ObjectManager* objManager) :
	GameObject(objManager),
	m_hp(kMaxHp),
	m_collider(Collision::AABB{ Vector3(), kColliderSize }),
	m_attackCooltimeCounter(0.0f),
	m_attackCooltime(0.0f),
	m_invincible(false),
	m_wasDamagedThisFrame(false),
	m_player(nullptr)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
	m_collider.SetPosition(GetTransform().position);
	
	UpdateEnemy();

	if (m_attackCooltimeCounter > 0)
	{
		m_attackCooltimeCounter -= Time::GetInstance().GetDeltaTime();
	}
	else
	{
		if (m_collider.CheckCollision(GetPlayer()->GetCircle()))
		{
			Attack();

			m_attackCooltimeCounter = m_attackCooltime;
		}
	}

	m_collider.SetPosition(GetTransform().position);
}

void EnemyBase::PostUpdate()
{
	if (!m_wasDamagedThisFrame)
	{
		m_invincible = false;
	}

	m_wasDamagedThisFrame = false;
}

void EnemyBase::Damage(const int damage)
{
	m_wasDamagedThisFrame = true;

	// 攻撃判定に当たった瞬間ではないなら早期リターン
	if (m_invincible) return;

	m_invincible = true;

	m_hp -= damage;
}
