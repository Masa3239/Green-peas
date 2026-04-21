#pragma once

#include <memory>
#include "../Scene/SceneBase.h"

class Player;
class Camera;
class EnemyManager;
class UIManager;
class Map;
class ItemManager;
class WeaponManager;

class SceneTestOsawa : public SceneBase
{
public:

	SceneTestOsawa();
	~SceneTestOsawa();

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
	/// <returns></returns>
	SceneBase* Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

	void PreDraw() override;

	void PostDraw() override;

private:

	/// <summary>
	/// プレイヤー
	/// </summary>
	std::unique_ptr<Player> m_pPlayer;

	/// <summary>
	/// カメラ
	/// </summary>
	std::unique_ptr<Camera> m_pCamera;

	/// <summary>
	/// 敵のマネージャー
	/// </summary>
	std::unique_ptr<EnemyManager> m_pEnemyMgr;

	/// <summary>
	/// UIのマネージャー
	/// </summary>
	std::unique_ptr<UIManager> m_pUIMgr;

	/// <summary>
	/// アイテムのマネージャー
	/// </summary>
	std::unique_ptr<ItemManager> m_pItemMgr;

	/// <summary>
	/// マップ
	/// </summary>
	std::unique_ptr<Map> m_pMap;

	std::unique_ptr<WeaponManager> m_pWeaponManager;
};
