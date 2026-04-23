#pragma once
#include"Weapon.h"

class Thunder;

namespace {
}


class ThunderWand :public Weapon
{
public:
	ThunderWand(ObjectManager* objManager);
	~ThunderWand();

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
	int GetWeaponType()override { return Weapon::Flame; }
private:
	Thunder* m_pThunders[kBulletNum];
	Transform m_drawTransform;
	Vector3 m_swingPos;
	float m_verticalSpeed;
};

