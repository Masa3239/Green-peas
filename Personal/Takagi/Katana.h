#pragma once
#include"Weapon.h"
#include"../../Chara/Collision.h"
#include"../../Utility/Transform.h"

class Katana:public Weapon
{
public:
	Katana(ObjectManager* objManager);
	~Katana();

	void Init()override;
	void End()override;
	void Update()override;
	void Draw()override;
	//void SetPos(const Vector3& pos) { GetTransform().position = pos; }
	bool Attack()override;
	//Collision::Capsule GetCollision()override { return m_circle; }
	bool CheckAttack()override;
	void CheckCollision()override;
	void SetScale(float scale)override { m_scale = scale; }
	int GetWeaponType()override { return Weapon::Katana; }

private:
	int m_effectHandle[kEffectFrame];
	float m_effectFrame;
	Transform m_effectTransform;
	bool m_attack;
	float m_desireRadian;
	Collision::Circle m_circle;
	float m_charge;
	bool m_chargeFlag;
	float m_chaergeScale;
};

