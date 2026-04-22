#include "PlayerStaminaBar.h"
#include"../Asai/PlayerUIBase.h"
#include"../../Utility/Vector3.h"

#include<DxLib.h>

#include"../Takagi/Player.h"

namespace {

	const char* const kGraphHandlePath = ".\\Personal\\Asai\\Graph\\barYellow_verticalMid.png";

	constexpr Vector3 kOffSet{ 50.0f,-10.0f,0.0f };

	constexpr float kSizeX = 12;

	constexpr float kSizeY = 50;

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
	//画像の読み込み
	m_graphHandle = LoadGraph(kGraphHandlePath);
}

void PlayerStaminaBar::Update()
{
	//前のフレームと値が違ったら
	if (m_value != m_prevValue) {
		//変更された
		m_isChanged = true;

	}
	else {
		//変更されていない
		m_isChanged = false;

	}

	//更新
	m_prevValue = m_value;

}

void PlayerStaminaBar::Draw()
{

	//描画しない設定なら描画しない
	if (m_isVisible || !m_isChanged)return;

	//作成予定
	//DrawRectGraph()

	//仮
	DrawBox(m_pos.x - kSizeX / 2, m_pos.y - kSizeY / 2, m_pos.x + kSizeX / 2, m_pos.y + kSizeY / 2, 0xffffff, true);

	float staminaGaugeHeight = (m_pos.y + kSizeY / 2) - (m_pos.y - kSizeY / 2);

	DrawExtendGraph(
		m_pos.x - kSizeX / 2,
		m_pos.y + kSizeY / 2 - (staminaGaugeHeight * m_rate),
		m_pos.x + kSizeX / 2,
		m_pos.y + kSizeY / 2,
		m_graphHandle, TRUE);

	//DrawBox(
	//	m_pos.x - kSizeX / 2,
	//	m_pos.y + kSizeY / 2 - (staminaGaugeHeight * m_rate),
	//	m_pos.x + kSizeX / 2,
	//	m_pos.y + kSizeY / 2,
	//	0xffff00, TRUE);

}

void PlayerStaminaBar::DebugDraw()
{

	printfDx("UI playerStaminaValue %f\n", m_value);
	printfDx("UI playerStaminaprevValue %f\n", m_prevValue);
	//printfDx("UI playerStaminaMax %f\n", m_max);
	//printfDx("UI playerStaminaRate %f\n", m_rate);

	printfDx("%d\n", m_isVisible);
	printfDx("%d\n", m_isChanged);

}

void PlayerStaminaBar::End()
{
	//画像の破棄
	DeleteGraph(m_graphHandle);
}

PlayerUI::DrawType PlayerStaminaBar::GetDrawType() const
{
    return PlayerUI::DrawType::World;
}

void PlayerStaminaBar::SetPlayer(Player* pPlayer)
{

	m_value = pPlayer->GetGaugeCurrentValue(Player::GaugeType::Stamina);
	m_max = pPlayer->GetGaugeMaxValue(Player::GaugeType::Stamina);
	m_rate = pPlayer->GetGaugeRate(Player::GaugeType::Stamina);

	m_pos = pPlayer->GetTransform().position + kOffSet;

}
