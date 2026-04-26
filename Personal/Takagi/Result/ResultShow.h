#pragma once
#include<memory>
#include"../../../Scene/CarryOver.h"
class BackBoard;
class ResultHead;
class ScoreShow;
class ResultModeSelect;
class SceneBase;

class ResultShow
{
public:
	enum {
		Back,
		Head,
		Score,
		Mode,
		Max
	};
	ResultShow();
	~ResultShow();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(const CarryOver& carryOver);
	/// <summary>
	/// 終了処理
	/// </summary>
	void End();
	/// <summary>
	/// 更新処理
	/// </summary>
	SceneBase* Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// リザルト中かどうか
	/// </summary>
	/// <returns></returns>
	bool IsResult() { return m_isResult; }
private:

	/// <summary>
	/// 数値の表示をするフォントハンドル
	/// </summary>
	int m_fontHandle;
	/// <summary>
	/// 背景のポインタ
	/// </summary>
	std::unique_ptr<BackBoard> m_backBoard;
	/// <summary>
	/// クリアしたかどうかの表示をするポインタ
	/// </summary>
	std::unique_ptr<ResultHead> m_resultHead;
	/// <summary>
	/// スコア表示をするポインタ
	/// </summary>
	std::unique_ptr<ScoreShow> m_scoreShow;
	/// <summary>
	/// モード選択のポインタ
	/// </summary>
	std::unique_ptr<ResultModeSelect> m_modeSelect;
	/// <summary>
	/// リザルト演出の状態
	/// </summary>
	int m_phase;
	float m_interval;
	bool m_isResult;

};

