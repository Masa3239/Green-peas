#pragma once

namespace Animation {

	/// <summary>
	/// プレイヤーのアニメーションID
	/// ここの名前はある程度自分でわかりやすい名前にしてもいい
	/// </summary>
	enum class PlayerAnimation {

		Neutral = 0,
		Run,
		Jump,
		Attack,
		Max
	};

	/// <summary>
	/// アニメーションのデータ
	/// </summary>
	struct AnimationData
	{
		int index;			// アニメーションの番号
		bool isLoop;		// ループするかどうか
		bool isForcePlay;	// 割り込みができないかどうか
	};
}
