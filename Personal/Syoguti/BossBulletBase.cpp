#include "BossBulletBase.h"

BossBulletBase::BossBulletBase(ObjectManager* objManager) :
	GameObject(objManager),
	m_velocity(0.0f, 0.0f, 0.0f),
	m_collision(),
	m_pPlayer(nullptr) 
{
	for (int i = 0; i < 32; i++)
	{
		m_graphHandle[i] = -1;
	}
}