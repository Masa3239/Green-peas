#include "EnemyManager.h"
#include <cmath>
#include "EnemyBase.h"
#include "../Utility/Time.h"
#include "../Utility/MyMath.h"
#include "../Personal/Takagi/Player.h"
#include "../Personal/Asai/UIManager.h"

#include "EnemyMelee.h"
#include "EnemyShooter.h"
#include "EnemyMiniBoss.h"
#include <DxLib.h>

namespace
{
	// 自動生成される敵の最大数
	constexpr int kMaxEnemyNum = 100;

	// 敵生成の間隔
	constexpr float kGenerateDuration = 0.5f;

	// 生成時にプレイヤーから離す距離
	constexpr float kGenerateOffsetPos = 500.0f;
}

EnemyManager::EnemyManager(ObjectManager* objManager) :
	GameObject(objManager),
	m_player(nullptr),
	m_uiMgr(nullptr),
	m_generateCounter(0.0f),
	m_numDefeated(0)
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	//GenerateEnemy(new EnemyMiniBoss(GetObjectManager()));
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
	if (m_generateCounter <= 0 && m_enemies.size() <= kMaxEnemyNum)
	{
		// 敵を生成
		GenerateEnemy(new EnemyMelee(GetObjectManager()));
		//GenerateEnemy(new EnemyShooter(GetObjectManager()));

		m_generateCounter = kGenerateDuration;
	}
	else
	{
		m_generateCounter -= Time::GetInstance().GetDeltaTime();
	}

	m_enemies[0]->AddState(EnemyBase::kStatePalsy);

	CheckDead();
}

void EnemyManager::Draw()
{
	printfDx("Enemy Num: %d\n", m_enemies.size());
}

std::vector<EnemyBase*> EnemyManager::GetHitEnemies(const Collision::Shape& shape, const unsigned int elimState)
{
	std::vector<EnemyBase*> enemies;

	for (const auto& enemy : m_enemies)
	{
		if (enemy->GetMyState() & elimState) continue;

		if (!enemy->GetCollider().CheckCollision(shape)) continue;

		enemies.emplace_back(enemy);
	}

	return enemies;
}

bool EnemyManager::CheckHitEnemies(const Collision::Shape& shape, int damage)
{
	bool result = false;

	for (const auto& enemy : m_enemies)
	{
		if (!enemy->GetCollider().CheckCollision(shape)) continue;
		
		// ダメージを与えられなかったらスキップ
		if (!enemy->Damage(damage)) continue;

		m_uiMgr->CreateDamagePopUpText(enemy->GetTransform().position, damage);

		// 誰か一人でも当たっていたらtrueになる
		result = true;
	}

	return result;
}

bool EnemyManager::CheckHitEnemies(const Collision::Shape& shape, const float damage, const float criticalChance, const float criticalDamage, int weapon, int index)
{
	bool result = false;

	int finalDamage = 0;

	for (const auto& enemy : m_enemies)
	{
		if (!enemy->GetCollider().CheckCollision(shape)) continue;

		finalDamage = damage;

		if (GetRand(100) < criticalChance)
		{
			finalDamage *= criticalDamage;
		}

		// ダメージを与えられなかったらスキップ
		if (!enemy->Damage(finalDamage, weapon, index)) continue;

		m_uiMgr->CreateDamagePopUpText(enemy->GetTransform().position, finalDamage);

		// 誰か一人でも当たっていたらtrueになる
		result = true;
	}

	return result;
}

bool EnemyManager::ResetEnemyDamageFlag(int weapon, int index)
{
	for (const auto& enemy : m_enemies)
	{
		enemy->ResetDamageFlag(weapon, index);
	}

	return false;
}

void EnemyManager::AddEnemyTest()
{
	auto enemy = new EnemyMelee(GetObjectManager());
	enemy->Init();
	enemy->SetPlayer(m_player);

	m_enemies.emplace_back(enemy);
}

void EnemyManager::GenerateEnemy(EnemyBase* enemy)
{
	enemy->Init();
	enemy->SetPlayer(m_player);

	// 生成座標が範囲内になるまで繰り返す
	Vector3 playerPos = m_player->GetTransform().position;
	Vector3 pos;
	while (true)
	{
		float dir = MyMath::DegToRad(GetRand(360));
		pos = playerPos;
		pos.x += std::sin(dir) * kGenerateOffsetPos;
		pos.y += std::cos(dir) * kGenerateOffsetPos;

		// 範囲内なら決定
		if (pos.x >= 0 && pos.y >= 0) break;
	}
	enemy->GetTransform().position = pos;

	m_enemies.emplace_back(enemy);
}

void EnemyManager::CheckDead()
{
	// 死亡判定
	// オブジェクトマネージャー側
	// マネージャー側で死亡判定を行う
	for (const auto& enemy : m_enemies)
	{
		if (enemy->GetHP() > 0) continue;

		enemy->SetState(GameObject::State::Dead);
	}
	// 死亡していたら配列から削除
	for (auto iter = m_enemies.begin(); iter != m_enemies.end();)
	{
		EnemyBase* enemy = *iter;
		if (enemy->GetHP() <= 0)
		{
			iter = m_enemies.erase(iter);
			m_numDefeated++;
			continue;
		}

		iter++;
	}
}
