#include "Weapon.h"

Weapon::Weapon(ObjectManager* objManager):
GameObject(objManager),
m_graphHandle(-1),
m_swing(Transform()),
m_swingState(Swing::Max),
m_attackRadian(0),
m_pEnemyMgr(nullptr),
m_playerStatus(), 
m_weaponStatus() 
{
}

void Weapon::SetPos(const Vector3 position)
{
	GetTransform().position = position;
	m_catchCol.SetPosition(position);
}
