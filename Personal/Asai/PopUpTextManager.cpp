#include "PopUpTextManager.h"
#include<memory>
#include<vector>
#include"../../Utility/Vector3.h"

#include"../Asai/PopUpText.h"

PopUpTextManager::PopUpTextManager():
	m_pTexts(),
	m_textFonts()
{
}

PopUpTextManager::~PopUpTextManager()
{
}

void PopUpTextManager::Init()
{

	m_pTexts.resize(200);

	m_textFonts.resize(static_cast<int>(PopUpUI::TextType::Max));
	
	m_textFonts[static_cast<int>(PopUpUI::TextType::Damage)] = CreateFontToHandle(NULL, 40, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	//m_textFonts[static_cast<int>(PopUpUI::TextType::Critical)] = CreateFontToHandle(NULL, 40, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	m_textFonts[static_cast<int>(PopUpUI::TextType::Critical)] = CreateFontToHandle("VT323 - Regular", 50, 6, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	m_textFonts[static_cast<int>(PopUpUI::TextType::Heal)] = CreateFontToHandle(NULL, 40, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	for (int i = 0;i < m_pTexts.size();i++) {

		auto text = std::make_unique<PopUpText>();

		m_pTexts[i] = std::move(text);

	}

}

void PopUpTextManager::Update()
{

	for (auto& text : m_pTexts) {

		if (!text->GetIsActive())continue;

		text->Update();

	}

}

void PopUpTextManager::Draw()
{

	for (auto& text : m_pTexts) {

		if (!text->GetIsActive())continue;

		text->Draw();

	}

}

void PopUpTextManager::DebugDraw()
{

	printfDx("m_texts size %d\n", m_pTexts.size());

	int activeNum = 0;

	for (auto& text : m_pTexts) {

		if(!text->GetIsActive())continue;

		activeNum++;

	}

	printfDx("m_texts activeNum%d\n", activeNum);

	for (auto& text : m_pTexts) {

		if (!text->GetIsActive())continue;

		text->DebugDraw();

	}

}

void PopUpTextManager::End()
{

	for (auto& text : m_pTexts) {

		text->End();

	}

}

void PopUpTextManager::CreateText(Vector3 position, int amount, PopUpUI::TextType type)
{

	for (auto& text : m_pTexts) {

		if (text->GetIsActive())continue;

		text->Init();
		text->SetPos(position);
		text->SetData(amount, m_textFonts[static_cast<int>(type)], type);

		return;

	}

}
