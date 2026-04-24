#pragma once

#include<vector>
#include<memory>
#include "TreasureChest.h"
#include "../../System/ObjectManager.h"

class TreasureChest;

namespace {

	// 画像のサイズ
	constexpr float kGraphScale = 1.0f;
}

class ChestManager
{

public:

	ChestManager();

	~ChestManager();

	/// <summary>
	///  初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 終了
	/// </summary>
	void End();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void Create(Vector3 position);

private:

	std::vector<std::unique_ptr<TreasureChest>> m_chests;

	int m_graphHandle[kTreasureChestMotionNum];

	int m_motionCounter;

	int m_motionFrame;

	ObjectManager* m_pObjectMgr;

};

