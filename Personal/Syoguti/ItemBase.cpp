#include "ItemBase.h"

ItemBase::ItemBase(ObjectManager* objManager) :
	GameObject(objManager),
	m_transform(),
	m_graphHandle(-1),
	m_collision(),
	m_pPlayer(nullptr)
{
}

