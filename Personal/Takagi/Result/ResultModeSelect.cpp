#include "ResultModeSelect.h"
#include<DxLib.h>
#include<string>
#include"../../../Utility/Vector3.h"
#include"../../../Utility/Game.h"
#include"../../../Utility/Time.h"
#include"../../../Utility/MyMath.h"
#include"../../../System/InputManager.h"
#include"../../../Scene/CharacterSelectScene.h"
#include"../../../Scene/SceneTitle.h"
#include"../../../Personal/Osawa/Scene/SceneSelection.h"
namespace {
	const char* const kResultPath = "Resource\\Result\\";
	const char* const kGraphPath[ResultModeSelect::Max] = {
		"Title",
		"Retry",
	};
	const char* const kSurround = "Surround";
	const char* const kPng = ".png";
}
namespace {
	// スクリーンの中心座標
	constexpr Vector3 kScreenHalf = { Game::kScreenWidth * 0.5f,Game::kScreenHeight * 0.5f ,0 };
	// 選択肢のX距離
	constexpr float kDIstanceX = 150;
	// 座標の開始位置
	constexpr Vector3 kInitPos[ResultModeSelect::Max] = {
		{Game::kScreenWidth + 200,kScreenHalf.y + 200,0},
		{kInitPos[0].x + (kDIstanceX * 2),kScreenHalf.y + 200,0},
	};
	// 座標の終了位置
	constexpr Vector3 kEndPos[ResultModeSelect::Max] = {
	{kScreenHalf.x - kDIstanceX,kScreenHalf.y + 200,0},
	{kScreenHalf.x + kDIstanceX,kScreenHalf.y + 200,0},
	};
}
ResultModeSelect::ResultModeSelect():
	m_modeHandle(),
	m_surroundHandle(),
	m_select(0),
	m_drawPos(),
	m_stop(false)
{
	std::string path;
	for (int i = 0; i < Max; i++) {
		path = kResultPath;
		path += kGraphPath[i];
		m_modeHandle[i] = LoadGraph((path + kPng).c_str());
		path += kSurround;
		m_surroundHandle[i] = LoadGraph((path + kPng).c_str());
		m_drawPos[i] = kInitPos[i];
	}
	
}

ResultModeSelect::~ResultModeSelect()
{
}

void ResultModeSelect::Init()
{
}

void ResultModeSelect::End()
{
}

void ResultModeSelect::Update()
{
	bool skip = InputManager::GetInstance().IsPressed(Input::Action::Confirm);
	m_stop = IsStop();
	if (skip&&!m_stop) {
		for (int i = 0; i < Max; i++) {
			m_drawPos[i] = kEndPos[i];
		}
		return;
	}

	float time = Time::GetInstance().GetUnscaledDeltaTime();
	for (int i = 0; i < Max; i++) {
		Vector3 differ = kEndPos[i] - m_drawPos[i];
		differ *= time*3;
		m_drawPos[i] += differ;
		if (differ.GetSqLength() > 0.001f)continue;
		m_drawPos[i] = kEndPos[i];
		//m_stop = true;
	}
	if (!IsStop())return;
	if (InputManager::GetInstance().IsPressed(Input::Action::Left)) {
		m_select--;
	}
	if (InputManager::GetInstance().IsPressed(Input::Action::Right)) {
		m_select++;
	}
	m_select = MyMath::Clamp(m_select, 0, Max - 1);
}

void ResultModeSelect::Draw()
{
	if (IsStop()) {
		// 補間が終了していたら
		// 選択しているものを表示する
		DrawRotaGraph(m_drawPos[m_select].x, m_drawPos[m_select].y, 0.2f, 0, m_surroundHandle[m_select], TRUE);
	}
	// 選択肢の描画
	for (int i = 0; i < Max; i++) {
		DrawRotaGraph(m_drawPos[i].x, m_drawPos[i].y, 0.2f, 0, m_modeHandle[i], TRUE);
	}
}

bool ResultModeSelect::IsStop()
{
	// それぞれの補間が終わっていたらtrue
	for (int i = 0; i < Max; i++) {
		if (m_drawPos[i] != kEndPos[i])return false;
	}
	return true;
}

SceneBase* ResultModeSelect::CheckSelect()
{
	// 補間が終了していなければnullptrを返す
	if (!m_stop)return nullptr;
	// 決定ボタンを押していないときnullptrを返す
	if (!InputManager::GetInstance().IsPressed(Input::Action::Confirm)) {
		return nullptr;
	}
	// 選択しているシーンを返す
	switch (m_select)
	{
	case Title:
		return new SceneTitle();
		//return new SceneSelection();
		break;
	case Retry:
		return new CharacterSelectScene();
		break;
	default:
		break;
	}
	return nullptr;
}
