#pragma once
#include"../../../Scene/CarryOver.h"
class ScoreShow
{
public:
	enum {
		Job,
		Damage,
		Combo,
		Max,
	};
	ScoreShow();
	ScoreShow(const CarryOver& carryOver);
	~ScoreShow();
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

private:
	/// <summary>
	/// プレイスコア
	/// </summary>
	CarryOver m_score;
	/// <summary>
	/// 描画の際に使うスコア
	/// </summary>
	CarryOver m_showScore;
	/// <summary>
	/// 描画に使うフォントハンドル
	/// </summary>
	int m_fontHandle;
	int m_phase;
	float m_interval;
};

