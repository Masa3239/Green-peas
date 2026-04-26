#pragma once

#include "EnemyBase.h"

class EnemyMelee : public EnemyBase
{
public:

	EnemyMelee(ObjectManager* objManager);
	virtual ~EnemyMelee();

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

	constexpr static int kAnimFrameNum = 1;

	/// <summary>
	/// 攻撃クールタイムのカウンター
	/// </summary>
	float m_attackCooltimeCounter;

	int m_animFrame;

	float m_animFrameCounter;

	int m_graphs[8];
};
