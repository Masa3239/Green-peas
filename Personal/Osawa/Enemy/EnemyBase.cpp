#include "EnemyBase.h"

EnemyBase::EnemyBase(ObjectManager* objManager) :
	GameObject(objManager),
	m_hp(1)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
	UpdateEnemy();
}
