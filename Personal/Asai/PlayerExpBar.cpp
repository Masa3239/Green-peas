#include "PlayerExpBar.h"
#include"../Asai/PlayerUIBase.h"

#include<DxLib.h>
#include<string>
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

PlayerExpBar::PlayerExpBar():
	m_level(0),
	m_fontHandle(-1)
{
}

void PlayerExpBar::Init()
{
	//フォントを作成
	m_fontHandle = CreateFontToHandle(NULL, 25, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
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

	std::string level = "Lv." + std::to_string(m_level);

	DrawStringToHandle(kGraphPosLeft+10, kPosY, level.c_str(), 0x000000, m_fontHandle);

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

	m_level = pPlayer->GetLevel();

}
