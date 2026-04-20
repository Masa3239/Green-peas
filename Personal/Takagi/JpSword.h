#pragma once
#include"Weapon.h"
#include"../../Chara/Collision.h"
#include"../../Utility/Transform.h"

class JpSword:public Weapon
{
public:
	JpSword(ObjectManager* objManager);
	~JpSword();

	void Init()override;
	void End()override;
	void Update()override;
	void Draw()override;
	//void SetPos(const Vector3& pos) { GetTransform().position = pos; }
	void Attack()override;
	//Collision::Capsule GetCollision()override { return m_circle; }
	bool CheckAttack()override;
	void CheckCollision()override;
	void SetScale(float scale)override { m_scale = scale; }

private:
	int m_effectHandle[kEffectFrame];
	float m_effectFrame;
	Transform m_effectTransform;
	bool m_attack;
	float m_desireRadian;
	Collision::Circle m_circle;
	float m_charge;
	bool m_chargeFlag;
};

