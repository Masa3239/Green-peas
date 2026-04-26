#pragma once

#include "EnemyBase.h"
#include <array>
#include <memory>

class EnemyBullet;

class EnemyShooter : public EnemyBase
{
public:

	EnemyShooter(ObjectManager* objManager);
	virtual ~EnemyShooter();

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

	int m_graphs[8];
};
