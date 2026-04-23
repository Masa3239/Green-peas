#pragma once

#include "../Personal/Osawa/Enemy/EnemyManager.h"
#include"../Utility/Vector3.h"
#include <DxLib.h>

#include<string>//Split関数で使用する


struct EnemySpawnData
{
	EnemyManager::EnemyType type;
	Vector3 pos;
};
