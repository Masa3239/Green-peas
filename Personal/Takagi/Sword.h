#pragma once
#include"Weapon.h"
#include"../../Object/GameObject.h"
#include"../../Chara/Collision.h"

class Sword:public Weapon
{
public:
	Sword(ObjectManager* pbjManager);
	~Sword();

	void Init()override;
	void End()override;
	void Update()override;
	void Draw()override;
	void SetPos(const Vector3& pos) { GetTransform().position = pos; }
	void Attack()override;
	Collision::Circle GetCollision()override { return m_circle; }
	bool CheckAttack()override;

private:
	bool attack;
	float m_desireRadian;
	Collision::Circle m_circle;

};

