#pragma once
#include "ItemBase.h"
#include "../../Utility/Transform.h"

class HpHealItem : public ItemBase 
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	HpHealItem();

	/// <summary>
	/// 引数ありのコンストラクタ
	/// </summary>
	/// <param name="position"></param>
	HpHealItem(Vector3 position);

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
	virtual void SetGraphHandle(int graphHandlePath) override{ m_graphHandle = graphHandlePath; }

};

