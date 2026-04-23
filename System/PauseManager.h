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

	void TogglePause();

	void SetObjectManager(ObjectManager* objManager) { m_objManager = objManager; }

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

	ObjectManager* m_objManager;

	std::vector<GameObject*> m_activeGameObjects;
};
