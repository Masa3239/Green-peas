#include "PauseMenu.h"
#include "../System/InputManager.h"
#include "../System/PauseManager.h"
#include "../Scene/SceneBase.h"
#include "../Scene/SceneTitle.h"

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
	if (InputManager::GetInstance().IsPressed(Input::Action::Pause))
	{
		PauseManager::GetInstance().TogglePause();
		PauseManager::GetInstance().SetAlpha(kPauseScreenAlpha);

		m_choice = Choice::Back;
	}

	return OnPause();
}

void PauseMenu::Draw()
{
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
