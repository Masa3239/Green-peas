#include "UIManager.h"
#include<memory>

#include<DxLib.h>
#include"../Asai/PlayerUIManager.h"
#include"../Asai/PopUpTextManager.h"

#include"../Takagi/Player.h"

UIManager::UIManager():
	m_pPlayerUIMgr(),
	m_pPopUpTextMgr()
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

}

void UIManager::Update()
{

	m_pPlayerUIMgr->Update();

	m_pPopUpTextMgr->Update();

}

void UIManager::Draw()
{
}

void UIManager::ScreenDraw()
{

	m_pPlayerUIMgr->ScreenDraw();

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

}

void UIManager::SetPlayer(Player* pPlayer)
{

	m_pPlayerUIMgr->SetPlayer(pPlayer);

}

void UIManager::CreateDamagePopUpText(Vector3 pos, int amount)
{

	m_pPopUpTextMgr->CreateText(pos, amount, PopUpText::Type::Damage);

}
