#include "PauseMenu.h"
#include <DxLib.h>
#include "../System/InputManager.h"
#include "../System/PauseManager.h"
#include "../Scene/SceneBase.h"
#include "../Scene/SceneTitle.h"
#include "../Utility/Color.h"

namespace
{
	// ポーズ画面のアルファ値
	constexpr int kPauseScreenAlpha = 127;
}

PauseMenu::PauseMenu():
	m_choice(Choice::Back)
{
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Init()
{
}

void PauseMenu::End()
{
}

SceneBase* PauseMenu::Update()
{
	if (InputManager::GetInstance().IsPressed(Input::Action::Pause) || InputManager::GetInstance().IsPressed(Input::Action::Cancel))
	{
		PauseManager::GetInstance().TogglePause();
		PauseManager::GetInstance().SetAlpha(kPauseScreenAlpha);

		m_choice = Choice::Back;
	}

	return OnPause();
}

void PauseMenu::Draw()
{
	if (PauseManager::GetInstance().IsPause())
	{
		DrawString(150, 300, "Resume", Color::kGray);
		DrawString(150, 300, "Resume", m_choice == Choice::Back ? Color::kRed : Color::kGray);
		DrawString(150, 330, "Settings", m_choice == Choice::Setting ? Color::kRed : Color::kGray);
		DrawString(150, 360, "Back to Title", m_choice == Choice::Title ? Color::kRed : Color::kGray);
	}
}

SceneBase* PauseMenu::OnPause()
{
	if (!PauseManager::GetInstance().IsPause()) return nullptr;

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

			break;

		case Choice::Title:
			return new SceneTitle();
			break;
		}
	}

	return nullptr;
}
