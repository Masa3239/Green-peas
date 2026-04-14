#pragma once

#include "../Utility/Vector3.h"

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
		AABB		// Axis Aligne Bounding Box	回転しない
		//OBB		// Oriented Bounding Box	回転する
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
		/// 円の半径の取得
		/// </summary>
		/// <returns></returns>
		float GetRadius() const  { return m_radius; }

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
	private:

		void SetSize(const Vector3& size);

		Vector3 m_minPos;
		Vector3 m_maxPos;
		Vector3 m_halfSize;

	};

};
