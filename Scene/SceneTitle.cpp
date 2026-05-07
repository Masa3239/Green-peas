#include "SceneTitle.h"
#include <DxLib.h>
#include "../Personal/Osawa/TitleBackground.h"
#include "../System/InputManager.h"
#include "../Utility/Color.h"
#include "../Scene/CharacterSelectScene.h"
#include "../Scene/Fader.h"
#include "../Personal/Osawa/SettingsMenu.h"

namespace
{
	const char* const kPath = "Resource\\Logo.png";
}

SceneTitle::SceneTitle() :
	m_logoGraph(-1),
	m_menu(Menu::Title),
	m_choice(Choice::Start),
	m_settingsMenu(nullptr),
	m_background(nullptr)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	m_logoGraph = LoadGraph(kPath);

	m_settingsMenu = std::make_unique<SettingsMenu>();

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
	if (GetFader()->IsFadingOut()) return this;

	switch (m_menu)
	{
	case SceneTitle::Menu::Title:

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
				GetFader()->StartFadeOut<CharacterSelectScene>();
				break;

			case Choice::Settings:
				m_menu = Menu::Settings;
				m_settingsMenu->Init();
				break;

			case Choice::Quit:
				return nullptr;
			}
		}

		break;

	case SceneTitle::Menu::Settings:

		if (!m_settingsMenu->Update())
		{
			m_menu = Menu::Title;
			m_settingsMenu->End();
		}

		break;
	}

	return this;
}

void SceneTitle::Draw()
{
}

void SceneTitle::PostDraw()
{
	DrawRotaGraph(400, 200, 1, 0, m_logoGraph, 1);

	DrawFormatString(350, 450, m_choice == Choice::Start ? Color::kRed : Color::kGray, "GAME START");
	DrawFormatString(360, 500, m_choice == Choice::Settings ? Color::kRed : Color::kGray, "SETTINGS");
	DrawFormatString(380, 550, m_choice == Choice::Quit ? Color::kRed : Color::kGray, "QUIT");

	if (m_menu == Menu::Settings)
	{
		m_settingsMenu->Draw();
	}
}
