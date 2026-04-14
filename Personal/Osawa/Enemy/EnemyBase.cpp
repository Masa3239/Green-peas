#include "EnemyBase.h"

EnemyBase::EnemyBase(ObjectManager* objManager) :
	GameObject(objManager),
	m_hp(1),
	m_player(nullptr)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
	UpdateEnemy();
}
