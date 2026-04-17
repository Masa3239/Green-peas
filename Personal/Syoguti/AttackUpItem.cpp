#include "AttackUpItem.h"
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include "DxLib.h"
#include "../Takagi/Player.h"

namespace {

	//画像のサイズ
	constexpr float kGraphScale = 0.1f;

	// 円の当たり判定の半径
	constexpr float kCircleRadius = 50.0f;

	constexpr float kPoewrUpValue = 0.2f;
}

AttackUpItem::AttackUpItem(ObjectManager* objManager):
	ItemBase(objManager)
{
}

AttackUpItem::AttackUpItem(ObjectManager* objManager, Vector3 position):
	ItemBase(objManager)
{

	// 座標のリセット
	m_transform.Reset();

	// 指定された座標を受け取る
	m_transform.position = position;

	m_collision = Collision::Circle(m_transform.position, kCircleRadius);

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
	DeleteGraph(m_graphHandle);
}

void AttackUpItem::Update()
{
	// 中心座標をセット
	m_collision.SetPosition(m_transform.position);
}

void AttackUpItem::Draw()
{
	// 画像の描画
	DrawRotaGraph(m_transform.position.x, m_transform.position.y, kGraphScale, 0.0f, m_graphHandle, TRUE);
	// 当たり判定の描画
	m_collision.DebugDraw();
}

void AttackUpItem::ItemAbility(Player* player)
{
	m_pPlayer = player;
	m_pPlayer->Damage(kPoewrUpValue);
	printfDx("攻撃力が上がりました\n");
}
