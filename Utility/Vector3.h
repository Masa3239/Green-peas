#pragma once

#include <DxLib.h>

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
};
