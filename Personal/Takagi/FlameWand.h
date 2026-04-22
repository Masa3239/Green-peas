#pragma once
#include"Weapon.h"

class FireBall;

namespace {
	constexpr int kFlameNum = 100;
}


class FlameWand:public Weapon
{
public:
	FlameWand(ObjectManager* objManager);
	~FlameWand();

	void Init()override;
	void End()override;
	void Update()override;
	void Draw()override;
	void SetPos(const Vector3& pos) { GetTransform().position = pos; }
	bool Attack()override;
	bool CheckAttack()override;
	void CheckCollision()override;
	void Shot(const Transform& transform);
	void SetScale(float scale)override { m_scale = scale; }
	int GetWeaponType()override { return Weapon::Bow; }
private:
	FireBall* m_pFires[kFlameNum];
	Transform m_drawTransform;
};

