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
		if (m_enemies.size() <= 0) return;

		m_enemies.back().get()->SetHP(0);
	}

	for (auto& enemy : m_enemies)
	{
		enemy->Update();
	}

	std::vector<std::unique_ptr<EnemyBase>> deadEnemies;
	for (auto& enemy : m_enemies)
	{
		if (enemy->GetState() == EnemyBase::State::Dead)
		{

		}
	}
}

void EnemyManager::Draw()
{
	for (auto& enemy : m_enemies)
	{
		enemy->Draw();
	}
}

void EnemyManager::AddEnemy()
{
	auto enemy = std::make_unique<EnemyTest>();
	enemy->Init();

	m_enemies.emplace_back(std::move(enemy));
}
