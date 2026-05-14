#pragma once

#include "EnemyBase.h"
#include <memory>

class EnemyBullet;

class EnemyMiniBoss : public EnemyBase
{
public:

	EnemyMiniBoss(ObjectManager* objManager);
	~EnemyMiniBoss();

	enum AnimType
	{
		ERun,
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

	/// <summary>
	/// 死亡処理
	/// </summary>
	void Dead() override;

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

	constexpr static unsigned int kMaxBulletNum = 10;

	enum class Action
	{
		Idle,
		Melee,
		Follow,
		Distance,
		Back,
		Length
	};

	Action m_action;

	/// <summary>
	/// 攻撃クールタイムのカウンター
	/// </summary>
	float m_attackCooltimeCounter;

	/// <summary>
	/// 弾の配列
	/// </summary>
	std::array<std::unique_ptr<EnemyBullet>, kMaxBulletNum> m_bullets;
};
