#include "Collision.h"
#include <cassert>
#include <DxLib.h>
#include "../Utility/Color.h"

namespace Collision
{
	bool Circle::CheckCollision(const Shape& other) const
	{
		// 当たった形状が球だったら
		if (other.GetType() == Type::Circle)
		{
			// 相手の座標を取得するために
			// Sphereクラスをdynamic_castして派生クラスであるSphereクラスを用意する
			// memo：dynamic_castを避けた実装方法もある
			// ダブルディスパッチ こちらのほうが高度だが、処理負荷が軽い
			// これを使って衝突判定を作ったらポートフォリオには絶対に書くようにする
			const Circle* checkSphere = dynamic_cast<const Circle*>(&other);
			
			// GetTypeでType::Sphereがとれているから大丈夫なはずだけど確認
			assert(checkSphere);

			// 球の中心座標からチェックする球の中心座標を指すベクトルを求める
			Vector3 dif = this->GetPosition() - checkSphere->GetPosition();

			// ベクトルの各成分から距離を三平方の定理で求める
			float distance = dif.GetSqLength();
			//float distance = dif.x * dif.x + dif.y * dif.y + dif.z * dif.z;	授業用にイメージしやすく書かれたもの
			float radiusSum = this->m_radius + checkSphere->m_radius;

			// もし2つの判定の和がdistanceより短ければ当たっている
			// 半径の和を2乗しているのはdistanceを平方根にしていないため（平方根の計算は不可がかかる）
			return distance <= (radiusSum * radiusSum);
		}

		return false;
	}

	void Circle::DebugDraw() const
	{
		// 円の当たり判定を表示
		DrawCircle(m_center.x,m_center.y, m_radius, Color::kWhite, false);
	}

	AABB::AABB(const Vector3& center, const Vector3& size)
	{
		SetSize(size);
		SetPosition(center);
	}

	bool AABB::CheckCollision(const Shape& other) const
	{
		// ここではAABB vs AABBの当たり判定の計算を行う
		// 形状がAABBだったら
		if (other.GetType() != Type::AABB) return false;

		// 相手の座標を取得するためにAABBクラスをdynamic_castして取得する
		const AABB* checkBox = dynamic_cast<const AABB*>(&other);

		assert(checkBox);

		if (m_maxPos.x < checkBox->m_minPos.x) return false;
		if (m_minPos.x > checkBox->m_maxPos.x) return false;

		if (m_maxPos.y < checkBox->m_minPos.y) return false;
		if (m_minPos.y > checkBox->m_maxPos.y) return false;
		// Z軸は使わない
		//if (m_maxPos.z < checkBox->m_minPos.z) return false;
		//if (m_minPos.z > checkBox->m_maxPos.z) return false;

		// ここまで来たら当たっている
		return true;
	}

	void AABB::SetPosition(const Vector3& pos)
	{
		m_minPos = pos - m_halfSize;
		m_maxPos = pos + m_halfSize;
	}

	Vector3 AABB::GetPosition() const
	{
		return (m_minPos + m_maxPos) * 0.5f;
		//return m_minPos + m_halfSize;
	}

	void AABB::DebugDraw() const
	{
		DrawBox(m_minPos.x, m_minPos.y, m_maxPos.x, m_maxPos.y, Color::kWhite, FALSE);
	}

	void AABB::SetSize(const Vector3& size)
	{
		m_halfSize = size * 0.5f;
	}
}
