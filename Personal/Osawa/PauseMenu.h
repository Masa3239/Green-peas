#pragma once

class SceneBase;

class PauseMenu
{
public:

	PauseMenu();
	~PauseMenu();

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

	int m_choice;
};
