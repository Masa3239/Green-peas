#include "PlayerStaminaBar.h"
#include"../Asai/PlayerUIBase.h"
#include"../../Utility/Vector3.h"

#include<DxLib.h>

#include"../Takagi/Player.h"

namespace {

	const char* const kGraphHandlePath = "";

	constexpr Vector3 kOffSet{ 300.0f,0.0f,0.0f };

	constexpr float kSizeX = 50;

	constexpr float kSizeY = 150;

}

PlayerStaminaBar::PlayerStaminaBar():
	m_pos(),
	m_prevValue(0),
	m_isChanged(false)
{
}

PlayerStaminaBar::~PlayerStaminaBar()
{
}

void PlayerStaminaBar::Init()
{
}

void PlayerStaminaBar::Update()
{
	//前のフレームと値が違ったら
	if (m_value != m_prevValue) {
		//変更された
		m_isChanged = true;

	}

}

void PlayerStaminaBar::Draw()
{

	//描画しない設定なら描画しない
	//if (m_isVisible || !m_isChanged)return;

	//作成予定
	//DrawRectGraph()

	//仮
	DrawBox(m_pos.x - kSizeX / 2, m_pos.y - kSizeY / 2, m_pos.x + kSizeX / 2, m_pos.y - kSizeY / 2, 0xffffff, true);

	//float hpGaugeWidth = (kGaugeRight - 10) - (kGaugeLeft + 10);

	//DrawBox(kGaugeRight - 10 - (hpGaugeWidth * m_rate),
	//	kGaugeTop,
	//	kGaugeRight - 10,
	//	kGaugeBottom,
	//	0x00ff00, TRUE
	//);

}

void PlayerStaminaBar::DebugDraw()
{

	printfDx("UI playerStaminaValue %f\n", m_value);
	printfDx("UI playerStaminaMax %f\n", m_max);
	printfDx("UI playerStaminaRate %f\n", m_rate);

	printfDx("vectorX %f\n", m_pos.x);
	printfDx("vectorY %f\n", m_pos.y);
	printfDx("vectorZ %f\n", m_pos.z);

}

void PlayerStaminaBar::End()
{
	//DeleteGraph(m_graphHandle);
}

PlayerUI::DrawType PlayerStaminaBar::GetDrawType() const
{
    return PlayerUI::DrawType::World;
}

void PlayerStaminaBar::SetPlayer(Player* pPlayer)
{

	m_value = pPlayer->GetGaugeCurrentValue(Player::Stamina);
	m_max = pPlayer->GetGaugeMaxValue(Player::Stamina);
	m_rate = pPlayer->GetGaugeRate(Player::Stamina);

	m_pos = pPlayer->GetTransform().position + kOffSet;

}
