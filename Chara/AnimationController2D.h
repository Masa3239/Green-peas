#pragma once

#include <vector>
#include "Animation2D.h"

class AnimationController2D
{
public:

	AnimationController2D();
	~AnimationController2D() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// アニメーションを再生する
	/// </summary>
	void PlayAnimation(const Animation::Animation2DData& data);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// グラフィックハンドルを登録する
	/// </summary>
	/// <param name="index">登録先のアニメーションの番号</param>
	void RegisterGraphHandle(const int index, const char* const filePath, const int allNum, const int xNum, const int yNum, const int xSize, const int ySize);

	/// <summary>
	/// 現在再生中のグラフィックハンドルを取得する
	/// </summary>
	int GetCurrentGraph() const { return m_graphs[m_currentAnimation][m_currentFrame]; }

	/// <summary>
	/// アニメーションが再生しているかどうかを取得
	/// </summary>
	/// <returns>trueなら再生中</returns>
	bool IsPlaying() const { return m_isPlaying; }

	/// <summary>
	/// 割り込み不可能な再生かどうかを取得
	/// </summary>
	/// <returns>trueなら割り込みできない</returns>
	bool IsForcePlay() const { return m_isForcePlay; }

	/// <summary>
	/// 再生中のアニメーションの時間を取得
	/// </summary>
	/// <returns>再生中のアニメーションの再生時間</returns>
	float GetPlayTime() const { return m_time; }

private:

	/// <summary>
	/// アニメーションを再生させるグラフィックハンドル
	/// </summary>
	std::vector<std::vector<int>> m_graphs;

	/// <summary>
	/// 現在再生中のアニメーション
	/// </summary>
	int m_currentAnimation;

	/// <summary>
	/// 現在のアニメーションフレーム
	/// </summary>
	int m_currentFrame;

	/// <summary>
	/// 再生中のアニメーションの再生時間
	/// </summary>
	float m_time;

	/// <summary>
	/// アニメーションフレームの切り替え間隔
	/// </summary>
	float m_duration;

	/// <summary>
	/// 再生中のアニメーションがループするか
	/// </summary>
	bool m_isLoop;

	/// <summary>
	/// アニメーションが再生中かどうか
	/// </summary>
	bool m_isPlaying;

	/// <summary>
	/// 割り込み不可かどうか
	/// </summary>
	bool m_isForcePlay;
};
