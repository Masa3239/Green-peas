#pragma once
#include "../Scene/SceneBase.h"
#include"../Personal/Takagi/Player.h"
#include<memory>
class RotateCharacter;
class BuffManager;

class CharacterSelectScene : public SceneBase
{
public:
	CharacterSelectScene();
	~CharacterSelectScene();

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

	void PreDraw()override;
	void PostDraw()override;
private:
	RotateCharacter* m_characters;
	int m_graphHanedle[static_cast<int>(Character::Job::Max)];

};
