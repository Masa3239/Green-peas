#include "DefenceItem.h"
#include <DxLib.h>
#include "../Chara/Collision.h"
#include "../Takagi/Player.h"
#include "../Takagi/PlayerBuff.h"
#include "../System/SoundManager.h"

namespace {

	//画像のサイズ
	constexpr float kGraphScale = 1.5f;

	// 円の当たり判定の半径
	constexpr float kCircleRadius = 20.0f * kGraphScale;

	// 画像のオフセットYの値
	constexpr float kGraphOffsetY = 10.0f;

	constexpr PlayerStatus kDefenceUp = { 0, 0, 0, 0.5f, 0, 0, 0, 0 };
}

DefenceItem::DefenceItem(ObjectManager* objManager) :
	ItemBase(objManager)
{
}

DefenceItem::DefenceItem(ObjectManager* objManager, Vector3 position) :
	ItemBase(objManager)
{
	GetTransform().position = position;

	m_collision = Collision::Circle(GetTransform().position, kCircleRadius);
}

void DefenceItem::Init()
{
}

void DefenceItem::End()
{
}

void DefenceItem::Update()
{
	m_collision.SetPosition(GetTransform().position);
}

void DefenceItem::Draw()
{
	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y - kGraphOffsetY, kGraphScale, 0.0f, m_graphHandle, TRUE);

#ifdef _DEBUG
	m_collision.SetPosition(GetTransform().position);
#endif
}

void DefenceItem::ItemAbility(Player* player)
{
	m_pPlayer = player;

	PlayerBuff buff = { kDefenceUp, 30, false };
	m_pPlayer->AddBuff(buff);
	SoundManager::GetInstance().PlaySe(Sound::SE::PowerUp);
}
