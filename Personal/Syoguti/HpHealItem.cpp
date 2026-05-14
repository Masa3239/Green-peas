#include "HpHealItem.h"
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include "DxLib.h"
#include "../Takagi/Player.h"
#include "../../System/SoundManager.h"

namespace {
	
	//画像のサイズ
	constexpr float kGraphScale = 1.5f;

	// 円の当たり判定の半径
	constexpr float kCircleRadius = 20.0f * kGraphScale;

	// 画像のオフセットYの値
	constexpr float kGraphOffsetY = 10.0f;

	// 体力回復に使う割合
	constexpr int kRatio = 0.5f;
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
}

void HpHealItem::Update()
{
	// 中心座標をセット
	m_collision.SetPosition(GetTransform().position);
}

void HpHealItem::Draw()
{

	// 画像の描画
	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y - kGraphOffsetY, kGraphScale, 0.0f, m_graphHandle, TRUE);
	// 当たり判定の描画
	m_collision.DebugDraw();
}

void HpHealItem::ItemAbility(Player* player)
{
	m_pPlayer = player;

	// プレイヤーの最大体力を取得
	float healValue = player->GetGaugeMaxValue(Player::GaugeType::Hp);

	// プレイヤーの最大体力に割合をかけた値を用意
	healValue *= kRatio;

	// 回復処理を呼ぶ
	m_pPlayer->Heal(healValue);
	SoundManager::GetInstance().PlaySe(Sound::SE::Heal);
	
}
