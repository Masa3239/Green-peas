#include "AttackUpItem.h"
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include "DxLib.h"
#include "../Takagi/Player.h"
#include "../Takagi/PlayerStatus.h"
#include "../Takagi/PlayerBuff.h"

namespace {

	//画像のサイズ
	constexpr float kGraphScale = 1.5f;

	// 円の当たり判定の半径
	constexpr float kCircleRadius = 20.0f * kGraphScale;

	// 画像のオフセットYの値
	constexpr float kGraphOffsetY = 10.0f;

	// constexpr float kPoewrUpValue = 0.2f;
	constexpr PlayerStatus kAtatckUp = { 0,0,0.2f,0,0,0,0,0 };
}

AttackUpItem::AttackUpItem(ObjectManager* objManager):
	ItemBase(objManager)
{
}

AttackUpItem::AttackUpItem(ObjectManager* objManager, Vector3 position):
	ItemBase(objManager)
{

	// 座標のリセット
	GetTransform().Reset();

	// 指定された座標を受け取る
	GetTransform().position = position;

	m_collision = Collision::Circle(GetTransform().position, kCircleRadius);

}

AttackUpItem::~AttackUpItem()
{
	m_pPlayer = nullptr;
	delete m_pPlayer;
}

void AttackUpItem::Init()
{	
}

void AttackUpItem::End()
{
	// 画像の破棄
	// DeleteGraph(m_graphHandle);
}

void AttackUpItem::Update()
{
	// 中心座標をセット
	m_collision.SetPosition(GetTransform().position);
}

void AttackUpItem::Draw()
{
	// 画像の描画
	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y - kGraphOffsetY, kGraphScale, 0.0f, m_graphHandle, TRUE);
	// 当たり判定の描画
	m_collision.DebugDraw();
}

void AttackUpItem::ItemAbility(Player* player)
{
	m_pPlayer = player;
	PlayerBuff buff = { kAtatckUp,30,false };
	m_pPlayer->AddBuff(buff);
	// printfDx("攻撃力が上がりました\n");
}
