#include "Warrior.h"

Warrior::Warrior(ObjectManager* objManager):
	Player(objManager)
{
	m_directionX = 1;
	m_moveAmount=0;
	m_accel = 1;
	m_deltaTime = 0;
	m_moveVector={ 0,0,0 };
	m_direction=MyMath::FourDirection::Front;
	m_animFrame=0;
	m_camera=nullptr;
	m_cameraTransform.Reset();
	m_pEnemyMgr=nullptr;
	m_pItemMgr=nullptr;
	m_anger=false;
	m_cameraShakeCount = 0;
	m_playerType = Character::Job::Warrior;
}

Warrior::~Warrior()
{
}
//
//void Warrior::Init()
//{
//}
//
//void Warrior::End()
//{
//}
//
//void Warrior::Update()
//{
//}
//
//void Warrior::Move()
//{
//}
//
//void Warrior::MoveAmount()
//{
//}
//
//void Warrior::Dash(bool stamina)
//{
//}
//
//void Warrior::SpeedUpdate()
//{
//}
//
//void Warrior::Draw()
//{
//}
//
//void Warrior::Debug()
//{
//}
