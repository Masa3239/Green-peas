#include "PauseMenu.h"
#include <DxLib.h>
#include <string>
#include <utility>
#include "../System/InputManager.h"
#include "../System/PauseManager.h"
#include "../Scene/SceneBase.h"
#include "../Scene/SceneTitle.h"
#include "../Utility/Color.h"
#include "../Personal/Osawa/SettingsMenu.h"
#include "../Personal/Osawa/Easing/Tween.h"
#include "../Personal/Takagi/BuffManager.h"
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
	m_tween(nullptr),
	m_buffMgr(nullptr),
	m_fader(nullptr),
	m_borderHeight(0.0f)
{
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Init()
{
	m_settingsMenu = std::make_unique<SettingsMenu>();
	m_tween = std::make_unique<Tween>();
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
			Toggle();
			
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

	m_tween->Update();
}

void PauseMenu::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
	DrawBox(0, 0, m_borderHeight * 2.3f, 800, Color::kBlack, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawBox(0, 0, 800, m_borderHeight, Color::kBlack, true);
	DrawBox(0, 600, 800, 600 - m_borderHeight, Color::kBlack, true);
	DrawString(360, m_borderHeight - 40, "PAUSE", Color::kWhite);

	if (PauseManager::GetInstance().IsPause())
	{
		DrawString(150, 300, "Resume", m_choice == Choice::Back ? Color::kRed : Color::kGray);
		DrawString(150, 330, "Settings", m_choice == Choice::Setting ? Color::kRed : Color::kGray);
		DrawString(150, 360, "Back to Title", m_choice == Choice::Title ? Color::kRed : Color::kGray);

		std::vector<std::pair<int, int>> buffs;
		for (int i = 0; i < kBuffMax; i++)
		{
			int level = m_buffMgr->GetBuffLevel(static_cast<Buff::Type>(i));
			if (level <= 0) continue;

			int graph = m_buffMgr->GetBuffIcon(static_cast<Buff::Type>(i));
			auto data = std::make_pair(level, graph);
			buffs.emplace_back(data);
		}
		for (int i = 0; i < buffs.size(); i++)
		{
			DrawRotaGraph(40 + 60 * i, 560, 0.1f, 0, buffs[i].second, false);
			DrawBox(38 + 60 * i, 578, 75 + 60 * i, 620, Color::kBlack, true);
			DrawString(40 + 60 * i, 580, ("LV" + std::to_string(buffs[i].first)).c_str(), Color::kWhite);
		}

		if (m_menu == Menu::Settings)
		{
			m_settingsMenu->Draw();
		}
	}
}

void PauseMenu::Toggle()
{
	PauseManager::GetInstance().TogglePause();
	PauseManager::GetInstance().SetAlpha(kPauseScreenAlpha);

	m_choice = Choice::Back;

	if (!PauseManager::GetInstance().IsPause())
	{
		m_tween->StartAnim(&m_borderHeight, {
			Animation::Keyframe{m_borderHeight, 0.0f, Animation::Ease::BackOut},
			Animation::Keyframe{80.0f, 0.5f},
			});
	}
	else
	{
		m_tween->StartAnim(&m_borderHeight, {
			Animation::Keyframe{m_borderHeight, 0.0f, Animation::Ease::QuadIn},
			Animation::Keyframe{0.0f, 0.25f},
			});
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
			Toggle();
			break;

		case Choice::Setting:
			m_menu = Menu::Settings;
			m_settingsMenu->Init();
			break;

		case Choice::Title:
			m_fader->StartFadeOut<SceneTitle>();
			break;
		}
	}
}
