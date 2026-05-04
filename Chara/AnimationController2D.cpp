#include "AnimationController2D.h"
#include "../Utility/Time.h"

AnimationController2D::AnimationController2D() :
	m_currentAnimation(0),
	m_currentFrame(0),
	m_time(0.0f),
	m_duration(0.0f),
	m_isLoop(false),
	m_isPlaying(false),
	m_isForcePlay(false)
{
}

void AnimationController2D::Init()
{
}

void AnimationController2D::End()
{
	for (auto& graphs : m_graphs)
	{
		for (auto& graph : graphs)
		{
			DeleteGraph(graph);
		}
	}
}

void AnimationController2D::PlayAnimation(const Animation::Animation2DData& data)
{
	// 割り込み再生できないアニメーションが再生されていたら即時return
	if (m_isForcePlay && m_isPlaying) return;

	// 同じアニメーションが再生中なら即時リターン
	if (m_currentAnimation == data.index && m_isPlaying) return;

	m_currentAnimation = data.index;
	m_duration = data.duration;
	m_time = 0.0f;
	m_isLoop = data.isLoop;
	m_isForcePlay = data.isForcePlay;
	m_isPlaying = true;
}

void AnimationController2D::Update()
{
	if (!m_isPlaying) return;

	m_time += Time::GetInstance().GetDeltaTime() * 60.0f;

	// アニメーションフレームのカウントアップ
	if (m_time >= m_duration)
	{
		m_currentFrame++;

		m_time = 0.0f;
	}

	// ループ処理
	if (m_currentFrame >= m_graphs[m_currentAnimation].size() - 1)
	{
		if (m_isLoop)
		{
			// ループアニメーションなら頭に戻る
			m_currentFrame = 0;
		}
		else
		{
			// ワンショットアニメーションなら停止
			m_isPlaying = false;
			m_isForcePlay = false;
		}
	}
}

void AnimationController2D::RegisterGraphHandle(const int index, const char* const filePath, const int allNum, const int xNum, const int yNum, const int xSize, const int ySize)
{
	// 配列の範囲外なら配列を追加する
	while (index >= m_graphs.size())
	{
		m_graphs.emplace_back(std::vector<int>());
	}

	m_graphs[index].resize(allNum);

	LoadDivGraph(filePath, allNum, xNum, yNum, xSize, ySize, m_graphs[index].data());
}
