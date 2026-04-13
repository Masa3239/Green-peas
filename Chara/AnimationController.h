#pragma once

#include "Animation.h"

/// <summary>
/// アニメーションの再生処理を管理するクラス
/// </summary>
class AnimationController
{
public:

	AnimationController();

	~AnimationController() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="modelHandle">アニメーションを管理するモデルハンドル</param>
	void Init(int modelHandle);

	/// <summary>
	/// アニメーションの再生
	/// </summary>
	/// <param name="animIndex">アニメーションのデータ</param>
	void PlayAnimation(const Animation::AnimationData& data);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

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
	/// デバッグ情報の表示
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 再生中のアニメーションの時間を取得
	/// </summary>
	/// <returns>再生中のアニメーションの再生時間</returns>
	float GetPlayTime() const { return m_time; }

private:

	/// <summary>
	/// アニメーションを再生させるモデルハンドル
	/// </summary>
	int m_modelHandle;

	/// <summary>
	/// モデルにアタッチするアニメーション番号
	/// </summary>
	int m_attachIndex;

	/// <summary>
	/// 現在再生中のアニメーション
	/// </summary>
	int m_currentAnimation;

	/// <summary>
	/// 再生中のアニメーションの再生時間
	/// </summary>
	float m_time;

	/// <summary>
	/// 再生中のアニメーションの総尺
	/// </summary>
	float m_totalTime;

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
