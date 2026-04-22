#pragma once

#include "../Scene/SceneBase.h"
#include "../../Utility/Transform.h"
#include "BuffRandom.h"
#include <memory>

class EnemyBoss;
class Player;
class Camera;
class Map;
class ItemManager;
class EnemyManager;
class UIManager;
class WeaponManager;

class SceneTestSyoguti : public SceneBase
{
public:

	SceneTestSyoguti();
	~SceneTestSyoguti();

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

	void PreDraw()override;
	void PostDraw()override;

private:

	std::unique_ptr<ItemManager>m_pItemMgr;

	std::unique_ptr<EnemyBoss> m_pEnemyBoss;

	std::unique_ptr<Player> m_pPlayer;
	std::unique_ptr<Camera> m_pCamera;

	std::unique_ptr<WeaponManager> m_pWeaponMgr;

	std::unique_ptr<EnemyManager> m_pEnemyManager;
	std::unique_ptr<Map>m_pMap;

	std::unique_ptr<UIManager>m_pUIManager;


	std::vector<Buff::BuffType> m_testDraw;

	Transform m_transform;
	BuffRandom m_buffRandom;
};
