#include "WipeOutItem.h"
#include <DxLib.h>
#include "../Chara/Collision.h"
#include "../Takagi/Player.h"
#include "../System/SoundManager.h"

namespace {

	//画像のサイズ
	constexpr float kGraphScale = 1.5f;

	// 円の当たり判定の半径
	constexpr float kCircleRadius = 20.0f * kGraphScale;

	// 画像のオフセットYの値
	constexpr float kGraphOffsetY = 10.0f;

	constexpr int kRatio = 0.5f;
}

WipeOutItem::WipeOutItem(ObjectManager* objManager) :
	ItemBase(objManager)
{
}

WipeOutItem::WipeOutItem(ObjectManager* objManager, Vector3 position) :
	ItemBase(objManager)
{
	GetTransform().position = position;

	m_collision = Collision::Circle(GetTransform().position, kCircleRadius);
}

void WipeOutItem::Init()
{
}

void WipeOutItem::End()
{
}

void WipeOutItem::Update()
{
	m_collision.SetPosition(GetTransform().position);
}

void WipeOutItem::Draw()
{
	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y - kGraphOffsetY, kGraphScale, 0.0f, m_graphHandle, TRUE);

#ifdef _DEBUG
	m_collision.SetPosition(GetTransform().position);
#endif
}

void WipeOutItem::ItemAbility(Player* player)
{
	m_pPlayer = player;



	// プレイヤーの最大体力を取得
	//float value = player->CheckBuffValue().Defence;

	// プレイヤーの最大体力に割合をかけた値を用意
	//value *= kRatio;

	// 回復処理を呼ぶ
	//m_pPlayer->Heal(value);
}
