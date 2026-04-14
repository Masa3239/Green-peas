#pragma once

#include <memory>
#include "../Scene/SceneBase.h"

class Player;
class Camera;
class EnemyManager;

class SceneTestOsawa : public SceneBase
{
public:

	SceneTestOsawa();
	~SceneTestOsawa();

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

	std::unique_ptr<Player> m_player;

	std::unique_ptr<Camera> m_camera;

	std::unique_ptr<EnemyManager> m_enemyMgr;
};
