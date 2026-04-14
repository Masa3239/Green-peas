#pragma once

#include<vector>
#include<memory>
#include "ItemBase.h"

class ItemManager
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ItemManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ItemManager() = default;

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

private:

	std::vector<std::unique_ptr<ItemBase>> m_items;

	int m_hpHealItemGraphHandle;

};

