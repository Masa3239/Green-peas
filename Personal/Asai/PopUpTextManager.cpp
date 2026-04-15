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

	m_textFonts.resize(200);

	m_textFonts.resize(static_cast<int>(PopUpText::Type::Max));

	m_textFonts[static_cast<int>(PopUpText::Type::Damage)] = CreateFontToHandle(NULL, 40, 3);

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

void PopUpTextManager::CreateText(Vector3 position, int amount, PopUpText::Type type)
{

	auto text = std::make_unique<PopUpText>();
	text->Init();
	text->SetPos(position);
	text->SetData(amount, m_textFonts[static_cast<int>(type)], type);

	m_pTexts.push_back(std::move(text));

}
