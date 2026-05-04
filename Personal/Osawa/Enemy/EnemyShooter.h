#pragma once

#include "EnemyBase.h"
#include <array>
#include <memory>
#include "../Chara/AnimationController2D.h"

class EnemyBullet;

class EnemyShooter : public EnemyBase
{
public:

	EnemyShooter(ObjectManager* objManager);
	virtual ~EnemyShooter();

	enum AnimType
	{
		EIdle,
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

protected:

	void Attack() override;

private:

	constexpr static unsigned int kMaxBulletNum = 10;

	constexpr static int kAnimFrameNum = 1;

	enum class Action
	{
		Idle,
		Follow,
		Distance,
		Back,
	};

	void UpdateAnimation();

	void ChangeAnimation(AnimType next);

	Action m_action;

	/// <summary>
	/// 攻撃クールタイムのカウンター
	/// </summary>
	float m_attackCooltimeCounter;

	/// <summary>
	/// 弾の配列
	/// </summary>
	std::array<std::unique_ptr<EnemyBullet>, kMaxBulletNum> m_bullets;
	
	AnimationController2D m_animationController;

	AnimType m_currentAnimation;
};
