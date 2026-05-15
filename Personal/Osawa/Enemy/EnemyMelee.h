#pragma once

#include "EnemyBase.h"

class EnemyMelee : public EnemyBase
{
public:

	EnemyMelee(ObjectManager* objManager);
	virtual ~EnemyMelee();

	enum AnimType
	{
		EIdle,
		ERun,
		EAttack,
		Length
	};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 後処理
	/// </summary>
	void End() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void UpdateEnemy() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

	const Collision::Shape& GetCollider() override { return m_collider; }

protected:

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Attack() override;

	/// <summary>
	/// アニメーションの切り替え処理
	/// </summary>
	void BranchAnimation() override;

private:

	/// <summary>
	/// 攻撃クールタイムのカウンター
	/// </summary>
	float m_attackCooltimeCounter;

	/// <summary>
	/// 衝突判定
	/// </summary>
	Collision::AABB m_collider;
};
