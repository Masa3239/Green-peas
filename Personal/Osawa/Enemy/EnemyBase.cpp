#include "EnemyBase.h"

EnemyBase::EnemyBase() :
	m_state(State::Alive),
	m_hp(1)
{
	m_transform.Reset();
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
	UpdateEnemy();

	if (m_hp <= 0)
	{
		m_state = State::Dead;
	}
}
