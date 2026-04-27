#include "EnemyManager.h"
#include <cmath>
#include <memory>
#include "EnemyBase.h"
#include "../Utility/Time.h"
#include "../Utility/MyMath.h"
#include "../Personal/Takagi/Player.h"
#include "../Personal/Takagi/WeaponManager.h"
#include "../Personal/Asai/UIManager.h"
#include "../Personal/Syoguti/EnemyBoss.h"
#include "../Utility/MyRandom.h"
#include "../Personal/Kimura/EnemyMap/EnemyMap.h"

#include "EnemyMelee.h"
#include "EnemyShooter.h"
#include "EnemyMiniBoss.h"
#include <DxLib.h>

namespace
{
	// 自動生成される敵の最大数
	constexpr int kMaxEnemyNum = 1000;
	// 自動生成される敵の最小数
	constexpr int kMinEnemyNum = 30;

	// 敵生成の間隔
	constexpr float kGenerateDuration = 1.5f;
	
	// 生成時にプレイヤーから離す距離
	constexpr float kGenerateOffsetPos = 500.0f;

	constexpr float kWeaponDropChange = 20.0f;
}

EnemyManager::EnemyManager(ObjectManager* objManager) :
	GameObject(objManager),
	m_enemyBoss(nullptr),
	m_pPlayer(nullptr),
	m_uiMgr(nullptr),
	m_weaponMgr(nullptr),
	m_chestMgr(nullptr),
	m_generateCounter(0.0f),
	m_highestDamage(0),
	m_numDefeated(0)
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	//GenerateEnemy(EnemyType::Miniboss, 1);

	m_enemyBoss = std::make_unique<EnemyBoss>(GetObjectManager(), Vector3(5000, 300, 0));
	m_enemyBoss->SetPlayer(m_pPlayer);
	m_enemyBoss->Init();
}

void EnemyManager::End()
{
	for (auto& enemy : m_enemies)
	{
		enemy->End();
	}

	m_enemyBoss->End();
}

