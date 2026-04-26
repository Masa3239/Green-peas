#pragma once

#include "EnemyBase.h"
#include <memory>

class EnemyBullet;

class EnemyMiniBoss : public EnemyBase
{
public:

	EnemyMiniBoss(ObjectManager* objManager);
	~EnemyMiniBoss();

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

	void Dead() override;

protected:

	void Attack() override;

	constexpr static unsigned int kMaxBulletNum = 10;

	constexpr static int kAnimFrameNum = 8;

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

	int m_animFrame;

	float m_animFrameCounter;

	int m_graphs[kAnimFrameNum];
};
