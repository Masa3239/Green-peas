#pragma once
#include"../Personal/Takagi/Player.h"
/// <summary>
/// シーンを超えて引き継ぐ変数
/// </summary>
typedef struct CarryOver {
public:
	/// <summary>
	/// キャラクターの職業
	/// </summary>
	Character::Job characterJob;
	/// <summary>
	/// クリアしたか
	/// </summary>
	bool isClear;
	/// <summary>
	/// 最大コンボ数
	/// </summary>
	int maxCombo;
	/// <summary>
	/// 最大ダメージ
	/// </summary>
	int maxDamage;

public:
	/// <summary>
	/// 変数をリセットする関数
	/// </summary>
	constexpr void Reset() {
		characterJob = Character::Job::Max;
		isClear = false;
		maxCombo = 0;
		maxDamage = 0;
	}
};