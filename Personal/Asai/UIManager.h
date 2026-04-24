#pragma once
#include<memory>
#include"../../Utility/Vector3.h"
#include"../Asai/PopUpText.h"

class PlayerUIManager;
class PopUpTextManager;
class Combo;
class Minimap;

class Camera;
class Map;
class ItemManager;
class Player;
class EnemyManager;

class UIManager
{

public:

	UIManager();
	~UIManager();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// スクリーン座標に描画
	/// </summary>
	void ScreenDraw();

	/// <summary>
	/// ワールド座標に描画
	/// </summary>
	void WorldDraw();

	/// <summary>
	/// デバック描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	void GenerateMinimap(Camera* pCamera, Map* pMap);

	void SetPlayer(Player* pPlayer);

	void SetEnemyManager(EnemyManager* pEnemyManager);

	void SetItemManager(ItemManager* pItemManager);

	void CreatePopUpText(Vector3 pos, int amount, PopUpUI::TextType type);

private:

	/// <summary>
	/// プレイヤーのUI管理クラス
	/// </summary>
	std::unique_ptr<PlayerUIManager>m_pPlayerUIMgr;

	/// <summary>
	/// ポップアップテキスト管理クラス
	/// </summary>
	std::unique_ptr<PopUpTextManager>m_pPopUpTextMgr;

	/// <summary>
	/// コンボ表示クラス
	/// </summary>
	std::unique_ptr<Combo>m_pCombo;

	/// <summary>
	/// ミニマップクラス
	/// </summary>
	std::unique_ptr<Minimap>m_pMinimap;

	Player* m_pPlayer;

	EnemyManager* m_pEnemyManager;

};
