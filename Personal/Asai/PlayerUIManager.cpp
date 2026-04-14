#include "PlayerUIManager.h"
#include"../Asai/PlayerUIBase.h"
#include<vector>
#include<memory>

#include"../Asai/PlayerHpBar.h"
#include <cassert>

PlayerUIManager::PlayerUIManager():
	m_pUIs()
{
}

void PlayerUIManager::Init()
{
	
	std::unique_ptr<PlayerUIBase> hpBar = std::make_unique<PlayerHpBar>();
	assert(hpBar);
	
	m_pUIs.push_back(std::move(hpBar));

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

		if (UI->GetDrawType() != PlayerUI::DrawType::Screen)continue;

		UI->Draw();

	}

}

void PlayerUIManager::WorldDraw()
{

	for (auto& UI : m_pUIs) {

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
