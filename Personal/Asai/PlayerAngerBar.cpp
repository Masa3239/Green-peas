#include "PlayerAngerBar.h"

#include<DxLib.h>
#include"../../Utility/Game.h"

#include"../Takagi/Player.h"

namespace {

    const char* const kGraphHandlePath = ".\\Personal\\Asai\\Graph\\barRed_verticalMid.png";

    constexpr float kGaugeLeft = Game::kScreenWidth - 60;

    constexpr float kGaugeRight = Game::kScreenWidth - 30;

    constexpr float kGaugeTop = Game::kScreenHeight / 2;

    constexpr float kGaugeBottom = Game::kScreenHeight - 93;

}

PlayerAngerBar::PlayerAngerBar()
{
}

void PlayerAngerBar::Init()
{
    //画像の読み込み予定
    m_graphHandle = LoadGraph(kGraphHandlePath);

}

void PlayerAngerBar::Update()
{
}

void PlayerAngerBar::Draw()
{

    //描画しない設定なら描画しない
    if (m_isVisible)return;

    //仮
    DrawBox(kGaugeLeft, kGaugeTop, kGaugeRight, kGaugeBottom, 0xffffff, true);

    float angerGaugeHeight = (kGaugeBottom - 3) - (kGaugeTop + 3);

    DrawExtendGraph(kGaugeLeft,
        kGaugeBottom - 3 - (angerGaugeHeight * m_rate),
        kGaugeRight,
        kGaugeBottom - 3,
        m_graphHandle, TRUE
    );

    //DrawBox(kGaugeLeft,
    //    kGaugeBottom - 3 - (angerGaugeHeight * m_rate),
    //    kGaugeRight,
    //    kGaugeBottom - 3,
    //    0xff0000, TRUE
    //);

}

void PlayerAngerBar::DebugDraw()
{

    printfDx("UI playerAnger %f\n", m_value);
    printfDx("UI playerAngerMax %f\n", m_max);
    printfDx("UI playerAngerRate %f\n", m_rate);

}

void PlayerAngerBar::End()
{
    //画像の破棄
    DeleteGraph(m_graphHandle);
}

PlayerUI::DrawType PlayerAngerBar::GetDrawType() const
{
    return PlayerUI::DrawType::Screen;
}

void PlayerAngerBar::SetPlayer(Player* pPlayer)
{

    m_value = pPlayer->GetGaugeCurrentValue(Player::GaugeType::Anger);
    m_max = pPlayer->GetGaugeMaxValue(Player::GaugeType::Anger);
    m_rate = pPlayer->GetGaugeRate(Player::GaugeType::Anger);

}
