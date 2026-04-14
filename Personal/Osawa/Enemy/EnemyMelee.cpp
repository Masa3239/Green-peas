#include "EnemyMelee.h"
#include "../Personal/Takagi/Player.h"

EnemyMelee::EnemyMelee(ObjectManager* objManager) :
	EnemyBase(objManager)
{
}

EnemyMelee::~EnemyMelee()
{
}

void EnemyMelee::Init()
{
}

void EnemyMelee::End()
{
}

void EnemyMelee::UpdateEnemy()
{
	if (GetPlayer())
	{

	}
}

void EnemyMelee::Draw()
{
	auto& transform = GetTransform();
	
	DrawBox(transform.position.x, transform.position.y, transform.position.x + 20, transform.position.y + 20, 0xff0000, 1);
}
