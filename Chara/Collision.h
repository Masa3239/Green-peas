#pragma once

#include "../Utility/Vector3.h"
#include <array>

/// <summary>
/// 衝突判定関連のデータや処理
/// </summary>
namespace Collision
{
	/// <summary>
	/// 形状データ
	/// </summary>
	enum class Type
	{
		Circle,		// 円
		AABB,		// Axis Aligne Bounding Box	回転しない
		OBB,			// Oriented Bounding Box	回転する
		Capsule		// カプセル
	};
	/// <summary>
	/// 衝突判定の形状の抽象クラス
	/// これを継承して様々な形状で対応できるようにする
	/// </summary>
	class Shape
	{
	public:

		virtual ~Shape() = default;

		/// <summary>
		/// 形状データを取得する
		/// </summary>
		/// <returns></returns>
		virtual Type GetType() const = 0;

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		virtual bool CheckCollision(const Shape& other) const = 0;

		/// <summary>
		/// 座標を更新
		/// </summary>
		/// <param name="pos"></param>
		virtual void SetPosition(const Vector3& pos) = 0;

		/// <summary>
		/// 座標を取得する
		/// </summary>
		/// <returns></returns>
		virtual Vector3 GetPosition() const = 0;

		/// <summary>
		/// 形状のデバッグ描画
		/// </summary>
		virtual void DebugDraw() const = 0;
	};

	/// <summary>
	/// 衝突判定の円の形状のクラス
	/// </summary>
	class Circle : public Shape
	{
	public:

		Circle() = default;
		Circle(const Vector3& pos, float radius) : m_center(pos), m_radius(radius) {}

		~Circle() = default;

		/// <summary>
		/// 形状データの取得
		/// </summary>
		/// <returns></returns>
		Type GetType() const override { return Type::Circle; }

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool CheckCollision(const Shape& other) const override;

		/// <summary>
		/// 座標の更新 中心座標
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos) override { m_center = pos; }

		/// <summary>
		/// 球の中心座標の取得
		/// </summary>
		/// <returns></returns>
		Vector3 GetPosition() const override { return m_center; }
		/// <summary>
		/// 円の半径の設定
		/// </summary>
		/// <param name="radius"></param>
		void SetRadius(float radius) { m_radius = radius; }
		/// <summary>
		/// 円の半径の取得
		/// </summary>
		/// <returns></returns>
		float GetRadius() const { return m_radius; }

		/// <summary>
		/// 球のデバッグ描画
		/// </summary>
		void DebugDraw() const override;

	private:

		/// <summary>
		/// 球の中心座標
		/// </summary>
		Vector3 m_center;

