#pragma once

#include <memory>
#include <vector>
#include "../Object/GameObject.h"
#include "../Chara/Collision.h"

class ObjectManager;
class EnemyBase;
class Player;

class EnemyManager : public GameObject
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

	/// <summary>
	/// コライダーが敵に触れているかチェック
	/// </summary>
	/// <param name="shape">コライダー</param>
	/// <param name="damage">ダメージ量</param>
	/// <returns>敵に触れていたらtrue</returns>
	bool CheckHitEnemies(const Collision::Shape& shape, int damage);

	void AddEnemyTest();

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
