#include "AnimationCurve.h"
#include <DxLib.h>
#include <cmath>
#include <algorithm>
#include "../Utility/Time.h"

template <typename T>
float Pow(const T& value, const int exp)
{
	if (exp <= 0) return 0.0f;

	float result = value;

	for (int i = 0; i < exp - 1; i++)
	{
		result *= value;
	}

	return result;
}

AnimationCurve::AnimationCurve(float* value) :
	mPtrValue(value),
	mTime(0.0f)
{
}

AnimationCurve::AnimationCurve(float* value, const std::vector<Animation::Keyframe>& keyframes) :
	mKeyframes(keyframes),
	mPtrValue(value),
	mTime(0.0f)
{
}

void AnimationCurve::Update()
{
	mTime += Time::GetInstance().GetDeltaTime();

	UpdateValue();
}

void AnimationCurve::AddKeyframe(const float value, const float time, const Animation::Ease ease)
{
	// キーフレームを作成
	Animation::Keyframe keyframe {value, time, ease};

	// キーフレームをリストに追加
	mKeyframes.emplace_back(keyframe);

	// 小さい順に並び替える
	SortByTime();
}

void AnimationCurve::AddKeyframe(const Animation::Keyframe& keyframe)
{
	// キーフレームをリストに追加
	mKeyframes.emplace_back(keyframe);

	// 小さい順に並び替える
	SortByTime();
}

void AnimationCurve::UpdateValue()
{
	// 経過時間がすべてのキーフレームの範囲外なら値が更新されないため、更新
	if (mTime < mKeyframes.front().time)
	{
		*mPtrValue = mKeyframes.front().value;
		return;
	}
	else
	if (mTime > mKeyframes.back().time)
	{
		*mPtrValue = mKeyframes.back().value;
		return;
	}

	// 最後を除くすべてのキーフレームを調べる
	for (size_t i = 0; i < mKeyframes.size() - 1; i++)
	{
		// 開始時間
		float srcTime = mKeyframes[i].time;
		// 終了時間
		float dstTime = mKeyframes[i + 1].time;

		// 現在の時間がキーフレーム間にいないならスキップ
		if (!(mTime >= srcTime && mTime < dstTime)) continue;

		// 開始値
		float srcValue = mKeyframes[i].value;
		// 終了値
		float dstValue = mKeyframes[i + 1].value;

		// 変化量
		float change = dstValue - srcValue;
		// 開始時間からの経過時間
		float time = mTime - srcTime;
		// 開始地点から終了地点までの時間
		float duration = dstTime - srcTime;
		// 正規化した経過時間
		float normalizedTime = time / duration;

		// 現在の時間がt0からt1間にあるため、その範囲で補間する
		*mPtrValue = srcValue + change * Easing(mKeyframes[i].ease, normalizedTime);

		// この後のキーフレームは調べる必要がないため終了
		break;
	}
}

