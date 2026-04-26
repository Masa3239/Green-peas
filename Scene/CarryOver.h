#pragma once
#include"../Personal/Takagi/Player.h"
namespace Score {
	enum class Result {
		Clear,
		Failed,
		Max
};
}
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
	Score::Result isClear;
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
		isClear = Score::Result::Max;
		maxCombo = 0;
		maxDamage = 0;
	}
};