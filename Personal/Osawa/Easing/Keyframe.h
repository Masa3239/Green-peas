#pragma once

/// <summary>
/// アニメーションカーブで使用するデータ
/// </summary>
namespace Animation
{
	/// <summary>
	/// イージングの種類
	/// </summary>
	enum class Ease
	{
		Linear,			// 直線
		QuadIn,			// 二次
		QuadOut,		// 二次
		QuadInOut,		// 二次
		CubicIn,		// 三次
		CubicOut,		// 三次
		CubicInOut,		// 三次
		QuartIn,		// 四次
		QuartOut,		// 四次
		QuartInOut,		// 四次
		QuintIn,		// 五次
		QuintOut,		// 五次
		QuintInOut,		// 五次
		ExpoIn,			// 指数
		ExpoOut,		// 指数
		ExpoInOut,		// 指数
		SineIn,			// 三角関数
		SineOut,		// 三角関数
		SineInOut,		// 三角関数
		CircIn,			// 円形
		CircOut,		// 円形
		CircInOut,		// 円形
		BackIn,			// バック
		BackOut,		// バック
		BackInOut,		// バック
		ElasticIn,		// 弾性
		ElasticOut,		// 弾性
		ElasticInOut,	// 弾性
		BounceIn,		// バウンド
		BounceOut,		// バウンド
		BounceInOut		// バウンド
	};

	/// <summary>
	/// キーフレーム
	/// </summary>
	struct Keyframe
	{
		float value;
		float time = 0.0f;
		Ease ease = Ease::Linear;
	};
}