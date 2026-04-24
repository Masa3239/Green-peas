#include "Tween.h"
#include <memory>
#include <unordered_map>
#include "AnimationCurve.h"
#include "Keyframe.h"

Tween::Tween()
{
}

void Tween::StartAnim(float* value)
{
	// すでにアニメーションさせていたら、上書きするために停止する
	if (mAnimCurves.find(value) != mAnimCurves.end())
	{
		StopAnim(value);
	}

	// アニメーションカーブを生成
	auto animCurve = std::make_shared<AnimationCurve>(value);
	// リストに追加する
	mAnimCurves.emplace(value, std::move(animCurve));
}

void Tween::StartAnim(float* value, const std::vector<Animation::Keyframe>& keyframes)
{
	// すでにアニメーションさせていたら、上書きするために停止する
	if (mAnimCurves.find(value) != mAnimCurves.end())
	{
		StopAnim(value);
	}

	// アニメーションカーブを生成
	auto animCurve = std::make_shared<AnimationCurve>(value, keyframes);
	// リストに追加する
	mAnimCurves.emplace(value, std::move(animCurve));
}

void Tween::StopAnim(float* value)
{
	// 要素を削除
	mAnimCurves.erase(value);
}

void Tween::StopAnimAll()
{
	// 全要素を削除
	mAnimCurves.clear();
}

void Tween::Update()
{
	// すべてのアニメーションカーブを更新する
	for (auto iter = mAnimCurves.begin(); iter != mAnimCurves.end();)
	{
		// 更新処理
		iter->second->Update();

		// アニメーションが終了したらリストから消す
		if (iter->second->IsCompleted())
		{
			// 削除してイテレータを次へ
			iter = mAnimCurves.erase(iter);
			continue;
		}

		// イテレータを次へ
		iter++;
	}
}

std::weak_ptr<AnimationCurve> Tween::GetAnimCurve(float* value)
{
	try
	{
		// ここでキーが存在しないなら例外が投げられる
		auto ptr = std::weak_ptr<AnimationCurve>(mAnimCurves.at(value));

		// ポインタを返す
		return ptr;
	}
	catch (const std::exception& e)
	{
		// 空のポインタを返す
		return std::weak_ptr<AnimationCurve>();
	}
}
