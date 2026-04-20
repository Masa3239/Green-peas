#include "HpHealItem.h"
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include "DxLib.h"
#include "../Takagi/Player.h"

namespace {
	
	//画像のサイズ
	constexpr float kGraphScale = 0.1f;

	// 円の当たり判定の半径
	constexpr float kCircleRadius = 50.0f;

	constexpr int kHealValue = 50;
}

HpHealItem::HpHealItem(ObjectManager* objManager):
	ItemBase(objManager)
{
}

HpHealItem::HpHealItem(ObjectManager* objManager,Vector3 position) :
	ItemBase(objManager)
{

	// 座標のリセット
	GetTransform().Reset();

	// 指定された座標を受け取る
	GetTransform().position = position;

	m_collision = Collision::Circle(GetTransform().position, kCircleRadius);
}

HpHealItem::~HpHealItem()
{
	m_pPlayer = nullptr;
	delete m_pPlayer;
}

void HpHealItem::Init()
{
}

void HpHealItem::End()
{
	// 画像の破棄
	DeleteGraph(m_graphHandle);
}

void HpHealItem::Update()
{
	// 中心座標をセット
	m_collision.SetPosition(GetTransform().position);
}

void HpHealItem::Draw()
{

	// 画像の描画
	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y, kGraphScale, 0.0f, m_graphHandle, TRUE);
	// 当たり判定の描画
	m_collision.DebugDraw();
}

void HpHealItem::ItemAbility(Player* player)
{
	m_pPlayer = player;
	m_pPlayer->Heal(kHealValue);
	printfDx("HPが回復しました\n");
}
