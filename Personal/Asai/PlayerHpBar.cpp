#include "PlayerHpBar.h"
#include"../Asai/PlayerUIBase.h"

#include<DxLib.h>
#include"../../Utility/MyMath.h"
#include"../../Utility/Game.h"

#include"../Takagi/Player.h"

namespace {

	const char* const kGraphHandlePath = "";
	
	constexpr float kGaugeLeft = Game::kScreenWidth / 2;

	constexpr float kGaugeRight = Game::kScreenWidth - 70;

	constexpr float kGaugeTop = Game::kScreenHeight - 50;

	constexpr float kGaugeBottom = Game::kScreenHeight - 20;

}

PlayerHpBar::PlayerHpBar()
{
}

void PlayerHpBar::Init()
{

	//画像の読み込み予定
	//m_graphHandle = LoadGraph(kGraphHandlePath);

}

void PlayerHpBar::Update()
{

}

void PlayerHpBar::Draw()
{

	//描画しない設定なら描画しない
	if (m_isVisible)return;

	//作成予定
	//DrawRectGraph()

	//仮
	DrawBox(kGaugeLeft, kGaugeTop, kGaugeRight, kGaugeBottom, 0xffffff, true);

	float hpGaugeWidth = (kGaugeRight - 10) - (kGaugeLeft + 10);

	DrawBox(kGaugeRight - 10 - (hpGaugeWidth * m_rate),
		kGaugeTop,
		kGaugeRight - 10,
		kGaugeBottom,
		0x00ff00, TRUE
	);


	float max = kGaugeLeft + 10;

	//DrawBox(
	//	max * m_rate,
	//	kGaugeTop,
	//	kGaugeRight - 10,
	//	kGaugeBottom, 0x00ff00, true);

}

void PlayerHpBar::DebugDraw()
{

	printfDx("UI playerHP %f\n", m_value);
	printfDx("UI playerHPMax %f\n", m_max);
	printfDx("UI playerHPRate %f\n", m_rate);

}

void PlayerHpBar::End()
{
	//画像の破棄
	//DeleteGraph(m_graphHandle);
}

PlayerUI::DrawType PlayerHpBar::GetDrawType() const
{
	return PlayerUI::DrawType::Screen;
}

void PlayerHpBar::SetPlayer(Player* pPlayer)
{

	m_value = pPlayer->GetGaugeCurrentValue(Player::Hp);
	m_max = pPlayer->GetGaugeMaxValue(Player::Hp);
	m_rate = pPlayer->GetGaugeRate(Player::Hp);

}
