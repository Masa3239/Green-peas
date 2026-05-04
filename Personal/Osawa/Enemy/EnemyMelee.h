#pragma once

#include "EnemyBase.h"
#include "../Chara/AnimationController2D.h"

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

protected:

	void Attack() override;

private:

	void UpdateAnimation();

	void ChangeAnimation(AnimType next);

	/// <summary>
	/// 攻撃クールタイムのカウンター
	/// </summary>
	float m_attackCooltimeCounter;

	AnimationController2D m_animationController;

	AnimType m_currentAnimation;
};
