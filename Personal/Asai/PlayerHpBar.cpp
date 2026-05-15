#include "PlayerHpBar.h"
#include"../Asai/PlayerUIBase.h"

#include<DxLib.h>
#include<string>
#include"../../Utility/MyMath.h"
#include"../../Utility/Game.h"
#include"../Takagi/Player.h"

namespace {

	const char* const kGraphHandlePath = ".\\Resource\\barGreen_horizontalMid.png";
	
	constexpr float kGaugeLeft = Game::kScreenWidth / 2;

	constexpr float kGaugeRight = Game::kScreenWidth - 70;

	constexpr float kGaugeTop = Game::kScreenHeight - 50;

	constexpr float kGaugeBottom = Game::kScreenHeight - 20;

	constexpr float kHpGaugeWidth = (kGaugeRight - 10) - (kGaugeLeft);

}

PlayerHpBar::PlayerHpBar():
	m_font()
{
}

void PlayerHpBar::Init()
{

	//画像の読み込み予定
	m_graphHandle = LoadGraph(kGraphHandlePath);

	m_font = CreateFontToHandle(NULL, 15, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

}

void PlayerHpBar::Update()
{
	
}

void PlayerHpBar::Draw()
{

	//描画しない設定なら描画しない
	if (m_isVisible)return;

	//仮
	DrawBox(kGaugeLeft, kGaugeTop, kGaugeRight, kGaugeBottom, 0xffffff, true);

	//画像の描画
	DrawExtendGraph(kGaugeRight - 10 - (kHpGaugeWidth * m_rate), kGaugeTop, kGaugeRight - 10, kGaugeBottom, m_graphHandle, FALSE);

	//0以上1以下なら1を表示する
	if (m_value < 1 && m_value>0) {
		m_value = 1;
	}

	std::string value = std::to_string(static_cast<int>(m_value));
	std::string max = std::to_string(static_cast<int>(m_max));

	std::string draw = value + "/" + max;

	DrawStringToHandle(kGaugeRight - 80, kGaugeTop + 10, draw.c_str(), 0xffffff, m_font);

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
	DeleteGraph(m_graphHandle);
}

PlayerUI::DrawType PlayerHpBar::GetDrawType() const
{
	return PlayerUI::DrawType::Screen;
}

void PlayerHpBar::SetPlayer(Player* pPlayer)
{

	m_value = pPlayer->GetGaugeCurrentValue(Player::GaugeType::Hp);
	m_max = pPlayer->GetGaugeMaxValue(Player::GaugeType::Hp);
	m_rate = pPlayer->GetGaugeRate(Player::GaugeType::Hp);

}
