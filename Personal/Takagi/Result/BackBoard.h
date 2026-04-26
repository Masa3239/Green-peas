#pragma once
#include"../../../Utility/Transform.h"
#include"../../../Utility/Vector3.h"
class BackBoard
{
public:
	enum {
		Left,
		Right,
		Max
	};
	BackBoard();
	~BackBoard();
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();
	/// <summary>
	/// 終了処理
	/// </summary>
	void End();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 演出が終わったかどうかを調べる関数
	/// </summary>
	/// <returns></returns>
	bool IsEnd();
private:
	/// <summary>
	/// リザルト背景のグラフィックハンドル
	/// </summary>
	int m_backBoardHandle;

	/// <summary>
	/// 左側の座標
	/// </summary>
	Vector3 m_sidePos[Max];
	float m_fallSpeed[Max];
	/// <summary>
	/// 背景を描画するトランスフォーム
	/// </summary>
	Transform m_between;
};

