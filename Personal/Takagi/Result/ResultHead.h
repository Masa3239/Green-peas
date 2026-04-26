#pragma once
#include"../../../Utility/Transform.h"
class ResultHead
{
public:
	ResultHead() = default;
	~ResultHead() = default;
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() = 0;
	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void End() = 0;
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// 演出が終了したかどうかを調べる関数
	/// </summary>
	/// <returns></returns>
	bool IsFinish() { return m_isFinish; }
protected:
	/// <summary>
	/// グラフィックハンドル
	/// </summary>
	int m_graphHandle;
	/// <summary>
	/// 描画する座標・角度・拡縮
	/// </summary>
	Transform m_transform;
	/// <summary>
	/// 演出が終了したか
	/// </summary>
	bool m_isFinish;
};

