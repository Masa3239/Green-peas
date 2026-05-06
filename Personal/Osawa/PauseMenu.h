#pragma once

#include <memory>

class SceneBase;
class SettingsMenu;

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

	SceneBase* Update();

	void Draw();

private:

	SceneBase* OnPause();

	Menu m_menu;

	int m_choice;

	std::unique_ptr<SettingsMenu> m_settingsMenu;
};
