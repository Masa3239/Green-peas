#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include "Keyframe.h"

class AnimationCurve;

/// <summary>
/// 値を補間移動させるアニメーションカーブの管理と更新を行う
/// </summary>
class Tween
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Tween();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Tween() = default;

	/// <summary>
	/// アニメーションを開始する
	/// </summary>
	/// <param name="value">アニメーションさせたい変数のポインタ</param>
	void StartAnim(float* value);

	/// <summary>
	/// アニメーションを開始する
	/// 初期化時にキーフレームを設定させる
	/// </summary>
	/// <param name="value">アニメーションさせたい変数のポインタ</param>
	/// <param name="keyframes">キーフレームの配列</param>
	void StartAnim(float* value, const std::vector<Animation::Keyframe>& keyframes);

	/// <summary>
	/// 指定したアニメーションを終了する
	/// </summary>
	/// <param name="value">終了させたい変数のポインタ</param>
	void StopAnim(float* value);

	/// <summary>
	/// アニメーションをすべて終了する
	/// </summary>
	void StopAnimAll();

	/// <summary>
	/// アニメーションカーブの更新
	/// </summary>
	void Update();

	/// <summary>
	/// アニメーションカーブを取得する
	/// キーの追加等を行う
	/// </summary>
	/// <param name="value">アニメーションさせている変数のポインタ</param>
	/// <returns>アニメーションカーブのポインタ</returns>
	std::weak_ptr<AnimationCurve> GetAnimCurve(float* value);

private:

	/// <summary>
	/// アニメーションカーブのリスト
	/// </summary>
	std::unordered_map<float*, std::shared_ptr<AnimationCurve>> mAnimCurves;
};
