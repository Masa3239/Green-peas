#include "EnemyManager.h"
#include "EnemyBase.h"

#include "EnemyTest.h"
#include <DxLib.h>

EnemyManager::EnemyManager(ObjectManager* objManager) :
	m_objManager(objManager)
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{

}

void EnemyManager::End()
{
	for (auto& enemy : m_enemies)
	{
		enemy->End();
	}
}

void EnemyManager::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		if (m_enemies.size() <= 1) return;

		m_enemies.back()->SetHP(0);
	}

	for (const auto& enemy : m_enemies)
	{
		if (enemy->GetHP() > 0) continue;

		enemy->SetState(GameObject::State::Dead);
	}

	for (auto iter = m_enemies.begin(); iter != m_enemies.end();)
	{
		EnemyBase* enemy = *iter;
		if (enemy->GetHP() <= 0)
		{
			iter = m_enemies.erase(iter);
			continue;
		}

		iter++;
	}
}

void EnemyManager::Draw()
{
	printfDx("Enemy Num: %d\n", m_enemies.size());
}

void EnemyManager::AddEnemy()
{
	auto enemy = new EnemyTest(m_objManager);
	enemy->Init();

	m_enemies.emplace_back(enemy);
}
