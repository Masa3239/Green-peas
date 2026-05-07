#include "PlayerWeaponUI.h"
#include"../Asai/PlayerUIBase.h"
#include"../Takagi/Player.h"

#include<DxLib.h>
#include"../../Utility/Color.h"
#include"../../Utility/Game.h"
#include"../../Utility/Vector3.h"

namespace {

	//装備中の武器の表示座標
	constexpr Vector3 kMainWeponPos = { 55.0f,Game::kScreenHeight - 55,0.0f };

	//装備中の武器の大きさ
	constexpr float kMainWeponRadius = 50.0f;

	//装備中の武器の拡大率
	constexpr float kMainWeaponScale = 1.0f;

	//装備していない武器の表示座標
	constexpr Vector3 kSubWeponPos = { kMainWeponPos.x + 75,kMainWeponPos.y + 25,kMainWeponPos.z };

	//装備していない武器の大きさ
	constexpr float kSubWeponRadius = kMainWeponRadius / 2;

	//装備していない武器の拡大率
	constexpr float kSubWeaponScale = 0.5f;

}

PlayerWeaponUI::PlayerWeaponUI() :
	m_weaponGraph(),
	m_weaponScale()
{
}

void PlayerWeaponUI::Init()
{
}

void PlayerWeaponUI::Update()
{
}

void PlayerWeaponUI::Draw()
{
	//枠を描画
	DrawFrame();
	//武器を描画
	DrawWepon();

}

void PlayerWeaponUI::DebugDraw()
{

	printfDx("m_weaponGraph[0] %d\n", m_weaponGraph[0]);
	printfDx("m_weaponGraph[1] %d\n", m_weaponGraph[1]);

	printfDx("m_weaponScale[0] %f\n", m_weaponScale[0]);
	printfDx("m_weaponScale[1] %f\n", m_weaponScale[1]);

}

void PlayerWeaponUI::End()
{
}

PlayerUI::DrawType PlayerWeaponUI::GetDrawType() const
{
	return PlayerUI::DrawType::Screen;
}

void PlayerWeaponUI::SetPlayer(Player* pPlayer)
{

	if (!pPlayer)return;

	auto graph = pPlayer->GetWeaponGraphHandle();

	for (int i = 0;i < kWeaponMaxNum;i++) {

		m_weaponGraph[i] = graph[i];

	}

	auto scale = pPlayer->GetWeaponScale();

	for (int i = 0;i < kWeaponMaxNum;i++) {

		m_weaponScale[i] = scale[i];

	}

}

void PlayerWeaponUI::DrawFrame()
{

	//装備中の武器の枠を描画する
	DrawCircle(kMainWeponPos.x, kMainWeponPos.y, kMainWeponRadius, Color::kWhite, FALSE);
	//装備していない武器の枠を描画する
	DrawCircle(kSubWeponPos.x, kSubWeponPos.y, kSubWeponRadius, Color::kWhite, FALSE);

}

void PlayerWeaponUI::DrawWepon()
{

	if (!m_weaponGraph || !m_weaponScale)return;

	//装備中の武器を描画
	DrawRotaGraph(kMainWeponPos.x, kMainWeponPos.y, m_weaponScale[0] * kMainWeaponScale, 0, m_weaponGraph[0], TRUE);

	//装備していない武器を描画
	DrawRotaGraph(kSubWeponPos.x, kSubWeponPos.y, m_weaponScale[1] * kSubWeaponScale, 0, m_weaponGraph[1], TRUE);

}