float AnimationCurve::Easing(Animation::Ease ease, float time)
{
	switch (ease)
	{
	case Animation::Ease::Linear:
		return time;

	case Animation::Ease::QuadIn:
		return Pow(time, 2);

	case Animation::Ease::QuadOut:
		return -Pow(1.0f - time, 2) + 1.0f;

	case Animation::Ease::QuadInOut:
		if (time < 0.5f)
		{
			return Pow(time * 2.0f, 2) * 0.5f;
		}
		else
		{
			return -Pow(time * 2.0f - 2.0f, 2) * 0.5f + 1.0f;
		}

	case Animation::Ease::CubicIn:
		return Pow(time, 3);

	case Animation::Ease::CubicOut:
		return Pow(time - 1.0f, 3) + 1.0f;

	case Animation::Ease::CubicInOut:
		if (time < 0.5f)
		{
			return Pow(time * 2.0f, 3) * 0.5f;
		}
		else
		{
			return Pow(time * 2.0f - 2.0f, 3) * 0.5f + 1.0f;
		}

	case Animation::Ease::QuartIn:
		return Pow(time, 4);

	case Animation::Ease::QuartOut:
		return -Pow(time - 1.0f, 4) + 1.0f;

	case Animation::Ease::QuartInOut:
		if (time < 0.5f)
		{
			return Pow(time * 2.0f, 4) * 0.5f;
		}
		else
		{
			return -Pow(time * 2.0f - 2.0f, 4) * 0.5f + 1.0f;
		}

	case Animation::Ease::QuintIn:
		return Pow(time, 5);

	case Animation::Ease::QuintOut:
		return Pow(time - 1.0f, 5) + 1.0f;

	case Animation::Ease::QuintInOut:
		if (time < 0.5f)
		{
			return Pow(time * 2.0f, 5) * 0.5f;
		}
		else
		{
			return Pow(time * 2.0f - 2.0f, 5) * 0.5f + 1.0f;
		}

	case Animation::Ease::ExpoIn:
		return std::pow(2.0f, 10.0f * (time - 1.0f));

	case Animation::Ease::ExpoOut:
		return -std::pow(2.0f, -10.0f * time) + 1.0f;

	case Animation::Ease::ExpoInOut:
		if (time < 0.5f)
		{
			return std::pow(2.0f, 10.0f * (time - 0.5f) * 2.0f) * 0.5f;
		}
		else
		{
			return -std::pow(2.0f, -10.0f * (time - 0.5f) * 2.0f) * 0.5f + 1.0f;
		}

	case Animation::Ease::SineIn:
		return -std::cos(time * DX_PI_F * 0.5f) + 1.0f;

	case Animation::Ease::SineOut:
		return std::sin(time * DX_PI_F * 0.5f);

	case Animation::Ease::SineInOut:
		return std::sin((time - 0.5f) * DX_PI_F) * 0.5f + 0.5f;

	case Animation::Ease::CircIn:
		return -std::sqrt(1.0f - Pow(time, 2)) + 1.0f;

	case Animation::Ease::CircOut:
		return std::sqrt(1.0f - Pow(time - 1.0f, 2));

	case Animation::Ease::CircInOut:
		if (time < 0.5f)
		{
			return (-std::sqrt(1.0f - Pow(time * 2.0f, 2)) + 1.0f) * 0.5f;
		}
		else
		{
			return (std::sqrt(1.0f - Pow((time - 1.0f) * 2.0f, 2)) + 1.0f) * 0.5f;
		}

	case Animation::Ease::BackIn:
	{
		const float c1 = 1.70158f;
		const float c3 = c1 + 1.0f;

		return Pow(time, 2) * (c3 * time - c1);
	}

	case Animation::Ease::BackOut:
	{
		const float c1 = 1.70158f;
		const float c3 = c1 + 1.0f;

		return Pow(time - 1, 2) * (c3 * (time - 1) + c1) + 1.0f;
	}

	case Animation::Ease::BackInOut:
	{
		const float c1 = 1.70158f;
		const float c2 = c1 * 1.525f;
		const float c4 = c2 + 1.0f;

		if (time < 0.5f)
		{
			return Pow(time * 2.0f, 2) * (c4 * (time * 2) - c2) * 0.5f;
		}
		else
		{
			return Pow((time - 1.0f) * 2.0f, 2) * (c4 * ((time - 1.0f) * 2.0f) + c2) * 0.5f + 1.0f;
		}
	}

	case Animation::Ease::ElasticIn:
	{
		const float c4 = (2.0f * DX_PI_F) / 3.0f;

		return -std::pow(2.0f, 10.0f * time - 10.0f) * std::sin((time * 10.0f - 10.75f) * c4);
	}

	case Animation::Ease::ElasticOut:
	{
		const float c4 = (2.0f * DX_PI_F) / 3.0f;

		return std::pow(2.0f, -10.0f * time) * std::sin((time * 10.0f - 0.75f) * c4) + 1.0f;
	}

	case Animation::Ease::ElasticInOut:
	{
		const float c5 = (2.0f * DX_PI_F) / 4.5f;

		if (time < 0.5f)
		{
			return -std::pow(2.0f, 10.0f * (time * 2.0f) - 10.0f) * std::sin(((time * 2.0f) * 10.0f - 11.125) * c5) * 0.5f;
		}
		else
		{
			return std::pow(2.0f, -10.0f * (time * 2.0f) + 10.0f) * std::sin(((time * 2.0f) * 10.0f - 11.125) * c5) * 0.5f + 1.0f;
		}
	}

	case Animation::Ease::BounceIn:
		return 1.0f - Easing(Animation::Ease::BounceOut, 1.0 - time);

	case Animation::Ease::BounceOut:
	{
		const float n1 = 7.5625;
		const float d1 = 2.75;

		if (time < 1.0f / d1)
		{
			return n1 * Pow(time, 2);
		}
		else
		if (time < 2.0f / d1)
		{
			return n1 * Pow(time - 1.5f / d1, 2) + 0.75f;
		}
		else
		if (time < 2.5f / d1)
		{
			return n1 * Pow(time - 2.25f / d1, 2) + 0.9375f;
		}
		else
		{
			return n1 * Pow(time - 2.625f / d1, 2) + 0.984375f;
		}
	}

	case Animation::Ease::BounceInOut:
		if (time < 0.5f)
		{
			return (1.0f - Easing(Animation::Ease::BounceOut, 1.0 - time * 2.0f)) * 0.5f;
		}
		else
		{
			return (1.0f + Easing(Animation::Ease::BounceOut, -1.0 + time * 2.0f)) * 0.5f;
		}
	}

	return 0.0f;
}

void AnimationCurve::SortByTime()
{
	// 時間の小さい順にキーフレームを読み込むために小さい順に並び替える
	std::sort(mKeyframes.begin(), mKeyframes.end(),
		[](const Animation::Keyframe& a, const Animation::Keyframe& b)
		{
			return (a.time < b.time);
		});
}
