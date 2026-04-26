#pragma once
#include"../../../Utility/Vector3.h"

class SceneBase;

class ResultModeSelect
{
public:
	enum {
		Title,
		Retry,
		Max
	};
	ResultModeSelect();
	~ResultModeSelect();
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
	/// 補間が終わったかどうかを調べる関数
	/// </summary>
	/// <returns>終了地点と等しいときtrue</returns>
	bool IsStop();
	/// <summary>
	/// 選択したシーンを返す関数
	/// </summary>
	/// <returns></returns>
	SceneBase* CheckSelect();
private:
	/// <summary>
	/// 画面遷移のグラフィックハンドル
	/// </summary>
	int m_modeHandle[Max];
	/// <summary>
	/// 選択中表示のグラフィックハンドル
	/// </summary>
	int m_surroundHandle[Max];
	/// <summary>
	/// 現在選択しているもの
	/// </summary>
	int m_select;
	/// <summary>
	/// 画像を表示する座標
	/// </summary>
	Vector3 m_drawPos[Max];
	bool m_stop;
};