void EnemyManager::Update()
{
	if ((m_generateCounter <= 0 || m_enemies.size() <= kMinEnemyNum) && m_enemies.size() <= kMaxEnemyNum)
	{
		// 敵を生成
		if (MyRandom::Int(0, 1) == 0)
			GenerateEnemy(EnemyType::Melee, MyRandom::Int(m_pPlayer->GetLevel() - 1, m_pPlayer->GetLevel() + 1));
		else
			GenerateEnemy(EnemyType::Shooter, MyRandom::Int(m_pPlayer->GetLevel() - 1, m_pPlayer->GetLevel() + 1));

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

std::vector<EnemyBase*> EnemyManager::GetHitEnemies(const Collision::Shape& shape, const unsigned int elimState)
{
	std::vector<EnemyBase*> enemies;

	for (const auto& enemy : m_enemies)
	{
		if (enemy->GetMyState() & elimState) continue;

		if (!enemy->GetCollider().CheckCollision(shape)) continue;

		enemies.emplace_back(enemy.get());
	}

	return enemies;
}

bool EnemyManager::CheckHitEnemies(const Collision::Shape& shape, const float damage, const float criticalChance, const float criticalDamage, int weapon, int index)
{
	bool result = false;

	int finalDamage = 0;

	PopUpUI::TextType textType = PopUpUI::TextType::Damage;

	for (const auto& enemy : m_enemies)
	{
		if (!enemy->GetCollider().CheckCollision(shape)) continue;

		finalDamage = damage;
		textType = PopUpUI::TextType::Damage;

		if (GetRand(100) < criticalChance)
		{
			finalDamage *= criticalDamage;
			textType = PopUpUI::TextType::Critical;
		}

		// ダメージを与えられなかったらスキップ
		if (!enemy->Damage(finalDamage, weapon, index)) continue;

		m_uiMgr->CreatePopUpText(enemy->GetTransform().position, finalDamage, textType);

		// 最高ダメージを更新する
		if (m_highestDamage < finalDamage) m_highestDamage = finalDamage;

		// 誰か一人でも当たっていたらtrueになる
		result = true;
	}

	if (m_enemyBoss->GetCollider().CheckCollision(shape))
	{
		finalDamage = damage;
		textType = PopUpUI::TextType::Damage;

		if (GetRand(100) < criticalChance)
		{
			finalDamage *= criticalDamage;
			textType = PopUpUI::TextType::Critical;
		}

		// ダメージを与えられなかったらスキップ
		if (!m_enemyBoss->Damage(finalDamage, weapon, index)) return result;

		m_uiMgr->CreatePopUpText(m_enemyBoss->GetTransform().position, finalDamage, textType);

		// 最高ダメージを更新する
		if (m_highestDamage < finalDamage) m_highestDamage = finalDamage;

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

	m_enemyBoss->ResetDamageFlag(weapon, index);

	return false;
}

std::vector<Vector3> EnemyManager::GetMiniBossPositions() const
{
	std::vector<Vector3> positions;

	for (const auto& enemy : m_miniBosses)
	{
		positions.emplace_back(enemy->GetTransform().position);
	}

	return positions;
}

EnemyBase* EnemyManager::GenerateEnemy(EnemyType type, int level)
{
	std::unique_ptr<EnemyBase> enemy;
	switch (type)
	{
	case EnemyManager::EnemyType::Melee:	enemy = std::make_unique<EnemyMelee>(GetObjectManager()); break;
	case EnemyManager::EnemyType::Shooter:	enemy = std::make_unique<EnemyShooter>(GetObjectManager()); break;
	case EnemyManager::EnemyType::Miniboss:	enemy = std::make_unique<EnemyMiniBoss>(GetObjectManager()); break;
	}
	enemy->SetPlayer(m_pPlayer);
	enemy->SetEnemyManager(this);
	enemy->SetLevel(level);
	enemy->Init();

	// 生成座標が範囲内になるまで繰り返す
	Vector3 playerPos = m_pPlayer->GetTransform().position;
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

	if (type == EnemyType::Miniboss) m_miniBosses.emplace_back(dynamic_cast<EnemyMiniBoss*>(enemy.get()));
	return m_enemies.emplace_back(std::move(enemy)).get();
}

EnemyBase* EnemyManager::GenerateEnemy(EnemyType type, Vector3 pos, int level)
{
	std::unique_ptr<EnemyBase> enemy;
	switch (type)
	{
	case EnemyManager::EnemyType::Melee:	enemy = std::make_unique<EnemyMelee>(GetObjectManager()); break;
	case EnemyManager::EnemyType::Shooter:	enemy = std::make_unique<EnemyShooter>(GetObjectManager()); break;
	case EnemyManager::EnemyType::Miniboss:	enemy = std::make_unique<EnemyMiniBoss>(GetObjectManager()); break;
	}
	enemy->SetPlayer(m_pPlayer);
	enemy->SetEnemyManager(this);
	enemy->SetLevel(level);
	enemy->Init();

	enemy->GetTransform().position = pos;

	if (type == EnemyType::Miniboss) m_miniBosses.emplace_back(dynamic_cast<EnemyMiniBoss*>(enemy.get()));
	return m_enemies.emplace_back(std::move(enemy)).get();
}

void EnemyManager::InitGenerate(EnemyMap* enemyMap)
{
	auto& enemies = enemyMap->GetSpawnList();

	for (const auto& status : enemies)
	{
		auto enemy = GenerateEnemy(status.type, status.pos, status.level);
		enemy->SetFixSpawn(true);
	}
}

void EnemyManager::RemoveEnemy(EnemyBase* enemy)
{
	enemy->SetState(GameObject::State::Dead);

	for (auto iter = m_enemies.begin(); iter != m_enemies.end(); iter++)
	{
		if (iter->get() != enemy) continue;

		m_enemies.erase(iter);

		break;
	}
}

void EnemyManager::CheckDead()
{
	// 死亡判定
	// オブジェクトマネージャー側
	// マネージャー側で死亡判定を行う
	for (const auto& enemy : m_enemies)
	{
		if (enemy->GetHP() > 0) continue;

		enemy->Dead();
		enemy->SetState(GameObject::State::Dead);

		if (MyRandom::Judge(kWeaponDropChange))
		{
			int weapon = MyRandom::Int(Weapon::Sword, Weapon::Max - 1);
			m_weaponMgr->Create(enemy->GetTransform().position, weapon);
		}
	}
	// 死亡していたら配列から削除
	for (auto iter = m_enemies.begin(); iter != m_enemies.end();)
	{
		EnemyBase* enemy = iter->get();
		if (enemy->GetHP() <= 0)
		{
			iter = m_enemies.erase(iter);
			m_numDefeated++;
			continue;
		}

		iter++;
	}
}
