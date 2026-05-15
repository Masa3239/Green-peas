#pragma once
#include"../../../Utility/Transform.h"
#include"../../../Utility/Vector3.h"
/// <summary>
/// リザルトの表示時の背景の処理をするクラス
/// 2点の座標を使って座標・角度を求めて描画する
/// </summary>
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
	bool IsFinish();
	/// <summary>
	/// 演出のスキップ
	/// </summary>
	bool CheckSkip();
private:
	/// <summary>
	/// リザルト背景のグラフィックハンドル
	/// </summary>
	int m_backBoardHandle;

	/// <summary>
	/// 左右の座標
	/// </summary>
	Vector3 m_sidePos[Max];
	/// <summary>
	/// 左右の落下速度
	/// </summary>
	float m_fallSpeed[Max];
	/// <summary>
	/// 背景を描画するトランスフォーム
	/// </summary>
	Transform m_between;
	/// <summary>
	/// 落下開始の時間
	/// </summary>
	float m_fallStart[Max];
};

