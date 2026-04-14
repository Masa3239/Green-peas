#pragma once

#include <memory>
#include <vector>

class ObjectManager;
class EnemyBase;

class EnemyManager
{
public:

	EnemyManager(ObjectManager* objManager);
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

	ObjectManager* m_objManager;

	/// <summary>
	/// “G‚Ì”z—ñ
	/// </summary>
	std::vector<EnemyBase*> m_enemies;
};
