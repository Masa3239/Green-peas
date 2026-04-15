#include "PopUpTextManager.h"
#include<memory>
#include<vector>

#include"../Asai/PopUpText.h"

PopUpTextManager::PopUpTextManager():
	m_Texts()
{
}

PopUpTextManager::~PopUpTextManager()
{
}

void PopUpTextManager::Init()
{
}

void PopUpTextManager::Update()
{

	for (auto& text : m_Texts) {

		text->Update();

	}

}

void PopUpTextManager::Draw()
{

	for (auto& text : m_Texts) {

		text->Draw();

	}

}

void PopUpTextManager::DebugDraw()
{

	for (auto& text : m_Texts) {

		text->DebugDraw();

	}

}

void PopUpTextManager::End()
{

	for (auto& text : m_Texts) {

		text->End();

	}

}

void PopUpTextManager::CreateDamageText()
{
}
