#include "SceneTempResult.h"
#include <DxLib.h>
#include "../System/InputPad.h"
#include "../Scene/SceneInGame.h"

SceneTempResult::SceneTempResult(std::string string) :
	m_string(string)
{
}

SceneTempResult::~SceneTempResult()
{
}

void SceneTempResult::Init()
{
}

void SceneTempResult::End()
{
}

SceneBase* SceneTempResult::Update()
{
	if (Pad::IsPressed(Pad::Button::B))
	{
		return new SceneInGame();
	}

	return this;
}

void SceneTempResult::Draw()
{
	DrawString(20, 20, m_string.c_str(), 0xffffff);

	DrawString(20, 40, "RETRY -> B BUTTON", 0xffffff);
}
