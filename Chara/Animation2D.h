#pragma once

namespace Animation
{
	/// <summary>
	/// 2Dアニメーションのデータ
	/// </summary>
	struct Animation2DData
	{
		int index;			// アニメーションの番号
		float duration;		// アニメーションフレームを切り替える間隔（フレーム数）
		bool isLoop;		// ループするかどうか
		bool isForcePlay;	// 割り込みができないかどうか
	};
}
