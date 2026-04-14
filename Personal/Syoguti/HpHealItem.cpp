#include "HpHealItem.h"
#include "../../Chara/Collision.h"
#include "DxLib.h"

namespace {
	
	//画像のサイズ
	constexpr float kGraphScale = 0.1f;

	constexpr float kCircleRadius = 50.0f;
}

HpHealItem::HpHealItem()
{
	m_collision = Collision::Circle(m_transform.position, kCircleRadius);
}

void HpHealItem::Init()
{

	// 画像の位置(仮)
	m_transform.position.x = 100.0f;
	m_transform.position.y = 100.0f;
	// 中心座標をセット
	m_collision.SetPosition(m_transform.position);
}

void HpHealItem::End()
{
	// 画像の破棄
	DeleteGraph(m_graphHandle);
}

void HpHealItem::Update()
{

	
}

void HpHealItem::Draw()
{

	// 画像の描画
	DrawRotaGraph(m_transform.position.x, m_transform.position.y, kGraphScale, 0.0f, m_graphHandle, TRUE);
	// 当たり判定の描画
	m_collision.DebugDraw();
}
