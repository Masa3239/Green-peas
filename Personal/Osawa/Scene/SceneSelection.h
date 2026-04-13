#pragma once

#include "../Scene/SceneBase.h"

class SceneSelection : public SceneBase
{
public:

	SceneSelection();
	~SceneSelection();

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
};
