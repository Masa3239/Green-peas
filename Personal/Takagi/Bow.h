#pragma once
#include"Weapon.h"

namespace {
	constexpr int kArrownum = 100;
}

class Arrow;
class Bow:public Weapon
{
public:
	Bow(ObjectManager* bjManager);
	~Bow();

	void Init()override;
	void End()override;
	void Update()override;
	void Draw()override;
	void SetPos(const Vector3& pos) { GetTransform().position = pos; }
	void Attack()override;
	bool CheckAttack()override;
	//Collision::Circle GetCollision()override;
	void CheckCollision()override;
private:
	//bool attack;
	//float m_desireRadian;
	Arrow* m_pArrows[kArrownum];
};

