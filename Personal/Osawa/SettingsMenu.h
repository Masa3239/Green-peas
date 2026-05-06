#pragma once

class SettingsMenu
{
public:

	SettingsMenu();
	~SettingsMenu() = default;

	enum Choice
	{
		BGMVol,
		SEVol,
		Length
	};

	/// <summary>
	/// 設定メニューを開始する
	/// </summary>
	void Init();
	
	/// <summary>
	/// 設定メニューを終了する
	/// </summary>
	void End();

	bool Update();

	void Draw();

private:

	int m_choice;

	float m_bgmVolume;

	float m_seVolume;
};
