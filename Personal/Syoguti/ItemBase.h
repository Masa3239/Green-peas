#pragma once
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"

/// <summary>
/// アイテムの基本クラス
/// </summary>
class ItemBase
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ItemBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ItemBase() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 終了
	/// </summary>
	virtual void End() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// グラフパスをセットするセッター関数
	/// </summary>
	/// <param name="graphHandlePath"></param>
	virtual void SetGraphHandlePath(int graphHandlePath) { m_graphHandle = graphHandlePath; }

	/// <summary>
	/// 当たり判定の情報を取得するゲッター関数
	/// </summary>
	/// <returns></returns>
	virtual const Collision::Circle GetCollision() { return m_collision; }

protected:

	/// <summary>
	/// 画像の座標
	/// </summary>
	Transform m_transform;
	
	/// <summary>
	/// 画像ハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// 円の当たり判定
	/// </summary>
	Collision::Circle m_collision;

};

