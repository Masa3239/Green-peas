#include "SceneTitle.h"
#include <DxLib.h>
#include "../System/Input/Keyboard.h"
#include "../Personal/Osawa/Scene/SceneSelection.h"
#include "../System/InputManager.h"
#include "../Utility/Color.h"
#include "../Scene/CharacterSelectScene.h"

SceneTitle::SceneTitle() :
	m_choice(Choice::Start)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
}

void SceneTitle::End()
{
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
	printfDx("TITLE SCENE");

	DrawFormatString(350, 400, m_choice == Choice::Start ? Color::kRed : Color::kGray, "GAME START");
	DrawFormatString(380, 450, m_choice == Choice::Quit ? Color::kRed : Color::kGray, "QUIT");
}
