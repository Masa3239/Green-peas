#pragma once
#include "../Scene/SceneBase.h"
#include"../../System/InputPad.h"
#include<memory>
class Player;
class Camera;
class Map;
class SceneTestTakagi : public SceneBase
{
public:

	SceneTestTakagi();
	~SceneTestTakagi();

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


private:
	std::unique_ptr<Player> m_pPlayer;
	std::unique_ptr<Camera> m_pCamera;


	Map* m_pMap;

};
