#pragma once

#include <memory>
#include "SceneBase.h"

class SettingsMenu;
class TitleBackground;

class SceneTitle : public SceneBase
{
public:

	SceneTitle();
	~SceneTitle();

	enum class Menu
	{
		Title,
		Settings,
		Length
	};

	enum Choice
	{
		Start,
		Settings,
		Quit,
		Length
	};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 後処理
	/// </summary>
	void End() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <returns></returns>
	SceneBase* Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

	void PostDraw() override;

private:

	int m_logoGraph;

	Menu m_menu;

	int m_choice;

	std::unique_ptr<SettingsMenu> m_settingsMenu;

	std::unique_ptr<TitleBackground> m_background;
};
