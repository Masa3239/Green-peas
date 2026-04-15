#pragma once
#include"Weapon.h"
class Sword:public Weapon
{
public:
	Sword();
	~Sword();

	void Init()override;
	void End()override;
	void Update()override;
	void Draw()override;
};

