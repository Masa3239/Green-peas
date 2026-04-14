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
	void Init() override;

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
	/// グラフパスをセットするセッター関数
	/// </summary>
	/// <param name="graphHandlePath"></param>
	virtual void SetGraphHandlePath(int graphHandlePath) override{ m_graphHandle = graphHandlePath; }

};

