#include "ResultShow.h"
#include"BackBoard.h"
#include"ResultHead.h"
#include"Clear.h"
#include"../../../Utility/Time.h"
namespace {
	// 演出同士のインターバル
	constexpr float kInterval[ResultShow::Max] = { 0.5f,0.5f };
}
ResultShow::ResultShow():
	m_backBoard(nullptr),
	m_resultHead(nullptr),
	m_phase(Back),
	m_interval(0)
{
	m_backBoard = std::make_unique<BackBoard>();
	m_resultHead = std::make_unique<Clear>();
}

ResultShow::~ResultShow()
{
}

void ResultShow::Init()
{
	m_backBoard->Init();
	m_resultHead->Init();
}

void ResultShow::End()
{
	m_backBoard->End();
	m_resultHead->End();
}

void ResultShow::Update()
{
	if (m_interval > 0) {
		m_interval -= Time::GetInstance().GetUnscaledDeltaTime();
	}

	switch (m_phase)
	{
	case Back:
		// 背景の更新処理
		m_backBoard->Update();

		if (!m_backBoard->IsEnd())break;
		// 背景の演出が終わっていたら
		m_phase = Head;
		m_interval = kInterval[m_phase];
		break;
	case Head:
		m_resultHead->Update();
		break;
	default:
		break;
	}
}

void ResultShow::Draw()
{
	m_backBoard->Draw();
	m_resultHead->Draw();
}
