#include "PlayerHpBar.h"
#include"../Asai/PlayerUIBase.h"

#include<DxLib.h>
#include"../../Utility/MyMath.h"

namespace {

	const char* const kGraphHandlePath = "";

}

PlayerHpBar::PlayerHpBar():
	m_graphHandle(-1)
{
}

void PlayerHpBar::Init()
{

	//画像の読み込み予定
	//m_graphHandle = LoadGraph(kGraphHandlePath);

}

void PlayerHpBar::Update()
{
	//HPの割合を計算
	m_rate = MyMath::Rate(m_value, m_max);

}

void PlayerHpBar::Draw()
{

	//描画しない設定なら描画しない
	if (m_isVisible)return;

	//作成予定
	//DrawRectGraph()

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

const PlayerUI::DrawType& PlayerHpBar::GetDrawType() const
{
	return PlayerUI::DrawType::screen;
}
