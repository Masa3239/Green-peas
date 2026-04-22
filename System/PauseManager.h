#pragma once

class PauseManager
{
public:

	/// <summary>
	/// インスタンスの生成、取得を行う
	/// </summary>
	static PauseManager& GetInstance();

	~PauseManager() = default;

	void Update();

private:

	PauseManager() = default;
	// コピーコンストラクタ禁止
	PauseManager(const PauseManager&) = delete;
	// コピー代入禁止
	PauseManager& operator=(const PauseManager&) = delete;
	// ムーブ禁止
	PauseManager(PauseManager&&) = delete;
	// ムーブ代入禁止
	PauseManager& operator=(PauseManager&&) = delete;

	void OnPause();

	/// <summary>
	/// ポーズ前の画面のグラフィックハンドル
	/// </summary>
	int mScreenGraph;

	/// <summary>
	/// ポーズしているかどうか
	/// </summary>
	bool mIsPaused;
};
