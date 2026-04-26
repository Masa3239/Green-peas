#pragma once
#include "../Scene/SceneBase.h"
#include"../../System/InputPad.h"
#include<memory>
class Player;
class Camera;
class Map;
class ItemManager;
class EnemyManager;
class UIManager;
class WeaponManager;
class PauseMenu;
class BuffManager;
class ResultShow;

class SceneTestTakagi : public SceneBase
{
public:

	SceneTestTakagi();
	~SceneTestTakagi();

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
	std::unique_ptr<Player> m_pPlayer;
	std::unique_ptr<Camera> m_pCamera;

	std::unique_ptr<EnemyManager> m_pEnemyManager;
	std::unique_ptr<ItemManager> m_pItemManager;
	std::unique_ptr<Map>m_pMap;

	std::unique_ptr<UIManager>m_pUIManager;
	std::unique_ptr<WeaponManager>m_pWeaponManager;
	std::unique_ptr<PauseMenu>m_pPauseMenu;
	std::unique_ptr<BuffManager>m_pBuffManager;
	std::unique_ptr<ResultShow>m_pResultShow;
};
