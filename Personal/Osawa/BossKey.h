#pragma once

#include "../Object/GameObject.h"

class Player;

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

	void SetPlayer(Player* player) { m_pPlayer = player; }

private:

	Action m_action;

	Player* m_pPlayer;

	Vector3 m_color;

	float m_moveRadian;

	float m_moveDistance;

	float m_moveSpeed;

	float m_animationTimer;
};
