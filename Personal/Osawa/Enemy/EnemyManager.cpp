#include "EnemyManager.h"
#include "EnemyBase.h"

#include "EnemyTest.h"
#include <DxLib.h>

EnemyManager::EnemyManager()
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

		m_enemies.back().get()->SetHP(0);
	}

	for (auto& enemy : m_enemies)
	{
		enemy->Update();
	}

	for (auto iter = m_enemies.begin(); iter != m_enemies.end();)
	{
		if (iter->get()->GetState() == EnemyBase::State::Dead)
		{
			iter = m_enemies.erase(iter);
			continue;
		}

		iter++;
	}
}

void EnemyManager::Draw()
{
	for (auto& enemy : m_enemies)
	{
		enemy->Draw();
	}

	printfDx("Enemy Num: %d\n", m_enemies.size());
}

void EnemyManager::AddEnemy()
{
	auto enemy = std::make_unique<EnemyTest>();
	enemy->Init();

	m_enemies.emplace_back(std::move(enemy));
}
