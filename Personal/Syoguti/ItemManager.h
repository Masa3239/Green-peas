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

	/// <summary>
	/// 生成
	/// </summary>
	void Create();

	/// <summary>
	/// 指定したインデックスのアイテムを削除
	/// </summary>
	/// <param name="index"></param>
	void Remove(int index);

	/// <summary>
	/// 引数のサークルとアイテムが当たっているか調べる
	/// </summary>
	/// <param name="other"></param>
	void CheckHitCircle(const Collision::Circle other);

private:

	std::vector<std::unique_ptr<ItemBase>> m_items;

	int m_hpHealItemGraphHandle;

};

