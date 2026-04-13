#pragma once

#include "EnemyBase.h"

class EnemyTest : public EnemyBase
{
public:

	EnemyTest();
	virtual ~EnemyTest();

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
};
