#pragma once
#include"Player.h"
class Wizard :public Player
{
public:
	/// <summary>
	/// プレイヤーのコンストラクタ
	/// メンバ変数の初期設定を行う
	/// </summary>
	Wizard(ObjectManager* objManager);

	/// <summary>
	/// プレイヤーのデストラクタ
	/// </summary>
	~Wizard();
	Character::Job GetPlayerJob()override { return Character::Job::Wizard; }
};
