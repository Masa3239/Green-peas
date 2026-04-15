#include "EnemyManager.h"
#include <cmath>
#include "EnemyBase.h"
#include "../Utility/Time.h"
#include "../Utility/MyMath.h"
#include "../Personal/Takagi/Player.h"

#include "EnemyMelee.h"
#include <DxLib.h>

namespace
{
	// “G¶¬‚ÌŠÔŠu
	constexpr float kGenerateDuration = 0.5f;

	// ¶¬Žž‚ÉƒvƒŒƒCƒ„[‚©‚ç—£‚·‹——£
	constexpr float kGenerateOffsetPos = 500.0f;
}

EnemyManager::EnemyManager(ObjectManager* objManager) :
	m_objManager(objManager),
	m_player(nullptr),
	m_generateCounter(0.0f)
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

	if (m_generateCounter <= 0)
	{
		// “G‚ð¶¬
		GenerateEnemy(new EnemyMelee(m_objManager));

		m_generateCounter = kGenerateDuration;
	}
	else
	{
		m_generateCounter -= Time::GetInstance().GetDeltaTime();
	}

	CheckDead();
}

void EnemyManager::Draw()
{
	printfDx("Enemy Num: %d\n", m_enemies.size());
}

void EnemyManager::AddEnemy()
{
	auto enemy = new EnemyMelee(m_objManager);
	enemy->Init();
	enemy->SetPlayer(m_player);

	m_enemies.emplace_back(enemy);
}

void EnemyManager::GenerateEnemy(EnemyBase* enemy)
{
	enemy->Init();
	enemy->SetPlayer(m_player);

	// ¶¬À•W‚ª”ÍˆÍ“à‚É‚È‚é‚Ü‚ÅŒJ‚è•Ô‚·
	Vector3 playerPos = m_player->GetTransform().position;
	Vector3 pos;
	while (true)
	{
		float dir = MyMath::DegToRad(GetRand(360));
		pos = playerPos;
		pos.x += std::sin(dir) * kGenerateOffsetPos;
		pos.y += std::cos(dir) * kGenerateOffsetPos;

		// ”ÍˆÍ“à‚È‚çŒˆ’è
		if (pos.x >= 0 && pos.y >= 0) break;
	}
	enemy->GetTransform().position = pos;

	m_enemies.emplace_back(enemy);
}

void EnemyManager::CheckDead()
{
	// Ž€–S”»’è
	for (const auto& enemy : m_enemies)
	{
		if (enemy->GetHP() > 0) continue;

		enemy->SetState(GameObject::State::Dead);
	}
	// Ž€–S‚µ‚Ä‚¢‚½‚ç”z—ñ‚©‚çíœ
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
