#pragma once

class Map;
class Camera;
class Player;
class EnemyManager;
class ItemManager;

struct Vector3;

class Minimap
{

public:

	Minimap();
	~Minimap();

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
	/// デバックの描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	void GenerateMinimap();

	void SetMap(Map* pMap) { m_pMap = pMap; }

	void SetCamera(Camera* pCamera) { m_pCamera = pCamera; }

	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	void SetEnemyManager(EnemyManager* pEnemyMgr) { m_pEnemyMgr = pEnemyMgr; }

	void SetItemManager(ItemManager* pItemMgr) { m_pItemMgr = pItemMgr; }

private:

	Vector3 ToMinimapPos(const Vector3 pos);

private:

	int m_playerUIGrahpHandle;

	Map* m_pMap;

	Player* m_pPlayer;

	Camera* m_pCamera;

	EnemyManager* m_pEnemyMgr;

	ItemManager* m_pItemMgr;

};
