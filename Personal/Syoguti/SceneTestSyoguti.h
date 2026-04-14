#pragma once

#include "../Scene/SceneBase.h"
#include <memory>

class ItemManager;

class SceneTestSyoguti : public SceneBase
{
public:

	SceneTestSyoguti();
	~SceneTestSyoguti();

	/// <summary>
	/// ‰Šú‰»ˆ—
	/// </summary>
	void Init() override;

	/// <summary>
	/// Œãˆ—
	/// </summary>
	void End() override;

	/// <summary>
	/// XVˆ—
	/// </summary>
	/// <returns></returns>
	SceneBase* Update() override;

	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw() override;

private:

	std::unique_ptr<ItemManager>m_pItemMgr;

};
