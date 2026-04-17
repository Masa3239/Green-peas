#include "Weapon.h"

Weapon::Weapon(ObjectManager* objManager):
m_graphHandle(-1),
m_swing(Transform()),
m_swingState(Swing::Max),
m_attackRadian(0),
m_pEnemyMgr(nullptr),
GameObject(objManager),
m_playerStatus(), 
m_weaponStatus() 
{
}
