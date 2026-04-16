#pragma once

#include "../Object/GameObject.h"
#include "../Utility/Transform.h"
#include "../Chara/Collision.h"

class Player;

class EnemyBase : public GameObject
{
public:

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
	/// HPを取得
	/// </summary>
	int GetHP() const { return m_hp; }
	/// <summary>
	/// HPを設定
	/// </summary>
	void SetHP(const int hp) { m_hp = hp; }
	/// <summary>
	/// ダメージを与える
	/// </summary>
	/// <param name="damage">ダメージ量</param>
	void Damage(const int damage) { m_hp -= damage; }

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
	/// プレイヤーのポインタ
	/// </summary>
	Player* m_player;
};
