#pragma once

#include "../Personal/Osawa/Enemy/EnemyManager.h"
#include"../Utility/Vector3.h"
#include <DxLib.h>

#include<string>//Split関数で使用する


struct EnemySpawnData
{
	EnemyManager::EnemyType type;
	int level;
	Vector3 pos;
};

//各種番号メモ
enum EnemyNum {
	//空白
	None = 0,
	//近距離雑魚
	Melee=1,
	//遠距離雑魚
	Shooter=2,
	//中ボス
	Miniboss=3,

};