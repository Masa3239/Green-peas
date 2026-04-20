#pragma once
#include"Weapon.h"
#include"../../Object/GameObject.h"
#include"../../Chara/Collision.h"

class Sword:public Weapon
{
public:
	Sword(ObjectManager* objManager);
	~Sword();

	void Init()override;
	void End()override;
	void Update()override;
	void Draw()override;
	//void SetPos(const Vector3& pos) { GetTransform().position = pos; }
	void Attack()override;
	//Collision::Capsule GetCollision()override { return m_circle; }
	bool CheckAttack()override;
	void CheckCollision()override;
	void SetScale(float scale)override { m_scale = scale*m_scaleEx; }

private:
	int m_effectHandle[kEffectFrame];
	float m_effectFrame;
	Transform m_effectTransform;
	bool m_attack;
	float m_desireRadian;
	Collision::Capsule m_cupsule;
	float m_charge;
	bool m_chargeFlag;
	float m_scaleEx;
};

