#pragma once

#include "../Scene/SceneBase.h"
#include"Map/Map.h"
#include"EnemyMap/EnemyMap.h"

class Map;
class EnemyMap;
class SceneTestKimura : public SceneBase
{
public:

	SceneTestKimura();
	~SceneTestKimura();

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
	/// <returns></returns>
	SceneBase* Update() override;

	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw() override;
private:
	Map* m_pMap;
	EnemyMap* m_pEnemymap;
};
