#pragma once

#include "../Scene/SceneBase.h"
#include "../Chara/Collision.h"

class SceneTestOBB : public SceneBase
{
public:

	SceneTestOBB();
	~SceneTestOBB();

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

	void PreDraw() override;

	void PostDraw() override;

private:

	Collision::Circle m_circle;

	Collision::OBB m_obb;

	Collision::OBB m_obb2;
};
