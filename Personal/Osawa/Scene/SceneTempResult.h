#pragma once
#include "../Scene/SceneBase.h"
#include <string>

class SceneTempResult : public SceneBase
{
public:

	SceneTempResult(std::string string);
	~SceneTempResult();

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

private:

	std::string m_string;
};
