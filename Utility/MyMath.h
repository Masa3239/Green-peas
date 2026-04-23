#pragma once

#define NOMINMAX

#include <DxLib.h>
#include <algorithm>
#include <cmath>
#include "../Utility/Vector3.h"

namespace MyMath {

	// ラジアン角に変更する定数
	constexpr float ToRadian = DX_PI_F / 180.0f;
	// デグリー角に変更する定数
	constexpr float ToDegree = 180.0f / DX_PI_F;

	/// <summary>
	/// デグリー角度からラジアン角度へ変換
	/// </summary>
	/// <param name="deg">デグリー角度</param>
	/// <returns>ラジアン角度</returns>
	constexpr float DegToRad(float deg)
	{

		return deg * DX_PI_F / 180.0f;
	}

	/// <summary>
	/// ラジアン角度からデグリー角度へ変換
	/// </summary>
	/// <param name="rad">ラジアン角度</param>
	/// <returns>デグリー角度</returns>
	constexpr float RadToDeg(float rad)
	{

		return rad * 180.0f / DX_PI_F;
	}

	/// <summary>
	/// デグリー角度を-180°～180°の範囲に収める
	/// </summary>
	/// <param name="angle"></param>
	/// <returns></returns>
	constexpr float NormalizeAngle(float angle)
	{

		while (angle > 180.0f) angle -= 360.0f;
		while (angle < -180.0f) angle += 360.0f;

		return angle;
	}

	/// <summary>
	/// valueの値を最小値min、最大値maxの値に収める
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="value"></param>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	template<typename T>
	constexpr T Clamp(T value, T min, T max)
	{
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	/// <summary>
	/// 最大値からの割合を返す
	/// </summary>
	/// <param name="value">調べたい値</param>
	/// <param name="Max">最大値</param>
	/// <returns></returns>
	constexpr float Rate(float value, float max) {
		return value / max;
	}
	/// <summary>
	/// 調べた値の符号を返す関数
	/// </summary>
	/// <param name="value">調べたい値</param>
	/// <returns>正の数なら1、負の数なら-1を返す</returns>
	constexpr int Sign(float value) {
		int res = 1;
		if (value < 0)res = -1;
		return res;
	}

	/// <summary>
	/// 線形補間
	/// </summary>
	/// <param name="src">開始値</param>
	/// <param name="dst">最終値</param>
	constexpr float Lerp(float src, float dst, float latency)
	{
		return src + (dst - src) * latency;
	}
	/// <summary>
	/// 等速補間
	/// </summary>
	/// <param name="src">開始値</param>
	/// <param name="dst">最終値</param>
	/// <param name="amount">変化量</param>
	template <typename T>
	constexpr T Approach(T src, T dst, T amount)
	{
		if (src > dst)
		{
			return (std::max)(dst, src - amount);
		}
		else
		{
			return (std::min)(dst, src + amount);
		}
	}

	inline bool IsNearZero(float value, float epsilon = 0.001f)
	{
		if (std::abs(value) <= epsilon) return true;
		
		return false;
	}

		// 入力方向
	enum class FourDirection {
		Front,		// 手前
		Left,		// 左
		Right,		// 右
		Back,		// 奥
		Max
	};
	constexpr FourDirection Direction(float radian) {
		float angle = radian * MyMath::ToDegree;

		if (angle < 135 && angle >= 45)return FourDirection::Front;
		else if (angle < 45 && angle >= -45)return FourDirection::Right;
		else if (angle < -45 && angle >= -135)return FourDirection::Back;
		return FourDirection::Left;
	}

	/// <summary>
	/// 1D軸の値をデッドゾーン内の割合にフィルタリングする
	/// </summary>
	/// <param name="axis">軸</param>
	/// <param name="maxValue">最大値</param>
	/// <param name="deadzoneMin">デッドゾーンの最小割合</param>
	/// <param name="deadzoneMax">デッドゾーンの最大割合</param>
	/// <returns>デッドゾーンを適用して正規化した軸</returns>
	inline float Filter1D(int axis, int maxValue, float deadzoneMin, float deadzoneMax)
	{
		// デッドゾーンをmaxValueの割合に変換
		const int dzMin = static_cast<int>(maxValue * deadzoneMin);
		const int dzMax = static_cast<int>(maxValue * deadzoneMax);

		// 計算しやすくするために絶対値を取得する
		const int absAxis = std::abs(axis);

		float result = 0.0f;

		// デッドゾーンより小さい入力なら0とする
		if (absAxis < dzMin) return result;

		// デッドゾーンの最小値と最大値の間の割合を取得する
		result = static_cast<float>(absAxis - dzMin) / static_cast<float>(dzMax - dzMin);

		// 符号を復元する
		result *= MyMath::Sign(axis);

		// 値を-1から1に収める
		result = std::clamp(result, -1.0f, 1.0f);

		return result;
	}

	/// <summary>
	/// 2D軸の値をデッドゾーン内の割合にフィルタリングする
	/// </summary>
	/// <param name="axisX">軸X</param>
	/// <param name="axisY">軸Y</param>
	/// <param name="maxValue">最大値</param>
	/// <param name="deadzoneMin">デッドゾーンの最小割合</param>
	/// <param name="deadzoneMax">デッドゾーンの最大割合</param>
	/// <returns>デッドゾーンを適用して正規化した軸</returns>
	inline Vector2& Filter2D(float axisX, float axisY, float maxValue, float deadzoneMin, float deadzoneMax)
	{
		// デッドゾーンをmaxValueの割合に変換
		const int dzMin = maxValue * deadzoneMin;
		const int dzMax = maxValue * deadzoneMax;

		// ベクトルに変換
		const Vector2 dir = Vector2(axisX, axisY);

		const float len = dir.GetLength();

		Vector2 result = Vector2::zero;

		// デッドゾーンより小さい入力なら0とする
		if (len < dzMin) return result;

		// デッドゾーンの最小値と最大値の間の割合を取得する
		float rate = static_cast<float>(len - dzMin) / static_cast<float>(dzMax - dzMin);

		// 値を0から1に収める
		rate = std::clamp(rate, 0.0f, 1.0f);

		// スケーリング
		result = dir * (rate / len);

		return result;
	}
}
