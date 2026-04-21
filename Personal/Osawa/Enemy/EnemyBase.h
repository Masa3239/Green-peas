#pragma once

#include "../Object/GameObject.h"
#include "../Utility/Transform.h"
#include "../Chara/Collision.h"
#include <array>

class Player;

class EnemyBase : public GameObject
{
public:

	// 状態異常：痺れ
	constexpr static unsigned int kStatePalsy = (1 << 0);

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
	const unsigned int GetMyState() { return m_variableStatus; }

	/// <summary>
	/// HPを取得
	/// </summary>
	int GetHP() const { return m_hp; }
	
	/// <summary>
	/// ダメージを与える
	/// </summary>
	/// <param name="damage">ダメージ量</param>
	/// <returns>ダメージを与えられたらtrue</returns>
	bool Damage(const int damage);

	Player* GetPlayer() const { return m_player; }
	void SetPlayer(Player* player) { m_player = player; }

	const Collision::AABB& GetCollider() const { return m_collider; }

protected:

	void SetAttackCooltime(const float time) { m_attackCooltime = time; }

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
	/// 自身のHP
	/// </summary>
	int m_hp;

	/// <summary>
	/// コライダー
	/// </summary>
	Collision::AABB m_collider;

	/// <summary>
	/// 攻撃クールタイムのカウンター
	/// </summary>
	float m_attackCooltimeCounter;

	/// <summary>
	/// 攻撃クールタイムの時間
	/// </summary>
	float m_attackCooltime;

	/// <summary>
	/// 無敵時間のカウンタ
	/// </summary>
	float m_invCounter;

	/// <summary>
	/// 状態異常
	/// </summary>
	unsigned int m_variableStatus;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	Player* m_player;
};
