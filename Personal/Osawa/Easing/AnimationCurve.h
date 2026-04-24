#pragma once

#include <vector>
#include "Keyframe.h"

/// <summary>
/// 値を補間移動し、キーフレームを管理するクラス
/// </summary>
class AnimationCurve
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="value">アニメーションさせる変数のポインタ</param>
	AnimationCurve(float* value);

	/// <summary>
	/// 引数ありコンストラクタ
	/// 初期化時にキーフレームを渡す
	/// </summary>
	/// <param name="value">アニメーションさせる変数のポインタ</param>
	/// <param name="keyframes">キーフレームの配列</param>
	AnimationCurve(float* value, const std::vector<Animation::Keyframe>& keyframes);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~AnimationCurve() = default;
	
	/// <summary>
	/// 更新処理
	/// キーフレームを補間する
	/// </summary>
	void Update();

	/// <summary>
	/// キーフレームを作成して追加する
	/// </summary>
	/// <param name="value">値</param>
	/// <param name="time">時間</param>
	/// <param name="ease">イージングの種類</param>
	void AddKeyframe(const float value, const float time, const Animation::Ease ease = Animation::Ease::Linear);
	/// <summary>
	/// キーフレームを直接追加する
	/// </summary>
	/// <param name="keyframe">キーフレーム</param>
	void AddKeyframe(const Animation::Keyframe& keyframe);

	/// <summary>
	/// アニメーションが完了しているかを取得する
	/// </summary>
	/// <returns>完了していたらtrue</returns>
	bool IsCompleted() const { return mTime > mKeyframes.back().time; };

private:

	/// <summary>
	/// 値を更新する
	/// </summary>
	void UpdateValue();

	/// <summary>
	/// 補間処理
	/// </summary>
	/// <param name="ease">イージングの種類</param>
	/// <param name="time">正規化された時間</param>
	float Easing(Animation::Ease ease, float time);

	/// <summary>
	/// キーフレームを時間順に並び替える
	/// </summary>
	void SortByTime();

	/// <summary>
	/// キーフレームのリスト
	/// 時間順に並んでいる
	/// </summary>
	std::vector<Animation::Keyframe> mKeyframes;

	/// <summary>
	/// アニメーションさせる変数のポインタ
	/// </summary>
	float* mPtrValue;

	/// <summary>
	/// 経過時間
	/// </summary>
	float mTime;
};
