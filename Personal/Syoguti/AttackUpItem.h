#pragma once
#include "ItemBase.h"
#include "../../Utility/Transform.h"

class AttackUpItem : public ItemBase
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	AttackUpItem();

	/// <summary>
	/// 引数ありのコンストラクタ
	/// </summary>
	/// <param name="position"></param>
	AttackUpItem(Vector3 position);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~AttackUpItem() = default;

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
	/// アイテムの効果
	/// </summary>
	virtual void ItemAbility() override;

	/// <summary>
	/// グラフハンドルをセットするセッター関数
	/// </summary>
	/// <param name="graphHandlePath"></param>
	virtual void SetGraphHandle(int graphHandle) override { m_graphHandle = graphHandle; }

};

