#pragma once

#include <memory>
#include <vector>
#include "../Object/GameObject.h"
#include "../Chara/Collision.h"

class ObjectManager;
class EnemyBase;
class Player;
class UIManager;

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
	/// コライダーに触れている敵を取得する
	/// </summary>
	/// <param name="shape">コライダー</param>
	/// <param name="elimState">判定に省きたい状態異常 EnemyBase::kState〇〇</param>
	std::vector<EnemyBase*> GetHitEnemies(const Collision::Shape& shape, const unsigned int elimState);

	/// <summary>
	/// コライダーが敵に触れているかチェック
	/// </summary>
	/// <param name="shape">コライダー</param>
	/// <param name="damage">ダメージ量</param>
	/// <returns>敵に触れていたらtrue</returns>
	bool CheckHitEnemies(const Collision::Shape& shape, int damage);

	/// <summary>
	/// コライダーが敵に触れているかチェック
	/// </summary>
	/// <param name="shape">コライダー</param>
	/// <param name="damage">基礎ダメージ量</param>
	/// <param name="criticalChance">クリティカル率</param>
	/// <param name="criticalDamage">クリティカルダメージ</param>
	/// <returns>敵に触れていたらtrue</returns>
	bool CheckHitEnemies(const Collision::Shape& shape, const float damage, const float criticalChance, const float criticalDamage);

	void AddEnemyTest();

	void SetPlayer(Player* player) { m_player = player; }

	void SetUIManager(UIManager* uiMgr) { m_uiMgr = uiMgr; }

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

	UIManager* m_uiMgr;

	/// <summary>
	/// 敵の生成待機のカウンター
	/// </summary>
	float m_generateCounter;

public:
	int GetDefeatedNum() const { return m_numDefeated; }
private:
	// α版用
	// 倒された敵の数
	int m_numDefeated;
};
