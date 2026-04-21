#pragma once

#include <DxLib.h>
#include <cassert>
#include <cmath>

/// <summary>
/// 2次元ベクトル
/// </summary>
struct Vector2
{
	// 座標
	float x, y;

	/// <summary>
	/// 各成分を0で初期化
	/// </summary>
	constexpr Vector2() : x(0.0f), y(0.0f) {};

	/// <summary>
	/// 各成分を指定して初期化
	/// </summary>
	constexpr Vector2(float x, float y) : x(x), y(y) {};

	// 演算子

	constexpr Vector2 operator-() const { return Vector2(-x, -y); }

	constexpr Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
	constexpr Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
	constexpr Vector2 operator*(const float s) const { return Vector2(x * s, y * s); }
	constexpr Vector2 operator/(const float s) const
	{
		if (s == 0.0f)
		{
			assert(false && "Vector2 // 0除算が行われました");
			return Vector2();
		}

		return Vector2(x / s, y / s);
	}

	constexpr Vector2& operator+=(const Vector2& v)
	{
		x += v.x;
		y += v.y;

		return *this;
	}
	constexpr Vector2& operator-=(const Vector2& v)
	{
		x -= v.x;
		y -= v.y;

		return *this;
	}
	constexpr Vector2& operator*=(const float s)
	{
		x *= s;
		y *= s;

		return *this;
	}
	constexpr Vector2& operator/=(const float s)
	{
		if (s == 0.0f)
		{
			assert(false && "Vector2 // 0除算が行われました");
			return *this;
		}

		x /= s;
		y /= s;

		return *this;
	}

	constexpr bool operator==(const Vector2& v) const { return x == v.x && y == v.y; }
	constexpr bool operator!=(const Vector2& v) const { return x != v.x || y != v.y; }

	// ヘルパー関数

	/// <summary>
	/// 内積を計算する
	/// </summary>
	constexpr float Dot(const Vector2& v)
	{
		return (x * v.x) + (y * v.y);
	}

	/// <summary>
	/// 外積を計算する
	/// </summary>
	constexpr float Cross(const Vector2& v)
	{
		return (x * v.y) - (y * v.x);
	}

	/// <summary>
	/// ベクトルの長さを取得する
	/// 処理が重いため非推奨
	/// </summary>
	inline float GetLength() const
	{
		return std::sqrt(GetSqLength());
	}

	/// <summary>
	/// ベクトルの長さの2乗を取得する
	/// </summary>
	constexpr float GetSqLength() const
	{
		return x * x + y * y;
	}

	/// <summary>
	/// 正規化したベクトルを取得する
	/// </summary>
	constexpr Vector2 GetNormalize()
	{
		return *this / GetLength();
	}

	// 定数

	static const Vector2 zero;
	static const Vector2 one;
	static const Vector2 up;
	static const Vector2 down;
	static const Vector2 left;
	static const Vector2 right;
};

/// <summary>
/// 3次元ベクトル構造体
/// 基本的には値として使うことが多いので構造体で作成する
/// →publicで作っていくが、気になればprivateを使い分ける
/// 処理が膨大になってきたらクラスに変更すればいい
/// </summary>
struct Vector3
{
public:

	// 座標
	float x, y, z;

public:

	/// <summary>
	/// デフォルトコンストラクタ
	/// 要素のすべてを0で初期化する
	/// 定数宣言で使えるようにするために、
	/// constexprをつけてヘッダーに記載
	/// </summary>
	constexpr Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

	/// <summary>
	/// 引数ありのコンストラクタ
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	//=====================================================
	//		演算
	//=====================================================

	/// <summary>
	/// マイナスのベクトルを返す
	/// </summary>
	/// <returns></returns>
	Vector3 operator-() const;

	/// <summary>
	/// ベクトルの加算
	/// </summary>
	/// <param name="vec">足されるベクトル</param>
	/// <returns></returns>
	Vector3 operator+(const Vector3& vec) const;

	/// <summary>
	/// ベクトルの減算
	/// </summary>
	/// <param name="vec">引かれるベクトル</param>
	/// <returns></returns>
	Vector3 operator-(const Vector3& vec) const;

	/// <summary>
	/// ベクトルとスカラーの乗算
	/// </summary>
	/// <param name="scale">スカラー</param>
	/// <returns></returns>
	Vector3 operator*(float scale) const;

	/// <summary>
	/// ベクトルとスカラーの除算
	/// </summary>
	/// <param name="scale">スカラー</param>
	/// <returns></returns>
	Vector3 operator/(float scale) const;

	/// <summary>
	/// ベクトルとベクトルの加算代入
	/// 自身を変更するので参照を返す
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	Vector3& operator+=(const Vector3& vec);

	/// <summary>
	/// ベクトルとベクトルの減算代入演算子
	/// 自身を変更するので参照を返す
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	Vector3& operator-=(const Vector3& vec);

	/// <summary>
	/// ベクトルとスカラーの乗算代入演算子
	/// 自身を変更するので参照を返す
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	Vector3& operator*=(float scale);

	/// <summary>
	/// ベクトルとスカラーの除算代入演算子
	/// 自身を変更するので参照を返す
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	Vector3& operator/=(float scale);

	/// <summary>
	/// 要素に添え字でアクセス
	/// </summary>
	float operator[](int index) const;

	/// <summary>
	/// ベクトルの比較 等しいかどうか
	/// </summary>
	/// <param name="vec"></param>
	/// <returns>等しいならtrue</returns>
	bool operator==(const Vector3& vec) const;

	/// <summary>
	/// ベクトルの比較 等しくないかどうか
	/// </summary>
	/// <param name="vec"></param>
	/// <returns>等しくなければtrue</returns>
	bool operator!=(const Vector3& vec) const;

	/// <summary>
	/// 内積を計算する
	/// </summary>
	float Dot(const Vector3& v) const;

	/// <summary>
	/// 外積を計算する
	/// </summary>
	Vector3 Cross(const Vector3& v) const;

	/// <summary>
	/// ベクトルの長さを取得
	/// 平方根の処理が少し負荷があるので厳密な長さが必要じゃなければ非推奨
	/// </summary>
	/// <returns></returns>
	float GetLength() const;

	/// <summary>
	/// ベクトルの長さの二乗を取得
	/// </summary>
	/// <returns></returns>
	float GetSqLength() const;

	/// <summary>
	/// ベクトルを正規化したものを取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetNormalize() const;

	/// <summary>
	/// DxLibのVECTOR型に変換
	/// </summary>
	/// <returns></returns>
	VECTOR ToVECTOR() const;

	// 定数

	static const Vector3 zero;
	static const Vector3 one;
	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 left;
	static const Vector3 right;
	static const Vector3 forward;
	static const Vector3 back;
};
