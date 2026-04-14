#include "PlayerHpBar.h"
#include"../Asai/PlayerUIBase.h"

#include<DxLib.h>
#include"../../Utility/MyMath.h"
#include"../../Utility/Transform.h"

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
	CalculateRate();

}

void PlayerHpBar::Draw()
{

	//描画しない設定なら描画しない
	if (m_isVisible)return;

	//作成予定
	//DrawRectGraph()

	DrawBox(100, 100, 200, 200, 0xff0000, true);

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
