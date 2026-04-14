#pragma once
#include "ItemBase.h"

class HpHealItem : public ItemBase 
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	HpHealItem();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~HpHealItem() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init(int graphHandle) override;

	/// <summary>
	/// 終了
	/// </summary>
	void End() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 生成
	/// </summary>
	void Regist() override;

};

