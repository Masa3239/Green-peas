#pragma once

#include <memory>
#include <vector>

class EnemyBase;

class EnemyManager
{
public:

	EnemyManager();
	~EnemyManager();

	/// <summary>
	/// ‰Šú‰»ˆ—
	/// </summary>
	void Init();

	/// <summary>
	/// Œãˆ—
	/// </summary>
	void End();

	/// <summary>
	/// XVˆ—
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw();

	void AddEnemy();

private:

	/// <summary>
	/// “G‚Ì”z—ñ
	/// </summary>
	std::vector<std::unique_ptr<EnemyBase>> m_enemies;
};
