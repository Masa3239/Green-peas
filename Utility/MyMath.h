#pragma once

#include <DxLib.h>

namespace MyMath {

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


}
