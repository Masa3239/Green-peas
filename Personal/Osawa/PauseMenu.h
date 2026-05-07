#pragma once

#include <memory>

class SceneBase;
class Fader;
class SettingsMenu;
class Tween;
class BuffManager;

class PauseMenu
{
public:

	PauseMenu();
	~PauseMenu();

	enum class Menu
	{
		Pause,
		Settings,
		Length
	};

	enum Choice
	{
		Back,
		Setting,
		Title,
		Length
	};

	void Init();

	void End();

	void Update();

	void Draw();

	void SetBuffManager(BuffManager* buffMgr) { m_buffMgr = buffMgr; }

	void SetFader(Fader* fader) { m_fader = fader; }

private:

	void Toggle();

	void OnPause();

	Menu m_menu;

	int m_choice;

	std::unique_ptr<SettingsMenu> m_settingsMenu;

	std::unique_ptr<Tween> m_tween;

	BuffManager* m_buffMgr;

	Fader* m_fader;

	float m_borderHeight;
};
