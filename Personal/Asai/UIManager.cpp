#include "UIManager.h"
#include<memory>
#include"../Asai/PlayerUIManager.h"
#include"../Asai/PopUpTextManager.h"
#include"../Asai/Combo.h"
#include"../Asai/Minimap.h"

#include<DxLib.h>
#include"../Takagi/Player.h"

UIManager::UIManager():
	m_pPlayerUIMgr(nullptr),
	m_pPopUpTextMgr(nullptr),
	m_pCombo(nullptr),
	m_pMinimap(nullptr),
	m_pPlayer(nullptr),
	m_pEnemyManager(nullptr)
{
}

UIManager::~UIManager()
{
}

void UIManager::Init()
{
	m_pPlayerUIMgr = std::make_unique<PlayerUIManager>();
	m_pPlayerUIMgr->Init();

	m_pPopUpTextMgr = std::make_unique<PopUpTextManager>();
	m_pPopUpTextMgr->Init();

	m_pCombo = std::make_unique<Combo>();
	m_pCombo->Init();

	m_pMinimap = std::make_unique<Minimap>();
	m_pMinimap->Init();

}

void UIManager::Update()
{

	m_pPlayerUIMgr->SetPlayer(m_pPlayer);
	m_pPlayerUIMgr->Update();

	m_pPopUpTextMgr->Update();

	m_pCombo->Update();

	m_pMinimap->Update();

}

void UIManager::Draw()
{
}

void UIManager::ScreenDraw()
{

	m_pPlayerUIMgr->ScreenDraw();

	m_pCombo->Draw();

	m_pMinimap->Draw();

}

void UIManager::WorldDraw()
{

	m_pPlayerUIMgr->WorldDraw();

	m_pPopUpTextMgr->Draw();

}

void UIManager::DebugDraw()
{

	m_pPlayerUIMgr->DebugDraw();

	m_pPopUpTextMgr->DebugDraw();

}

void UIManager::End()
{

	m_pPlayerUIMgr->End();
	m_pPopUpTextMgr->End();
	m_pCombo->End();
	m_pMinimap->End();

}

void UIManager::GenerateMinimap(Camera* pCamera, Map* pMap)
{

	m_pMinimap->GenerateMinimap(pCamera, pMap);

}

void UIManager::SetPlayer(Player* pPlayer)
{

	m_pPlayer = pPlayer;

	m_pMinimap->SetPlayer(pPlayer);

}

void UIManager::SetEnemyManager(EnemyManager* pEnemyManager)
{
	//セット
	m_pEnemyManager = pEnemyManager;

	m_pCombo->SetEnemyManager(m_pEnemyManager);

	m_pMinimap->SetEnemyManager(m_pEnemyManager);

}

void UIManager::SetItemManager(ItemManager* pItemManager)
{

	m_pMinimap->SetItemManager(pItemManager);

}

void UIManager::CreatePopUpText(Vector3 pos, int amount, PopUpUI::TextType type)
{

	m_pPopUpTextMgr->CreateText(pos, amount, type);

}
