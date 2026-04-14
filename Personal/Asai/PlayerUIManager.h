#pragma once
#include"../Asai/PlayerUIBase.h"
#include<vector>
#include<memory>

class Player;

class PlayerUIManager
{

public:

	PlayerUIManager();
	~PlayerUIManager() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// スクリーン座標に描画
	/// </summary>
	void ScreenDraw();

	/// <summary>
	/// ワールド座標に描画
	/// </summary>
	void WorldDraw();

	/// <summary>
	/// デバックの描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	void SetPlayer(Player* pPlayer);

private:

	/// <summary>
	/// 表示するプレイヤーのUIの配列
	/// </summary>
	std::vector<std::unique_ptr<PlayerUIBase>>m_pUIs;

};
