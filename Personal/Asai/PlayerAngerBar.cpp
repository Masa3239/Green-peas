#include "PlayerAngerBar.h"

#include<DxLib.h>
#include"../../Utility/Game.h"
#include"../../Utility/Time.h"
#include"../Takagi/Player.h"

namespace {

    const char* const kGraphHandlePath = ".\\Resource\\barRed_verticalMid.png";

    constexpr float kGaugeLeft = Game::kScreenWidth - 60;

    constexpr float kGaugeRight = Game::kScreenWidth - 30;

    constexpr float kGaugeTop = Game::kScreenHeight / 2;

    constexpr float kGaugeBottom = Game::kScreenHeight - 88;

    constexpr float kAngerGaugeHeight = (kGaugeBottom - 3) - (kGaugeTop);

    constexpr float kBlinkingInterval = 0.2f;

}

PlayerAngerBar::PlayerAngerBar():
    m_isDrawOutSideLine(false),
    m_BbinkingTimer(0)
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

    DrawBox(kGaugeLeft, kGaugeTop, kGaugeRight, kGaugeBottom, 0xffffff, true);

    DrawExtendGraph(kGaugeLeft,
        kGaugeBottom - 3 - (kAngerGaugeHeight * m_rate),
        kGaugeRight,
        kGaugeBottom - 3,
        m_graphHandle, TRUE
    );

    //怒りゲージが溜まっていないならスルー
    if (m_value != m_max)return;

    //タイマーを加算
    m_BbinkingTimer += Time::GetInstance().GetDeltaTime();

    //描画状態のチェック
    if (m_isDrawOutSideLine) {
        //外の枠を表示
        DrawBox(kGaugeLeft - 1, kGaugeTop - 1, kGaugeRight + 1, kGaugeBottom - 1, 0xff0000, false);
    }

    //点滅間隔を超えていないならスルー
    if (m_BbinkingTimer < kBlinkingInterval)return;
    //描画状態を切り替える
    m_isDrawOutSideLine = !m_isDrawOutSideLine;
    //タイマーをリセット
    m_BbinkingTimer = 0;

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
