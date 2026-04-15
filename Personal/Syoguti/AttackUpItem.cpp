#include "AttackUpItem.h"
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include "DxLib.h"

namespace {

	//画像のサイズ
	constexpr float kGraphScale = 0.1f;

	// 円の当たり判定の半径
	constexpr float kCircleRadius = 50.0f;

}

AttackUpItem::AttackUpItem()
{
}

AttackUpItem::AttackUpItem(Vector3 position)
{

	// 座標のリセット
	m_transform.Reset();

	// 指定された座標を受け取る
	m_transform.position = position;

	m_collision = Collision::Circle(m_transform.position, kCircleRadius);
}

void AttackUpItem::Init()
{
	// 中心座標をセット
	m_collision.SetPosition(m_transform.position);
}

void AttackUpItem::End()
{
	// 画像の破棄
	DeleteGraph(m_graphHandle);
}

void AttackUpItem::Update()
{
}

void AttackUpItem::Draw()
{
	// 画像の描画
	DrawRotaGraph(m_transform.position.x, m_transform.position.y, kGraphScale, 0.0f, m_graphHandle, TRUE);
	// 当たり判定の描画
	m_collision.DebugDraw();
}
