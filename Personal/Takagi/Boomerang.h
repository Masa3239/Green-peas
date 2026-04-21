#pragma once
#include"Weapon.h"
#include"../../Object/GameObject.h"
#include"../../Chara/Collision.h"
#include"../../Utility/Transform.h"

/// <summary>
/// ブーメランのクラス
/// </summary>
class Boomerang :public Weapon
{
public:
	Boomerang(ObjectManager* objManager);
	~Boomerang();

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
	int GetWeaponType()override { return Weapon::Boomerang; }
private:
	Transform m_attack;
	float m_speed;
	bool m_attackFlag;
	Collision::Circle m_circle;
	float m_drawAngle;
};

