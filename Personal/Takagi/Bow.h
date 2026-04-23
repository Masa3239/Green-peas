#pragma once
#include"Weapon.h"

class Arrow;
class Bow:public Weapon
{
public:
	Bow(ObjectManager* objManager);
	~Bow();

	void Init()override;
	void End()override;
	void Update()override;
	void Draw()override;
	void SetPos(const Vector3& pos) { GetTransform().position = pos; }
	bool Attack()override;
	bool CheckAttack()override;
	//Collision::Circle GetCollision()override;
	void CheckCollision()override;
	void Shot(const Transform& transform);
	void SetScale(float scale)override { m_scale = scale; }
	int GetWeaponType()override { return Weapon::Bow; }
private:
	//bool attack;
	//float m_desireRadian;
	Arrow* m_pArrows[kBulletNum];
	Transform m_drawTransform;
};

