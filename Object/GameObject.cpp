#include "GameObject.h"
#include "../System/ObjectManager.h"
#include "../Utility/Vector3.h"

GameObject::GameObject(ObjectManager* manager) :
	m_pObjManager(manager),
	m_state(State::Active),
	m_drawOrder(0)
{
	m_pObjManager->AddGameObject(this);

	m_transform.Reset();
}

GameObject::~GameObject()
{
	m_pObjManager->RemoveGameObject(this);
}
