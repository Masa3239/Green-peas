#pragma once

#include <memory>
#include <vector>
#include "../Object/GameObject.h"
#include "../Chara/Collision.h"

class ObjectManager;
class EnemyBase;
class EnemyMiniBoss;
class Player;
class UIManager;

class EnemyManager : public GameObject
{
public:

	EnemyManager(ObjectManager* objManager);
	~EnemyManager();

	enum class EnemyType
	{
		Melee,		// 近距離
		Shooter,	// 遠距離
		Miniboss,	// 中ボス
	};

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
	/// <param name="weapon">武器のID</param>
	/// <param name="index">武器のインデックス</param>
	/// <returns>敵に触れていたらtrue</returns>
	bool CheckHitEnemies(const Collision::Shape& shape, const float damage, const float criticalChance, const float criticalDamage, int weapon, int index);

	bool ResetEnemyDamageFlag(int weapon, int index);

	/// <summary>
	/// 中ボスの座標を取得
	/// </summary>
	std::vector<Vector3> GetMiniBossPositions() const;

	/// <summary>
	/// 敵をプレイヤーの周りに生成する
	/// </summary>
	/// <param name="type">生成したい敵の種類</param>
	void GenerateEnemy(EnemyType type);

	/// <summary>
	/// 敵を生成する
	/// </summary>
	/// <param name="type">生成したい敵の種類</param>
	/// <param name="pos">生成する場所</param>
	void GenerateEnemy(EnemyType type, Vector3 pos);

	void SetPlayer(Player* player) { m_pPlayer = player; }

	void SetUIManager(UIManager* uiMgr) { m_uiMgr = uiMgr; }

private:

	/// <summary>
	/// 死亡判定
	/// </summary>
	void CheckDead();

	/// <summary>
	/// 敵の配列
	/// </summary>
	std::vector<std::unique_ptr<EnemyBase>> m_enemies;

	/// <summary>
	/// 中ボスの配列
	/// </summary>
	std::vector<EnemyMiniBoss*> m_miniBosses;

	Player* m_pPlayer;

	UIManager* m_uiMgr;

	/// <summary>
	/// 敵の生成待機のカウンター
	/// </summary>
	float m_generateCounter;

public:
	int GetDefeatedNum() const { return m_numDefeated; }
private:
	int m_numDefeated;
};
