#include "HpHealItem.h"

#include "DxLib.h"

HpHealItem::HpHealItem()
{
}

void HpHealItem::Init()
{

	// 画像サイズの取得
	GetGraphSize(m_graphHandle, &m_sizeX, &m_sizeY);

	// 画像のスケール
	float scaleX = 64.0f / m_sizeX;
	float scaleY = 64.0f / m_sizeY;
	
	// 画像のスケールを小さい方に合わせる
	m_scale = (scaleX < scaleY) ? scaleX : scaleY;
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

	// 画像の位置(仮)
	m_posX = 100.0f;
	m_posY = 100.0f;

	// 画像の描画
	DrawRotaGraph(m_posX, m_posY, m_scale, 0.0f, m_graphHandle, TRUE);
}
