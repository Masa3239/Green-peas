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

	/// <summary>
	/// 敵をプレイヤーの周りに生成する
	/// </summary>
	/// <param name="enemy">敵のインスタンス</param>
	void GenerateEnemy(EnemyBase* enemy);

	/// <summary>
	/// 死亡判定
	/// </summary>
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
