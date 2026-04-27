#pragma once

#include <memory>
#include "SceneBase.h"

class Player;
class Camera;
class EnemyManager;
class UIManager;
class Map;
class EnemyMap;
class ItemManager;
class WeaponManager;
class PauseMenu;
class BuffManager;
class ChestManager;
class ResultShow;

/// <summary>
/// メインのゲームシーン
/// </summary>
class SceneInGame : public SceneBase
{
public:

	SceneInGame();
	~SceneInGame();

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

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw() override;

	/// <summary>
	/// 描画後処理
	/// </summary>
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
	/// <summary>
	/// マップ敵情報
	/// </summary>
	std::unique_ptr<EnemyMap> m_pEnemyMap;

	/// <summary>
	/// 武器のマネージャー
	/// </summary>
	std::unique_ptr<WeaponManager> m_pWeaponManager;

	/// <summary>
	/// ポーズメニュー
	/// </summary>
	std::unique_ptr<PauseMenu> m_pPauseMenu;
	
	/// <summary>
	/// バフのマネージャー
	/// </summary>
	std::unique_ptr<BuffManager>m_pBuffManager;

	/// <summary>
	/// 宝箱のマネージャー
	/// </summary>
	std::unique_ptr<ChestManager> m_pChestManager;

	std::unique_ptr<ResultShow>m_pResultShow;
};
