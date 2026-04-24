#pragma once

#include "../Object/GameObject.h"
#include "../Utility/Transform.h"
#include "../Chara/Collision.h"
#include "../Personal/Takagi/Weapon.h"
#include <array>
#include <vector>

class Player;
class EnemyManager;

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
	virtual ~EnemyBase();

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
	/// <returns>ダメージを与えられたらtrue</returns>
	bool Damage(const int damage);
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

	bool ResetDamageFlag(int weapon, int index);

	int GetLevel() const { return m_level; }
	void SetLevel(const int level) { m_level = level; }

	const StatusParam& GetStatusParam() const { return m_statusParam; }

	Player* GetPlayer() const { return m_pPlayer; }
	void SetPlayer(Player* player) { m_pPlayer = player; }

	const Collision::AABB& GetCollider() const { return m_collider; }

	EnemyManager* GetEnemyManager() const { return m_pEnemyMgr; }
	void SetEnemyManager(EnemyManager* enemyMgr) { m_pEnemyMgr = enemyMgr; }

protected:

	/// <summary>
	/// 攻撃処理
	/// </summary>
	virtual void Attack() = 0;

	void SetStatusParam(const StatusParam& status) { m_statusParam = status; }

private:

	/// <summary>
	/// 状態異常の削除
	/// </summary>
	/// <param name="state">状態異常のビット</param>
	void RemoveState(unsigned int state) { m_variableStatus &= ~state; }

	/// <summary>
	/// ダメージフラグの範囲外を使おうとしたら範囲を追加する
	/// </summary>
	void CheckDamageFlagSize(int weapon, int index);

	/// <summary>
	/// コライダー
	/// </summary>
	Collision::AABB m_collider;

	std::array<std::vector<bool>, Weapon::Max> m_damageFlag;

	int m_level;

	/// <summary>
	/// パラメータ
	/// </summary>
	StatusParam m_statusParam;

	/// <summary>
	/// 状態異常
	/// </summary>
	unsigned int m_variableStatus;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	Player* m_pPlayer;

	EnemyManager* m_pEnemyMgr;
};
