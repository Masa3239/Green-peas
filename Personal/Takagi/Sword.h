#pragma once
#include"Weapon.h"
#include"../../Object/GameObject.h"
#include"../../Chara/Collision.h"
namespace {
	// 斬撃エフェクト画像のフレーム数
	constexpr int kEffectFrame = 8;
}
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

private:
	int m_effectHandle[kEffectFrame];
	float m_effectFrame;
	Transform m_effectTransform;
	bool m_attack;
	float m_desireRadian;
	Collision::Capsule m_cupsule;
};

