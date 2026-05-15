#include "PlayerUIManager.h"
#include"../Asai/PlayerUIBase.h"
#include<vector>
#include<memory>

#include"../Asai/PlayerAngerBar.h"
#include"../Asai/PlayerExpBar.h"
#include"../Asai/PlayerHpBar.h"
#include"../Asai/PlayerStaminaBar.h"
#include"../Asai/PlayerWeaponUI.h"

PlayerUIManager::PlayerUIManager():
	m_pUIs()
{
}

void PlayerUIManager::Init()
{
	//HPのUIを追加
	m_pUIs.emplace_back(std::make_unique<PlayerHpBar>());

	//怒りゲージのUIを追加
	m_pUIs.emplace_back(std::make_unique<PlayerAngerBar>());

	//スタミナゲージのUIを追加
	m_pUIs.emplace_back(std::make_unique<PlayerStaminaBar>());

	//経験ゲージのUIを追加
	m_pUIs.emplace_back(std::make_unique<PlayerExpBar>());

	//武器のUIを追加
	m_pUIs.emplace_back(std::make_unique<PlayerWeaponUI>());

	//全ての要素を初期化
	for (auto& UI : m_pUIs) {

		UI->Init();

	}

}

void PlayerUIManager::Update()
{

	for (auto& UI : m_pUIs) {

		UI->Update();

	}

}

void PlayerUIManager::ScreenDraw()
{

	for (auto& UI : m_pUIs) {
		//PlayerUI::DrawType::Screen以外ならスルー
		if (UI->GetDrawType() != PlayerUI::DrawType::Screen)continue;

		UI->Draw();

	}

}

void PlayerUIManager::WorldDraw()
{

	for (auto& UI : m_pUIs) {
		//PlayerUI::DrawType::World以外ならスルー
		if (UI->GetDrawType() != PlayerUI::DrawType::World)continue;

		UI->Draw();

	}

}

void PlayerUIManager::DebugDraw()
{

	for (auto& UI : m_pUIs) {

		UI->DebugDraw();

	}

}

void PlayerUIManager::End()
{

	for (auto& UI : m_pUIs) {

		UI->End();

	}

}

void PlayerUIManager::SetPlayer(Player* pPlayer)
{

	for (auto& UI : m_pUIs) {

		UI->SetPlayer(pPlayer);

	}

}
