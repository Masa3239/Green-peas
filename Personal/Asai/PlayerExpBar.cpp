#include "PlayerExpBar.h"
#include"../Asai/PlayerUIBase.h"

#include<DxLib.h>
#include"../../Utility/Game.h"

#include"../Takagi/Player.h"

namespace {

	const char* const kGraphHandlePath = "";

	constexpr int kCirclePosX = Game::kScreenWidth - 50;

	constexpr int kPosY = Game::kScreenHeight - 50;

	constexpr int kRadius = 40;

	constexpr int kGraphPosLeft = kCirclePosX - kRadius;
	constexpr int kGraphPosRight = kCirclePosX + kRadius;
	constexpr int kGraphPosTop = kPosY - kRadius;
	constexpr int kGraphPosBottom = kPosY + kRadius;

}

PlayerExpBar::PlayerExpBar()
{
}

void PlayerExpBar::Init()
{
}

void PlayerExpBar::Update()
{
}

void PlayerExpBar::Draw()
{

	//描画しない設定なら描画しない
	if (m_isVisible)return;

	//作成予定
	//DrawRectGraph()

	//仮
	DrawCircle(kCirclePosX, kPosY, kRadius, 0xffffff, TRUE);

	float expGaugeHeight = (kGraphPosBottom) - (kGraphPosTop);

	DrawBox(
		kGraphPosLeft,
		kGraphPosBottom - (expGaugeHeight * m_rate),
		kGraphPosRight,
		kGraphPosBottom,
		0x0000ff, FALSE);

}

void PlayerExpBar::DebugDraw()
{
}

void PlayerExpBar::End()
{
}

PlayerUI::DrawType PlayerExpBar::GetDrawType() const
{
	return PlayerUI::DrawType::Screen;
}

void PlayerExpBar::SetPlayer(Player* pPlayer)
{

	m_value = pPlayer->GetGaugeCurrentValue(Player::GaugeType::Exp);
	m_max = pPlayer->GetGaugeMaxValue(Player::GaugeType::Exp);
	m_rate = pPlayer->GetGaugeRate(Player::GaugeType::Exp);

}