		/// <summary>
		/// 球の半径
		/// </summary>
		float m_radius;
	};

	class AABB : public Shape
	{
	public:

		AABB() = default;
		AABB(const Vector3& center, const Vector3& size);

		~AABB() = default;

		/// <summary>
		/// 形状データの取得
		/// </summary>
		/// <returns></returns>
		Type GetType() const override { return Type::AABB; }

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool CheckCollision(const Shape& other) const override;

		/// <summary>
		/// 中心座標を更新する
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos) override;

		/// <summary>
		/// 中心座標を取得する
		/// </summary>
		/// <returns></returns>
		Vector3 GetPosition() const override;

		/// <summary>
		/// AAVVのデバッグ描画
		/// </summary>
		void DebugDraw() const override;

		/// <summary>
		/// 点がAABB内に入っているかどうかを調べる
		/// </summary>
		/// <param name="pos"></param>
		/// <returns></returns>
		bool CheckPointInAABB(const Vector3& pos)const;
		/// <summary>
		/// 点と四角の最短距離を調べる
		/// </summary>
		/// <param name="pos"></param>
		/// <returns></returns>
		float Measure(const Vector3& pos)const;
		 Vector3 GetMaxPos()const { return m_maxPos; }
		Vector3 GetMinPos()const { return m_minPos; }
	private:

		void SetSize(const Vector3& size);

		Vector3 m_minPos;
		Vector3 m_maxPos;
		Vector3 m_halfSize;

	};

	/// <summary>
	/// 衝突判定のOBBの形状のクラス
	/// 現在2次元専用
	/// 参考：http://marupeke296.com/COL_3D_No13_OBBvsOBB.html
	/// </summary>
	class OBB : public Shape
	{
	public:

		OBB() = default;
		OBB(const Vector3& center, const Vector3& size);
		OBB(const Vector3& center, const Vector3& size, float radian);

		~OBB() = default;

		/// <summary>
		/// 方向ベクトルの方向
		/// </summary>
		enum Dir
		{
			Width,	// 幅(x)
			Height,	// 高さ(y)
			Depth,	// 奥行(z) 使えない
			Length,
		};

		/// <summary>
		/// 形状データの取得
		/// </summary>
		/// <returns></returns>
		Type GetType() const override { return Type::OBB; }

		/// <summary>
		/// 衝突判定
		/// </summary>
		bool CheckCollision(const Shape& other) const override;

		/// <summary>
		/// 中心座標を更新する
		/// </summary>
		void SetPosition(const Vector3& pos) override { m_centerPos = pos; }
		/// <summary>
		/// 中心座標を取得する
		/// </summary>
		Vector3 GetPosition() const override { return m_centerPos; }

		/// <summary>
		/// 角度の変更
		/// </summary>
		/// <param name="radian">ラジアン角</param>
		void SetRadian(const float radian);

		/// <summary>
		/// AAVVのデバッグ描画
		/// </summary>
		void DebugDraw() const override;
		
	private:

		/// <summary>
		/// 方向ベクトルの更新
		/// </summary>
		void UpdateDirVector();

		/// <summary>
		/// 投影線分の長さの半分を計算する
		/// </summary>
		/// <param name="separate">分離軸</param>
		/// <param name="width">幅の軸</param>
		/// <param name="height">高さの軸</param>
		/// <returns>投影線分の長さの半分</returns>
		float GetProjectionLength(const Vector3& separate, const Vector3& e1, const Vector3& e2) const;

		/// <summary>
		/// ベクトルを回転させる
		/// </summary>
		Vector3 RotateVector(Vector3 vec) const;

		/// <summary>
		/// 中心座標
		/// </summary>
		Vector3 m_centerPos;

		/// <summary>
		/// 大きさの半分
		/// </summary>
		Vector3 m_halfSize;

		/// <summary>
		/// 角度
		/// </summary>
		float m_radian;

		/// <summary>
		/// 方向ベクトル
		/// </summary>
		std::array<Vector3, Dir::Length> m_dirVector;
	};
	/// <summary>
/// 衝突判定の円の形状のクラス
/// </summary>
	class Capsule : public Shape
	{
	public:

		Capsule() = default;
		Capsule(const Vector3& start,const Vector3& end, float radius) : m_start(start),m_end(end), m_radius(radius) {}

		~Capsule() = default;

		/// <summary>
		/// 形状データの取得
		/// </summary>
		/// <returns></returns>
		Type GetType() const override { return Type::Capsule; }

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool CheckCollision(const Shape& other) const override;
		/// <summary>
		/// 中心座標を更新する
		/// </summary>
		void SetPosition(const Vector3& pos) override {}
		/// <summary>
		/// 中心座標を取得する
		/// </summary>
		Vector3 GetStartPos() const { return m_start; }
		Vector3 GetEndPos() const { return m_end; }
		Vector3 GetPosition() const override { return (m_start+m_end)/2; }
		/// <summary>
		/// 座標の更新 始点
		/// </summary>
		/// <param name="pos"></param>
		void SetStartPos(const Vector3& pos) { m_start = pos; }
		/// <summary>
		/// 座標の更新 終点
		/// </summary>
		/// <param name="pos"></param>
		void SetEndPos(const Vector3& pos) { m_end = pos; }
		/// <summary>
		/// 半径の設定
		/// </summary>
		/// <param name="radius"></param>
		void SetRadius(float radius) { m_radius = radius; }
		/// <summary>
		/// 円の半径の取得
		/// </summary>
		/// <returns></returns>
		float GetRadius() const { return m_radius; }

		/// <summary>
		/// 球のデバッグ描画
		/// </summary>
		void DebugDraw() const override;

	private:

		/// <summary>
		/// 球の中心座標
		/// </summary>
		Vector3 m_start;
		Vector3 m_end;

		/// <summary>
		/// 球の半径
		/// </summary>
		float m_radius;
	};
};
