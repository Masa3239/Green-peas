#pragma once

#include "EnemyBase.h"

class EnemyMiniBoss : public EnemyBase
{
public:

	EnemyMiniBoss(ObjectManager* objManager);
	virtual ~EnemyMiniBoss();

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
};
