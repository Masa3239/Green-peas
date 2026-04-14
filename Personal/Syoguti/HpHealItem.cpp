#include "HpHealItem.h"

#include "DxLib.h"

HpHealItem::HpHealItem()
{
}

void HpHealItem::Init()
{

	GetGraphSize(m_graphHandle, &m_sizeX, &m_sizeY);

	float scaleX = 64.0f / m_sizeX;
	float scaleY = 64.0f / m_sizeY;
	
	m_scale = (scaleX < scaleY) ? scaleX : scaleY;
}

void HpHealItem::End()
{
	DeleteGraph(m_graphHandle);
}

void HpHealItem::Update()
{
}

void HpHealItem::Draw()
{
	DrawRotaGraph(m_posX, m_posY, m_scale, 0.0f, m_graphHandle, TRUE);
}
