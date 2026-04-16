#include "BulletBase.h"

BulletBase::BulletBase(ObjectManager* objManager):
	GameObject(objManager),
	m_graphHandle(-1),
	m_transform(),
	m_spawnPos(),
	m_isActive(false),
	m_circle()
{
}
