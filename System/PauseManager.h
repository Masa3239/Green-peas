#pragma once

#include <vector>

class ObjectManager;
class GameObject;

class PauseManager
{
public:

	/// <summary>
	/// インスタンスの生成、取得を行う
	/// </summary>
	static PauseManager& GetInstance();

	~PauseManager() = default;

	void End();

	void Update();

	/// <summary>
	/// ポーズ状態を切り替える
	/// </summary>
	void TogglePause() { m_isToggled = true; };

	/// <summary>
	/// ポーズ中かどうか取得
	/// </summary>
	/// <returns></returns>
	bool IsPause() const { return m_isPause; }

	void SetObjectManager(ObjectManager* objManager) { m_objManager = objManager; }

	void SetAlpha(const int alpha) { m_alpha = alpha; }

private:

	PauseManager() : m_screenGraph(-1), m_isPause(false), m_objManager(nullptr) {};
	// コピーコンストラクタ禁止
	PauseManager(const PauseManager&) = delete;
	// コピー代入禁止
	PauseManager& operator=(const PauseManager&) = delete;
	// ムーブ禁止
	PauseManager(PauseManager&&) = delete;
	// ムーブ代入禁止
	PauseManager& operator=(PauseManager&&) = delete;

	/// <summary>
	/// ポーズ前の画面のグラフィックハンドル
	/// </summary>
	int m_screenGraph;

	/// <summary>
	/// ポーズしているかどうか
	/// </summary>
	bool m_isPause;

	/// <summary>
	/// ポーズを切り替えたかどうか
	/// </summary>
	bool m_isToggled;

	ObjectManager* m_objManager;

	/// <summary>
	/// ポーズ前にアクティブだったゲームオブジェクトを格納する配列
	/// </summary>
	std::vector<GameObject*> m_activeGameObjects;

	/// <summary>
	/// ポーズ画面の透明度
	/// </summary>
	int m_alpha = 255;
};
