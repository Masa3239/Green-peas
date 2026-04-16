#include "EnemyBase.h"
#include "../Chara/Collision.h"
#include "../Utility/Transform.h"

namespace
{
	constexpr Vector3 kColliderSize{ 25, 40, 0 };
}

EnemyBase::EnemyBase(ObjectManager* objManager) :
	GameObject(objManager),
	m_hp(1),
	m_collider(Collision::AABB{ Vector3(), kColliderSize }),
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
	m_collider.SetPosition(GetTransform().position);
}
