#include "EnemyTest.h"

EnemyTest::EnemyTest()
{
}

EnemyTest::~EnemyTest()
{
}

void EnemyTest::Init()
{
}

void EnemyTest::End()
{
}

void EnemyTest::UpdateEnemy()
{
}

void EnemyTest::Draw()
{
	auto transform = GetTransform();

	DrawBox(transform.position.x, transform.position.y, transform.position.x + 20, transform.position.y + 20, 0xffffff, 1);
}
