#include "SceneTitle.h"
#include <DxLib.h>
#include "../System/Input/Keyboard.h"
#include "../Personal/Osawa/Scene/SceneSelection.h"
#include "../Personal/Osawa/TitleBackground.h"
#include "../System/InputManager.h"
#include "../Utility/Color.h"
#include "../Scene/CharacterSelectScene.h"

namespace
{
	const char* const kPath = "Resource\\Logo.png";
}

SceneTitle::SceneTitle() :
	m_logoGraph(-1),
	m_choice(Choice::Start),
	m_background(nullptr)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	m_logoGraph = LoadGraph(kPath);

	m_background = std::make_unique<TitleBackground>(GetObjectManager());
	m_background->Init();
}

void SceneTitle::End()
{
	m_background->End();

	DeleteGraph(m_logoGraph);
}

SceneBase* SceneTitle::Update()
{
	if (InputManager::GetInstance().IsPressed(Input::Action::Up))
	{
		m_choice--;
	}
	if (InputManager::GetInstance().IsPressed(Input::Action::Down))
	{
		m_choice++;
	}

	m_choice = (Choice::Length + m_choice) % Choice::Length;

	if (InputManager::GetInstance().IsPressed(Input::Action::Confirm))
	{
		switch (m_choice)
		{
		case Choice::Start:
			return new CharacterSelectScene();

		case Choice::Quit:
			return nullptr;
		}
	}

	return this;
}

void SceneTitle::Draw()
{
}

void SceneTitle::PostDraw()
{
	DrawRotaGraph(400, 200, 1, 0, m_logoGraph, 1);

	DrawFormatString(350, 500, m_choice == Choice::Start ? Color::kRed : Color::kGray, "GAME START");
	DrawFormatString(380, 550, m_choice == Choice::Quit ? Color::kRed : Color::kGray, "QUIT");
}
