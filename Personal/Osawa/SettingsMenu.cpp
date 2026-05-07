#include "SettingsMenu.h"
#include <DxLib.h>
#include "../System/InputManager.h"
#include "../System/JsonManager.h"
#include "../Utility/Color.h"

namespace
{
	constexpr float kMaxVolume = 1.0f;
	constexpr float kMinVolume = 0.0f;

	const char* const kSettingsJsonPath = "Config\\Settings.json";
}

SettingsMenu::SettingsMenu() :
	m_choice(BGMVol),
	m_bgmVolume(1.0f),
	m_seVolume(1.0f)
{
}

void SettingsMenu::Init()
{
	// 設定データを取得する
	auto& json = JsonManager::GetInstance().Load(kSettingsJsonPath);

	m_bgmVolume = json["bgmVolume"];
	m_seVolume = json["seVolume"];
}

void SettingsMenu::End()
{
	// 設定データを保存する
	auto& json = JsonManager::GetInstance().Load(kSettingsJsonPath);

	json["bgmVolume"] = m_bgmVolume;
	json["seVolume"] = m_seVolume;

	JsonManager::GetInstance().Save(kSettingsJsonPath);
}

bool SettingsMenu::Update()
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

	switch (m_choice)
	{
	case Choice::BGMVol:
		if (InputManager::GetInstance().IsPressed(Input::Action::Right)) m_bgmVolume += 0.1f;
		if (InputManager::GetInstance().IsPressed(Input::Action::Left)) m_bgmVolume -= 0.1f;
		m_bgmVolume = std::clamp(m_bgmVolume, kMinVolume, kMaxVolume);
		break;

	case Choice::SEVol:
		if (InputManager::GetInstance().IsPressed(Input::Action::Right)) m_seVolume += 0.1f;
		if (InputManager::GetInstance().IsPressed(Input::Action::Left)) m_seVolume -= 0.1f;
		m_seVolume = std::clamp(m_seVolume, kMinVolume, kMaxVolume);
		break;
	}

	if (InputManager::GetInstance().IsPressed(Input::Action::Cancel))
	{
		return false;
	}

	return true;
}

void SettingsMenu::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
	DrawBox(250, 200, 550, 400, Color::kBlack, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(370, 220, "SETTINGS", Color::kWhite);

	int vol;

	vol = static_cast<int>(std::round(m_bgmVolume * 100));
	DrawString(300, 300, "BGM Volume: ", m_choice == Choice::BGMVol ? Color::kRed : Color::kGray);
	DrawString(450, 300, (std::to_string(vol) + "%").c_str(), m_choice == Choice::BGMVol ? Color::kRed : Color::kGray);

	vol = static_cast<int>(std::round(m_seVolume * 100));
	DrawString(300, 350, "SE Volume: ", m_choice == Choice::SEVol ? Color::kRed : Color::kGray);
	DrawString(450, 350, (std::to_string(vol) + "%").c_str(), m_choice == Choice::SEVol ? Color::kRed : Color::kGray);
}
