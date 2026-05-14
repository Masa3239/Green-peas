#pragma once

#include "../Object/GameObject.h"
#include "../Utility/Transform.h"
#include "../Chara/Collision.h"
#include "../Personal/Takagi/Weapon.h"
#include <array>
#include <vector>

class Player;
class EnemyManager;
class Map;

class EnemyBase : public GameObject
{
public:

	// 状態異常：痺れ
	constexpr static unsigned int kStatePalsy = (1 << 0);

	struct StatusParam
	{
		int hp;
		int maxHp;
		int attack;
		int defence;
		int exp;
	};

	EnemyBase(ObjectManager* objManager);
	virtual ~EnemyBase() = default;

	virtual void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 敵固有の更新処理
	/// </summary>
	virtual void UpdateEnemy() = 0;

	/// <summary>
	/// 状態異常を付与する
	/// </summary>
	/// <param name="state">状態異常のビット</param>
	void AddState(unsigned int state) { m_variableStatus |= state; }
	/// <summary>
	/// 状態異常の取得
	/// </summary>
	/// <param name="state">状態異常のビット</param>
	const unsigned int GetMyState() const { return m_variableStatus; }

	/// <summary>
	/// HPを取得
	/// </summary>
	int GetHP() const { return m_statusParam.hp; }
	
	/// <summary>
	/// ダメージを与える
	/// </summary>
	/// <param name="damage">ダメージ量</param>
	/// <param name="weapon">武器のID</param>
	/// <param name="index">武器のインデックス</param>
	/// <returns>ダメージを与えられたらtrue</returns>
	bool Damage(const int damage, int weapon, int index);

	/// <summary>
	/// 死亡処理
	/// </summary>
	virtual void Dead();

	/// <summary>
	/// ダメージフラグを下ろす
	/// </summary>
	/// <param name="weapon">武器ID</param>
	/// <param name="index">複数時の武器のインデックス</param>
	void ResetDamageFlag(int weapon, int index);

	int GetLevel() const { return m_level; }
	void SetLevel(const int level) { m_level = level; }

	const StatusParam& GetStatusParam() const { return m_statusParam; }
	void SetStatusParam(const StatusParam& status) { m_statusParam = status; }

	Player* GetPlayer() const { return m_pPlayer; }
	void SetPlayer(Player* player) { m_pPlayer = player; }

	void SetFixSpawn(const bool flag) { m_isFixSpawn = flag; }

	Collision::AABB& GetCollider() { return m_collider; }

	EnemyManager* GetEnemyManager() const { return m_pEnemyMgr; }
	void SetEnemyManager(EnemyManager* enemyMgr) { m_pEnemyMgr = enemyMgr; }

	void SetMap(Map* map) { m_pMap = map; }

protected:

	/// <summary>
	/// 攻撃処理
	/// </summary>
	virtual void Attack() = 0;

private:

	/// <summary>
	/// 状態異常の削除
	/// </summary>
	/// <param name="state">状態異常のビット</param>
	void RemoveState(unsigned int state) { m_variableStatus &= ~state; }

	/// <summary>
	/// 動きの更新をするかチェック
	/// </summary>
	bool CheckActive();

	/// <summary>
	/// 固定生成の敵に認識範囲を適用する
	/// </summary>
	bool ApplyRecognitionRange(float sqDistance);

	/// <summary>
	/// 自然生成の敵にデスポーン範囲を適用する
	/// </summary>
	bool ApplyDespawnRange(float sqDistance);

	/// <summary>
	/// マップ範囲内に収める
	/// </summary>
	void ClampInRange();

	/// <summary>
	/// マヒ状態にする
	/// </summary>
	/// <param name="weapon">武器ID</param>
	/// <returns>すでにマヒ状態ならtrue</returns>
	bool Paralyze(const int weapon);

	/// <summary>
	/// ダメージフラグの範囲外を使おうとしたら範囲を追加する
	/// </summary>
	void ResizeDamageFlag(int weapon, int index);

	/// <summary>
	/// プレイヤーが怒り状態のとき、
	/// プレイヤーを回復させる
	/// </summary>
	void HealPlayer();

	/// <summary>
	/// 経験値のドロップ処理
	/// </summary>
	void DropExp();

	/// <summary>
	/// 経験値を生成する
	/// </summary>
	/// <param name="amount">経験値量</param>
	void GenerateExp(int amount);

	/// <summary>
	/// ステータス
	/// </summary>
	StatusParam m_statusParam;

	/// <summary>
	/// 敵の強化レベル
	/// </summary>
	int m_level;

	/// <summary>
	/// 状態異常
	/// </summary>
	unsigned int m_variableStatus;

	/// <summary>
	/// 固定生成かどうか
	/// </summary>
	bool m_isFixSpawn;

	/// <summary>
	/// コライダー
	/// </summary>
	Collision::AABB m_collider;

	/// <summary>
	/// 武器ごとのダメージフラグ
	/// falseのときにはダメージを受けない
	/// </summary>
	std::array<std::vector<bool>, Weapon::Max> m_damageFlag;

	Player* m_pPlayer;
	EnemyManager* m_pEnemyMgr;
	Map* m_pMap;
};
