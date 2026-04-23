#pragma once
#include"Player.h"
class Hunter :public Player
{
public:
	/// <summary>
	/// プレイヤーのコンストラクタ
	/// メンバ変数の初期設定を行う
	/// </summary>
	Hunter(ObjectManager* objManager);

	/// <summary>
	/// プレイヤーのデストラクタ
	/// </summary>
	~Hunter();
	Character::Job GetPlayerJob()override { return Character::Job::Hunter; }
};