#include "EnemyBase.h"
#include "../Chara/Collision.h"
#include "../Utility/Transform.h"
#include "../Utility/Time.h"
#include "../Personal/Takagi/Player.h"

namespace
{
	constexpr Vector3 kColliderSize{ 25, 40, 0 };
}

EnemyBase::EnemyBase(ObjectManager* objManager) :
	GameObject(objManager),
	m_hp(100),
	m_collider(Collision::AABB{ Vector3(), kColliderSize }),
	m_attackCooltimeCounter(0.0f),
	m_attackCooltime(0.0f),
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
