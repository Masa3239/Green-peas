#pragma once

#include "EnemyBase.h"

class EnemyMelee : public EnemyBase
{
public:

	EnemyMelee(ObjectManager* objManager);
	virtual ~EnemyMelee();

	/// <summary>
	/// ‰Šú‰»ˆ—
	/// </summary>
	void Init() override;

	/// <summary>
	/// Œãˆ—
	/// </summary>
	void End() override;

	/// <summary>
	/// XVˆ—
	/// </summary>
	void UpdateEnemy() override;

	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw() override;

protected:

	void Attack() override;
};
