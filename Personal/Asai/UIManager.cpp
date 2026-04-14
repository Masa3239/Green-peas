#include "UIManager.h"
#include<memory>

#include<DxLib.h>
#include"../Asai/PlayerUIManager.h"

UIManager::UIManager():
	m_pPlayerUIMgr()
{
}

UIManager::~UIManager()
{
}

void UIManager::Init()
{
	m_pPlayerUIMgr = std::make_unique<PlayerUIManager>();
	m_pPlayerUIMgr->Init();

}

void UIManager::Update()
{

	m_pPlayerUIMgr->Update();

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

}

void UIManager::DebugDraw()
{

	m_pPlayerUIMgr->DebugDraw();

}

void UIManager::End()
{

	m_pPlayerUIMgr->End();

}
