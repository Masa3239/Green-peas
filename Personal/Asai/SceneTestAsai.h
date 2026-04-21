#pragma once

#include "../Scene/SceneBase.h"

class SceneTestAsai : public SceneBase
{
public:

	SceneTestAsai();
	~SceneTestAsai();

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

	void PreDraw()override;
	void PostDraw()override;


};
