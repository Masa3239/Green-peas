#include "ResultShow.h"
#include"BackBoard.h"
#include"ResultHead.h"
#include "ScoreShow.h"
#include"Clear.h"
#include"Failed.h"
#include"ResultModeSelect.h"
#include"../../../Utility/Time.h"
#include"../../../Scene/SceneBase.h"
#include"../../../Scene/SceneTitle.h"
#include"../../../System/PauseManager.h"
namespace {
	// 演出同士のインターバル
	constexpr float kInterval[ResultShow::Max] = { 0.5f,0.5f };
	constexpr CarryOver kScore = {
		Character::Job::Hunter,
		Score::Result::Clear,
		500,
		1000,
	};
}
ResultShow::ResultShow() :
	m_backBoard(nullptr),
	m_resultHead(nullptr),
	m_scoreShow(nullptr),
	m_modeSelect(nullptr),
	m_phase(Back),
	m_interval(0),
	m_isResult(false)
{
	m_backBoard = std::make_unique<BackBoard>();

	m_scoreShow = std::make_unique<ScoreShow>(kScore);
	m_modeSelect = std::make_unique<ResultModeSelect>();

}

ResultShow::~ResultShow()
{
}
void ResultShow::Init(const CarryOver& carryOver)
{
	if (!PauseManager::GetInstance().IsPause()) {
		PauseManager::GetInstance().TogglePause();
		PauseManager::GetInstance().SetAlpha(127);
	}
	m_isResult = true;
	m_scoreShow = std::make_unique<ScoreShow>(carryOver);
		m_resultHead = std::make_unique<Failed>();
	if (carryOver.isClear == Score::Result::Clear) {
	m_resultHead = std::make_unique<Clear>();
	}
	m_backBoard->Init();
	m_resultHead->Init();
	m_scoreShow->Init();
	m_modeSelect->Init();
}

void ResultShow::End()
{
	m_backBoard->End();
	if(m_resultHead)
	m_resultHead->End();
	m_scoreShow->End();
	m_modeSelect->End();
}

SceneBase* ResultShow::Update()
{
	if (m_interval > 0) {
		m_interval -= Time::GetInstance().GetUnscaledDeltaTime();
		return nullptr;
	}

	switch (m_phase)
	{
	case Back:
		// 背景の更新処理
		m_backBoard->Update();

		if (!m_backBoard->IsFinish())break;
		// 背景の演出が終わっていたら
		m_phase = Head;
		m_interval = kInterval[m_phase];
		break;
	case Head:
		m_resultHead->Update();
		if (!m_resultHead->IsFinish())break;
		// 背景の演出が終わっていたら
		m_phase = Score;
		m_interval = kInterval[m_phase];
		break;
	case Score:
		m_scoreShow->Update();
		if (!m_scoreShow->IsFinish())break;
		m_phase = Mode;
		m_interval = kInterval[m_phase];
		break;
	case Mode:
	{
		m_modeSelect->Update();
		SceneBase* nextScene = m_modeSelect->CheckSelect();
		if (!nextScene)break;
		return nextScene;
		break;
	}
	default:
		break;
	}
		return nullptr;
}

void ResultShow::Draw()
{
	m_backBoard->Draw();
	m_scoreShow->Draw();
	m_resultHead->Draw();
	m_modeSelect->Draw();
}
