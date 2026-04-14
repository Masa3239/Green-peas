#pragma once

#include <memory>
#include <vector>

class ObjectManager;
class EnemyBase;
class Player;

class EnemyManager
{
public:

	EnemyManager(ObjectManager* objManager);
	~EnemyManager();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 後処理
	/// </summary>
	void End();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	void AddEnemy();

	void SetPlayer(Player* player) { m_player = player; }

private:

	template <class T>
	void GenerateEnemy();

	void CheckDead();

	ObjectManager* m_objManager;

	/// <summary>
	/// 敵の配列
	/// </summary>
	std::vector<EnemyBase*> m_enemies;

	Player* m_player;

	/// <summary>
	/// 敵の生成待機のカウンター
	/// </summary>
	float m_generateCounter;
};

template<class T>
inline void EnemyManager::GenerateEnemy()
{
	auto enemy = new T(m_objManager);
	enemy->Init();
	enemy->SetPlayer(m_player);

	m_enemies.emplace_back(enemy);
}
