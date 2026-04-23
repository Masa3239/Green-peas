#include "BossBulletBase.h"

BossBulletBase::BossBulletBase(ObjectManager* objManager) :
	GameObject(objManager),
	m_graphHandle(-1),
	m_velocity(0.0f, 0.0f, 0.0f),
	m_collision(),
	m_pPlayer(nullptr) 
{
}