#pragma once

#include "../Object/GameObject.h"
#include <memory>

class Player;
class EnemyManager;
class Tween;

class BossKey : public GameObject
{
public:

	BossKey(ObjectManager* objManager);
	~BossKey();

	enum class Action
	{
		Appear,
		Move,
		Follow,
		Use
	};

	void Init() override;

	void End() override;

	void Update() override;

	void Draw() override;

	/// <summary>
	/// 鍵を使用する
	/// </summary>
	void UseKey();

	void SetPlayer(Player* player) { m_pPlayer = player; }
	void SetEnemyManager(EnemyManager* enemyMgr) { m_pEnemyMgr = enemyMgr; }

private:

	Action m_action;

	Player* m_pPlayer;

	EnemyManager* m_pEnemyMgr;

	std::unique_ptr<Tween> m_pTween;

	Vector3 m_color;

	float m_moveRadian;

	float m_moveDistance;

	float m_moveSpeed;

	float m_animationTimer;

	int m_graphsKey[24];

	int m_currentGraph;

	float m_graphAnimTimer;

	float m_graphAnimDuration;
};
