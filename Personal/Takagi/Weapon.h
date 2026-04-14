#pragma once
#include"../../Object/GameObject.h"
class Weapon:public GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Weapon(ObjectManager* objManager);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Weapon();

	void Init()override = 0;
	void End()override = 0;
	void Update()override = 0;
	void Draw()override = 0;
};

