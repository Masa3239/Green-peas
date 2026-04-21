#include "Collision.h"
#include <cassert>
#include <cmath>
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
		else if (other.GetType() == Type::AABB) {
			const Circle checkCircle = Circle(GetPosition(), GetRadius());
			if (other.CheckCollision(checkCircle))return true;
		}
		else if (other.GetType() == Type::Capsule) {
			const Capsule* check = dynamic_cast<const Capsule*>(&other);
			Vector3 start = check->GetStartPos();
			Vector3 end = check->GetEndPos();
			const float distance = Segment_Point_MinLength(start.ToVECTOR(), end.ToVECTOR(), m_center.ToVECTOR());
			if (distance <= m_radius + check->GetRadius())return true;
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
		//if (other.GetType() != Type::AABB) return false;
		if (other.GetType() == Type::AABB) {

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
		}
		else if (other.GetType() == Type::Circle) {
			const Circle* checkCircle = dynamic_cast<const Circle*>(&other);
			// 円の中心が四角の中にある時true
			if (CheckPointInAABB(checkCircle->GetPosition())) {
				return true;
			}
			// 円の中心が四角の中にない時
			// 四角と点の最短距離が円の半径よりも大きいときfalseを返す
			if (checkCircle->GetRadius()<Measure(checkCircle->GetPosition())) {
				return false;
			}
		
		}
		else if (other.GetType() == Type::Capsule) {
			const Capsule* check = dynamic_cast<const Capsule*>(&other);
			Vector3 start = check->GetStartPos();
			Vector3 end = check->GetEndPos();
			Vector3 rightTop = { m_maxPos.x,m_minPos.y,0 };
			Vector3 leftBottom = { m_minPos.x,m_maxPos.y,0 };
			float distance = Segment_Segment_MinLength(start.ToVECTOR(), end.ToVECTOR(), m_minPos.ToVECTOR(), rightTop.ToVECTOR());
			if (distance <= check->GetRadius())return true;
			distance = Segment_Segment_MinLength(start.ToVECTOR(), end.ToVECTOR(), m_minPos.ToVECTOR(), leftBottom.ToVECTOR());
			if (distance <= check->GetRadius())return true;
			distance = Segment_Segment_MinLength(start.ToVECTOR(), end.ToVECTOR(), leftBottom.ToVECTOR(), m_maxPos.ToVECTOR());
			if (distance <= check->GetRadius())return true;
			distance = Segment_Segment_MinLength(start.ToVECTOR(), end.ToVECTOR(), m_maxPos.ToVECTOR(), rightTop.ToVECTOR());
			if (distance <= check->GetRadius())return true;
			if (CheckPointInAABB(check->GetStartPos()))return true;
			if (CheckPointInAABB(check->GetEndPos()))return true;
			return false;
		}
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
	bool AABB::CheckPointInAABB(const Vector3& pos)const
	{
		// X座標が四角の範囲外ならfalse
		if (pos.x < m_minPos.x)return false;
		if (pos.x > m_maxPos.x)return false;
		// Y座標が四角の範囲外ならfalse
		if (pos.y < m_minPos.y)return false;
		if (pos.y > m_maxPos.y)return false;
		
		return true;
	}
	float AABB::Measure(const Vector3& pos) const
	{
		Vector3 leftBottom = { m_minPos.x,m_maxPos.y,m_minPos.z };	// 左下の座標
		Vector3 rightTop = { m_maxPos.x,m_minPos.y,m_minPos.z };	// 右上の座標
		// 点と辺の最短距離を調べる
		float min = Segment_Point_MinLength(m_minPos.ToVECTOR(), rightTop.ToVECTOR(), pos.ToVECTOR());
		float distance = Segment_Point_MinLength(m_maxPos.ToVECTOR(), rightTop.ToVECTOR(), pos.ToVECTOR());
		// 調べた距離が現在の最短距離よりも短ければ更新
		if (min > distance) {
			min = distance;
		}
		// 点と辺の最短距離を調べる
		distance = Segment_Point_MinLength(m_maxPos.ToVECTOR(), leftBottom.ToVECTOR(), pos.ToVECTOR());
		// 調べた距離が現在の最短距離よりも短ければ更新
		if (min > distance) {
			min = distance;
		}
		// 点と辺の最短距離を調べる
		distance = Segment_Point_MinLength(m_minPos.ToVECTOR(), leftBottom.ToVECTOR(), pos.ToVECTOR());
		// 調べた距離が現在の最短距離よりも短ければ更新
		if (min > distance) {
			min = distance;
		}

		// 最短距離を返す
		return min;
	}

	OBB::OBB(const Vector3& center, const Vector3& size) :
		m_centerPos(center),
		m_halfSize(size * 0.5f),
		m_radian(0.0f)
	{
		UpdateDirVector();
	}

	OBB::OBB(const Vector3& center, const Vector3& size, float radian) :
		m_centerPos(center),
		m_halfSize(size * 0.5f),
		m_radian(radian)
	{
		UpdateDirVector();
	}

	bool OBB::CheckCollision(const Shape& other) const
	{
		switch (other.GetType())
		{
		case Type::OBB:
		{
			const OBB* checkBox = dynamic_cast<const OBB*>(&other);

			assert(checkBox);

			// 各軸を用意
			const Vector3 ea1 = m_dirVector[Dir::Width] * m_halfSize.x;
			const Vector3 ea2 = m_dirVector[Dir::Height] * m_halfSize.y;
			const Vector3 eb1 = checkBox->m_dirVector[Dir::Width] * checkBox->m_halfSize.x;
			const Vector3 eb2 = checkBox->m_dirVector[Dir::Height] * checkBox->m_halfSize.y;

			// 2つの距離
			const Vector3 dist = m_centerPos - checkBox->m_centerPos;

			// 分離軸
			Vector3 separateAxis;

			// 投影線分の長さ
			float ra = 0.0f;
			float rb = 0.0f;

			float interval = 0.0f;

			// 分離軸 = ea1
			separateAxis = m_dirVector[Dir::Width];
			ra = m_halfSize.x;
			rb = GetProjectionLength(separateAxis, eb1, eb2);
			interval = std::abs(dist.Dot(separateAxis));
			if (interval >= ra + rb) return false;

			// 分離軸 = ea2
			separateAxis = m_dirVector[Dir::Height];
			ra = m_halfSize.y;
			rb = GetProjectionLength(separateAxis, eb1, eb2);
			interval = std::abs(dist.Dot(separateAxis));
			if (interval >= ra + rb) return false;

			// 分離軸 = eb1
			separateAxis = checkBox->m_dirVector[Dir::Width];
			ra = GetProjectionLength(separateAxis, ea1, ea2);
			rb = checkBox->m_halfSize.x;
			interval = std::abs(dist.Dot(separateAxis));
			if (interval >= ra + rb) return false;

			// 分離軸 = eb2
			separateAxis = checkBox->m_dirVector[Dir::Height];
			ra = GetProjectionLength(separateAxis, ea1, ea2);
			rb = checkBox->m_halfSize.y;
			interval = std::abs(dist.Dot(separateAxis));
			if (interval >= ra + rb) return false;

			break;
		}

		case Type::Circle:
		{
			const Circle* checkCircle = dynamic_cast<const Circle*>(&other);

			assert(checkCircle);

			Vector3 dist;

			// 各軸を調べる
			for (int i = 0; i < 3; i++)
			{
				float len = m_halfSize[i];
				if (len <= 0) continue;

				Vector3 d = checkCircle->GetPosition() - m_centerPos;

				float s = d.Dot(m_dirVector[i]) / len;

				s = std::abs(s);
				if (s > 1)
				{
					dist += m_dirVector[i] * (1 - s) * len;
				}
			}

			if (dist.GetLength() >= checkCircle->GetRadius()) return false;

			break;
		}
		}

		// ここまで来たら当たっている
		return true;
	}

	void OBB::SetRadian(const float radian)
	{
		m_radian = radian;

		UpdateDirVector();
	}

	void OBB::DebugDraw() const
	{
		Vector3 dirLeftTop = Vector3(-m_halfSize.x, -m_halfSize.y, 0.0f);
		Vector3 dirRightTop = Vector3(m_halfSize.x, -m_halfSize.y, 0.0f);
		Vector3 dirLeftBottom = Vector3(-m_halfSize.x, m_halfSize.y, 0.0f);
		Vector3 dirRightBottom = Vector3(m_halfSize.x, m_halfSize.y, 0.0f);

		Vector3 vertices[4];

		vertices[0] = m_centerPos + RotateVector(dirLeftTop);		// 左上
		vertices[1] = m_centerPos + RotateVector(dirRightTop);		// 右上
		vertices[2] = m_centerPos + RotateVector(dirLeftBottom);	// 左下
		vertices[3] = m_centerPos + RotateVector(dirRightBottom);	// 右下

		DrawLine(vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y, Color::kWhite);
		DrawLine(vertices[1].x, vertices[1].y, vertices[3].x, vertices[3].y, Color::kWhite);
		DrawLine(vertices[3].x, vertices[3].y, vertices[2].x, vertices[2].y, Color::kWhite);
		DrawLine(vertices[2].x, vertices[2].y, vertices[0].x, vertices[0].y, Color::kWhite);
	}

	void OBB::UpdateDirVector()
	{
		// 幅用の三角関数の値
		float sinParamWidth = std::sin(m_radian);
		float cosParamWidth = std::cos(m_radian);

		// 高さ用の三角関数の値
		float sinParamHeight = std::sin(m_radian - DX_PI_F * 0.5f);
		float cosParamHeight = std::cos(m_radian - DX_PI_F * 0.5f);

		m_dirVector[Dir::Width] = Vector3(cosParamWidth, sinParamWidth, 0.0f);

		m_dirVector[Dir::Height] = Vector3(cosParamHeight, sinParamHeight, 0.0f);

		m_dirVector[Dir::Depth] = Vector3();
	}

	float OBB::GetProjectionLength(const Vector3& separate, const Vector3& e1, const Vector3& e2) const
	{
		float result = std::abs(separate.Dot(e1)) + std::abs(separate.Dot(e2));

		return result;
	}

	Vector3 OBB::RotateVector(Vector3 vec) const
	{
		Vector3 vector = Vector3();

		float sinParam = std::sin(-m_radian);
		float cosParam = std::cos(-m_radian);

		vector.x = -vec.x * cosParam - vec.y * sinParam;
		vector.y = vec.x * sinParam - vec.y * cosParam;
		vector.z = 0.0f;

		return vector;
	}
	bool Capsule::CheckCollision(const Shape& other) const
	{
		switch (other.GetType())
		{
		case Type::Circle:
		{
			const Circle* check = dynamic_cast<const Circle*>(&other);
			const float distance = Segment_Point_MinLength(m_start.ToVECTOR(), m_end.ToVECTOR(), other.GetPosition().ToVECTOR());
			if (distance <= m_radius + check->GetRadius())return true;
			break;
		}
		case Type::AABB:
		{
			const AABB* check = dynamic_cast<const AABB*>(&other);
			Vector3 rightTop = { check->GetMaxPos().x,check->GetMinPos().y,0 };
			Vector3 leftTop = { check->GetMinPos().x,check->GetMinPos().y,0 };
			Vector3 leftBottom = { check->GetMinPos().x,check->GetMaxPos().y,0 };
			Vector3 rightBottom = { check->GetMaxPos().x,check->GetMaxPos().y,0 };
			float distance = Segment_Segment_MinLength(m_start.ToVECTOR(), m_end.ToVECTOR(), leftTop.ToVECTOR(), rightTop.ToVECTOR());
			if (distance <= m_radius)return true;
			distance = Segment_Segment_MinLength(m_start.ToVECTOR(), m_end.ToVECTOR(), leftTop.ToVECTOR(), leftBottom.ToVECTOR());
			if (distance <= m_radius)return true;
			distance = Segment_Segment_MinLength(m_start.ToVECTOR(), m_end.ToVECTOR(), leftBottom.ToVECTOR(), rightBottom.ToVECTOR());
			if (distance <= m_radius)return true;
			distance = Segment_Segment_MinLength(m_start.ToVECTOR(), m_end.ToVECTOR(), rightBottom.ToVECTOR(), rightTop.ToVECTOR());
			if (distance <= m_radius)return true;
			if (check->CheckPointInAABB(m_start))return true;
			if (check->CheckPointInAABB(m_end))return true;
			break;
		}
			break;
		default:
			break;
		}
		return false;
	}
	void Capsule::DebugDraw() const
	{
		DrawCircle(m_start.x, m_start.y, m_radius, Color::kCyan, TRUE);
		DrawCircle(m_end.x, m_end.y, m_radius, Color::kCyan, TRUE);
	}
}
