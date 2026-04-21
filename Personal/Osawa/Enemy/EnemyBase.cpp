#include "EnemyBase.h"
#include "../Chara/Collision.h"
#include "../Utility/Transform.h"
#include "../Utility/Time.h"
#include "../Personal/Takagi/Player.h"

namespace
{
	constexpr Vector3 kColliderSize{ 25, 40, 0 };

	constexpr int kMaxHp = 30;

	constexpr float kInvTime = 0.5f;
}

EnemyBase::EnemyBase(ObjectManager* objManager) :
	GameObject(objManager),
	m_hp(kMaxHp),
	m_collider(Collision::AABB{ Vector3(), kColliderSize }),
	m_attackCooltimeCounter(0.0f),
	m_attackCooltime(0.0f),
	m_invCounter(0.0f),
	m_variableStatus(0),
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

	// 当たり判定の座標更新
	m_collider.SetPosition(GetTransform().position);

	// 無敵時間をカウントダウン
	if (m_invCounter > 0) m_invCounter -= Time::GetInstance().GetDeltaTime();
}

bool EnemyBase::Damage(const int damage)
{
	// 攻撃判定に当たった瞬間ではないなら早期リターン
	if (m_invCounter > 0) return false;

	m_invCounter = kInvTime;

	m_hp -= damage;

	return true;
}
