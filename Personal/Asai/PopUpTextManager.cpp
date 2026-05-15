#include "PopUpTextManager.h"
#include<memory>
#include<vector>
#include"../../Utility/Vector3.h"

#include"../Asai/PopUpText.h"
#include"../../Utility/MyRandom.h"

namespace {
	//生成位置の最大オフセット
	constexpr int kCreatePosMaxMargin = 50;
	//ラジアン角
	constexpr float kRadianMax = MyMath::DegToRad(360);

}

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

	m_pTexts.resize(600);

	//フォントを作成
	m_textFonts.resize(static_cast<int>(PopUpUI::TextType::Max));
	m_textFonts[static_cast<int>(PopUpUI::TextType::Damage)] = CreateFontToHandle(NULL, 40, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	m_textFonts[static_cast<int>(PopUpUI::TextType::Critical)] = CreateFontToHandle("VT323 - Regular", 50, 6, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	m_textFonts[static_cast<int>(PopUpUI::TextType::Heal)] = CreateFontToHandle(NULL, 40, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	for (int i = 0;i < m_pTexts.size();i++) {
		//テキストを作成
		auto text = std::make_unique<PopUpText>();
		//配列に格納
		m_pTexts[i] = std::move(text);

	}

}

void PopUpTextManager::Update()
{

	for (auto& text : m_pTexts) {
		//非アクティブならスルー
		if (!text->GetIsActive())continue;

		text->Update();

	}

}

void PopUpTextManager::Draw()
{

	for (auto& text : m_pTexts) {
		//非アクティブならスルー
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

	for (auto& font : m_textFonts) {

		DeleteFontToHandle(font);

	}

}

void PopUpTextManager::CreateText(Vector3 position, int amount, PopUpUI::TextType type)
{

	//最大オフセットからどれくらいずらすか
	float rate = MyRandom::Float01();
	//生成位置の角度をランダムで決める
	float spawnRadian = MyRandom::Float(0, kRadianMax);

	//生成位置のオフセット
	Vector3 offSetPos{

		sinf(spawnRadian) * kCreatePosMaxMargin * rate,
		cosf(spawnRadian) * kCreatePosMaxMargin * rate,
		0
	};

	for (auto& text : m_pTexts) {

		//アクティブ状態ならスルー
		if (text->GetIsActive())continue;

		//生成
		text->Init();
		text->SetPos(position + offSetPos);
		text->SetData(amount, m_textFonts[static_cast<int>(type)], type);

		return;

	}

	//ここまできたら全てのテキストが使われている
	
	//新しく作成する
	auto newText = std::make_unique<PopUpText>();

	//生成
	newText->Init();
	newText->SetPos(position + offSetPos);
	newText->SetData(amount, m_textFonts[static_cast<int>(type)], type);

	//配列に追加
	m_pTexts.push_back(std::move(newText));

}
