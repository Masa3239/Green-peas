#pragma once
#include"Weapon.h"
#include"../../Object/GameObject.h"

class Sword:public Weapon,public GameObject
{
public:
	Sword(ObjectManager* objManager);
	~Sword();

	void Init()override;
	void End()override;
	void Update()override;
	void Draw()override;
	void SetPos(const Vector3& pos) { GetTransform().position = pos; }
	void Attack();

private:
	bool attack;
};

