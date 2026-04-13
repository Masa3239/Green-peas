#pragma once

#include "../Utility/Vector3.h"
#include "../Utility/MyMath.h"

/// <summary>
/// 位置、回転、拡縮を管理する構造体
/// </summary>
struct Transform
{
public:

	/// <summary>
	/// 座標（ワールド）
	/// </summary>
	Vector3 position{ 0.0f, 0.0f, 0.0f };

	/// <summary>
	/// 回転（ラジアン）
	/// 三角関数との親和性を考慮してラジアンで扱う
	/// </summary>
	Vector3 rotation{ 0.0f, 0.0f, 0.0f };

	/// <summary>
	/// 拡大率（1.0倍が等倍）
	/// </summary>
	Vector3 scale{ 1.0f, 1.0f, 1.0f };

public:

	/// <summary>
	/// 移動
	/// </summary>
	/// <param name="vec">移動成分のベクトル</param>
	void Translate(const Vector3& vec) { position += vec; }

	/// <summary>
	/// 回転 引数のベクトルはラジアン角
	/// </summary>
	/// <param name="vec">回転成分のベクトル</param>
	void RotateRad(const Vector3& vec) { rotation += vec; }

	/// <summary>
	/// 回転 引き数のベクトルはデグリー角
	/// </summary>
	/// <param name="vecDeg">回転成分のベクトル</param>
	void RotateDeg(const Vector3& vecDeg)
	{
		rotation.x += MyMath::DegToRad(vecDeg.x);
		rotation.y += MyMath::DegToRad(vecDeg.y);
		rotation.z += MyMath::DegToRad(vecDeg.z);
	}

	/// <summary>
	/// 角度を指定 引数のベクトルはデグリー角
	/// </summary>
	/// <param name="vecDeg">回転成分のベクトル</param>
	void SetRotateDeg(const Vector3& vecDeg)
	{
		rotation.x = MyMath::DegToRad(vecDeg.x);
		rotation.z = MyMath::DegToRad(vecDeg.z);
		rotation.y = MyMath::DegToRad(vecDeg.y);
	}

	/// <summary>
	/// 回転の値をデグリー角で取得 デバッグで使用する想定
	/// </summary>
	/// <returns>デグリー角の回転成分</returns>
	Vector3 GetRotateDeg() const
	{
		return {
			MyMath::RadToDeg(rotation.x),
			MyMath::RadToDeg(rotation.y),
			MyMath::RadToDeg(rotation.z)
		};
	}

	/// <summary>
	/// Transformを初期状態に戻す
	/// </summary>
	void Reset()
	{
		position = { 0.0f, 0.0f, 0.0f };
		rotation = { 0.0f, 0.0f, 0.0f };
		scale = { 1.0f, 1.0f, 1.0f };
	}
};
