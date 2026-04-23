#include "BulletBase.h"

BulletBase::BulletBase(ObjectManager* objManager):
	GameObject(objManager),
	m_scale(1.0f),
	m_spawnPos(),
	m_isActive(false),
	m_circle()
{
}
