#include "ScoreShow.h"
#include<DxLib.h>
#include"../../../Utility/Time.h"
#include"../../../Utility/Game.h"
#include"../../../Utility/Vector3.h"
#include"../Player.h"
#include<string>
#include"../../../System/InputManager.h"
namespace {
	// スクリーンの中心座標
	constexpr Vector3 kScreenHalf = { Game::kScreenWidth * 0.5f,Game::kScreenHeight * 0.5f,0 };
	// フォントサイズ
	constexpr int kFontsize = 40;
	// スコア表示の間隔
	constexpr float kInterval = 1.0f;
	// スコア表示の座標
	constexpr Vector3 kTextPos[ScoreShow::Max] = {
		{kScreenHalf.x - 300,kScreenHalf.y - 100,0},
		{kTextPos[0].x,kTextPos[0].y + 60,0},
		{kTextPos[0].x,kTextPos[1].y + 60,0},
		{kTextPos[0].x,kTextPos[2].y + 60,0},
	};
	// 数値の描画座標
	constexpr float kScorePosX = 300;
	const char* const kScoreName[ScoreShow::Max] = {
		"  Job     : ",
		"MaxDamage : ",
		"  Combo   : ",
		"  kill    : ",
	};
	const char* const kJobName[static_cast<int>(Character::Job::Max)] = {
		"Warrior",
		"Hunter",
		"Wizard",
	};
}

ScoreShow::ScoreShow():
	m_score(),
	m_showScore(),
	m_fontHandle(-1),
	m_phase(0),
	m_interval(kInterval)
{
	m_score.Reset();
	m_showScore.Reset();
	m_fontHandle = CreateFontToHandle(NULL, kFontsize, 3, DX_FONTTYPE_EDGE);
}

ScoreShow::ScoreShow(const CarryOver& carryOver) :
	m_score(carryOver),
	m_showScore(),
	m_fontHandle(-1),
	m_phase(-1),
	m_interval(kInterval)
{
	m_showScore.Reset();
	m_fontHandle = CreateFontToHandle(NULL, kFontsize, 3, DX_FONTTYPE_EDGE);
}

ScoreShow::~ScoreShow()
{
}

void ScoreShow::Init()
{
}

void ScoreShow::End()
{
}

void ScoreShow::Update()
{
	float time = Time::GetInstance().GetUnscaledDeltaTime();
	bool skip = InputManager::GetInstance().IsPressed(Input::Action::Confirm);
	if (m_interval > 0) {
		m_interval -= time;
		if (skip)m_interval = 0;
		return;
	}
	switch (m_phase)
	{
	case Job:
			m_phase = Damage;
			m_interval = kInterval;
		break;
	case Damage: {

		if (m_showScore.maxDamage == m_score.maxDamage) {
			m_interval = kInterval;
			m_phase = Combo;
			break;
		}
		float value = static_cast<int>(m_score.maxDamage * time * 0.5f);
		value = MyMath::Clamp(value, 1.0f, value);
		m_showScore.maxDamage += value;
		m_showScore.maxDamage = MyMath::Clamp(m_showScore.maxDamage, 0, m_score.maxDamage);
		if (skip)m_showScore.maxDamage = m_score.maxDamage;
		break;
	}
	case Combo: {

		if (m_showScore.maxCombo == m_score.maxCombo) {
			m_interval = kInterval;
			m_phase = Kill;
			break;
		}
		float value = static_cast<int>(m_score.maxCombo * time * 0.5f);
		value = MyMath::Clamp(value, 1.0f, value);
		m_showScore.maxCombo += value;
		m_showScore.maxCombo = MyMath::Clamp(m_showScore.maxCombo, 0, m_score.maxCombo);
		if (skip)m_showScore.maxCombo = m_score.maxCombo;

		break;
	}
	case Kill: {

		if (m_showScore.kill == m_score.kill) {
			m_interval = kInterval;
			m_phase = Max;
			break;
		}
		float value = static_cast<int>(m_score.kill * time * 0.5f);
		value = MyMath::Clamp(value, 1.0f, value);
		m_showScore.kill += value;
		m_showScore.kill = MyMath::Clamp(m_showScore.kill, 0, m_score.kill);
		if (skip)m_showScore.kill = m_score.kill;

		break;
	}
	case Max:
		break;
	default:
		m_phase = Job;
		m_interval = kInterval;
		break;
	}
}

void ScoreShow::Draw()
{
	for (int i = 0; i < Max; i++) {
		if (i > m_phase )break;
		DrawStringToHandle(kTextPos[i].x, kTextPos[i].y, kScoreName[i], 0xffffff, m_fontHandle);
		std::string score;
		switch (i)
		{
		case Job:
			score = kJobName[static_cast<int>(m_score.characterJob)];
			break;
		case Damage:
			score = std::to_string(m_showScore.maxDamage);
			break;
		case Combo:
			score = std::to_string(m_showScore.maxCombo);
			break;
		case Kill:
			score = std::to_string(m_showScore.kill);
			break;
		default:
			break;
		}
		DrawStringToHandle(kTextPos[i].x + kScorePosX, kTextPos[i].y, score.c_str(), 0xffffff, m_fontHandle);
	}
}

bool ScoreShow::IsFinish()
{
	return (m_phase == Max);
}
