#include "AnimationController.h"
#include <DxLib.h>

namespace
{
	// アニメーションの再生速度
	constexpr float kPlaySpeed = 0.5f;
}

AnimationController::AnimationController() :
	m_modelHandle(-1),
	m_attachIndex(-1),
	m_currentAnimation(-1),
	m_time(0.0f),
	m_totalTime(0.0f),
	m_isLoop(false),
	m_isPlaying(false),
	m_isForcePlay(false)
{
}

void AnimationController::Init(int modelHandle)
{
	m_modelHandle = modelHandle;
}

void AnimationController::PlayAnimation(const Animation::AnimationData& data)
{
	// 割り込み再生できないアニメーションが再生されていたら即時return
	if (m_isForcePlay && m_isPlaying) return;

	// 同じアニメーションが再生中なら即時リターン
	if (m_currentAnimation == data.index && m_isPlaying) return;

	// すでに再生中なら一度アニメーションを外しておく
	if (m_attachIndex != -1)
	{
		MV1DetachAnim(m_modelHandle, m_attachIndex);
	}

	// アニメーションのインデックスを更新
	m_attachIndex = MV1AttachAnim(m_modelHandle, data.index, -1, false);

	// アニメーションの総尺を取得
	m_totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_attachIndex);

	// アニメーションの設定
	m_currentAnimation = data.index;

	// 再生時間をリセット
	m_time = 0.0f;

	// ループ設定を更新
	m_isLoop = data.isLoop;

	// 再生中に設定
	m_isPlaying = true;

	// 割り込み不可の設定
	m_isForcePlay = data.isForcePlay;
}

void AnimationController::Update()
{
	// 再生していなければ即時リターン
	if (!m_isPlaying) return;

	// 再生時間を更新
	m_time += kPlaySpeed;

	// ループ処理
	if (m_time > m_totalTime)
	{
		if (m_isLoop)
		{
			// ループアニメーションなら頭に戻る
			m_time = 0.0f;
		}
		else
		{
			// ワンショットアニメーションなら停止
			m_isPlaying = false;
			m_time = m_totalTime;
			m_isForcePlay = false;
		}
	}

	// モデルに再生時間をセット
	MV1SetAttachAnimTime(m_modelHandle, m_attachIndex, m_time);
}

void AnimationController::DebugDraw()
{
	printfDx("Animation: time = %4f\n", m_time);
	printfDx("Animation: totalTime = %4f\n", m_totalTime);
	printfDx("Animation: isLoop = %4f\n", m_isLoop ? "ループ" : "ワンショット");
	printfDx("Animation: isPlaying = %4f\n", m_isPlaying ? "再生中" : "再生していない");
}
