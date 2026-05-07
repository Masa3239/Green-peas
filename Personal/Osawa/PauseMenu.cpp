#include "PauseMenu.h"
#include <DxLib.h>
#include "../System/InputManager.h"
#include "../System/PauseManager.h"
#include "../Scene/SceneBase.h"
#include "../Scene/SceneTitle.h"
#include "../Utility/Color.h"
#include "../Personal/Osawa/SettingsMenu.h"
#include "../Scene/Fader.h"

namespace
{
	// ポーズ画面のアルファ値
	constexpr int kPauseScreenAlpha = 127;
}

PauseMenu::PauseMenu():
	m_menu(Menu::Pause),
	m_choice(Choice::Back),
	m_settingsMenu(nullptr),
	m_fader(nullptr)
{
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Init()
{
	m_settingsMenu = std::make_unique<SettingsMenu>();
}

void PauseMenu::End()
{
}

void PauseMenu::Update()
{
	switch (m_menu)
	{
	case Menu::Pause:

		if (InputManager::GetInstance().IsPressed(Input::Action::Pause))
		{
			PauseManager::GetInstance().TogglePause();
			PauseManager::GetInstance().SetAlpha(kPauseScreenAlpha);

			m_choice = Choice::Back;
		}

		OnPause();

		break;

	case Menu::Settings:

		if (!m_settingsMenu->Update())
		{
			m_menu = Menu::Pause;
			m_settingsMenu->End();
		}

		break;
	}
}

void PauseMenu::Draw()
{
	if (PauseManager::GetInstance().IsPause())
	{
		DrawString(150, 300, "Resume", m_choice == Choice::Back ? Color::kRed : Color::kGray);
		DrawString(150, 330, "Settings", m_choice == Choice::Setting ? Color::kRed : Color::kGray);
		DrawString(150, 360, "Back to Title", m_choice == Choice::Title ? Color::kRed : Color::kGray);

		if (m_menu == Menu::Settings)
		{
			m_settingsMenu->Draw();
		}
	}
}

void PauseMenu::OnPause()
{
	if (!PauseManager::GetInstance().IsPause()) return;
	if (m_fader->IsFadingOut()) return;

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
		case Choice::Back:
			PauseManager::GetInstance().TogglePause();
			break;

		case Choice::Setting:
			m_menu = Menu::Settings;
			m_settingsMenu->Init();
			break;

		case Choice::Title:
			m_fader->StartFadeOut<SceneTitle>();
			//PauseManager::GetInstance().TogglePause();
			//return new SceneTitle();
			break;
		}
	}
}
