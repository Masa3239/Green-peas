#pragma once

#include "../Object/GameObject.h"
#include "../Chara/Collision.h"

class Player;

class ExpOrb : public GameObject
{
public:

	ExpOrb(ObjectManager* objManager, int exp);
	~ExpOrb();

	void Init() override;

	void End() override;

	void Update() override;

	void Draw() override;

	void SetPlayer(Player* player) { m_pPlayer = player; }

private:

	float m_speed;

	/// <summary>
	/// ŒoŒ±’l‚Ì—Ê
	/// </summary>
	int m_expAmount;

	Collision::Circle m_collider;

	Player* m_pPlayer;
};

