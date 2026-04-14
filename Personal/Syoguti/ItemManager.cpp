#include "ItemManager.h"
#include "HpHealItem.h"

#include "DxLib.h"

namespace {

	// 画像のファイルパス
	const char* const kHpHealItemGraphHandlePath = "Personal\\Syoguti\\Resource\\ItemTest1.png";

	// アイテムの個数
	constexpr int kHpHealItems = 10;

}

ItemManager::ItemManager() :
	m_hpHealItemGraphHandle(-1)
{
}

void ItemManager::Init()
{

	// 画像のファイルパスを取得
	m_hpHealItemGraphHandle = LoadGraph(kHpHealItemGraphHandlePath);

	for (int i = 0; i < kHpHealItems; i++) {

		m_items.push_back(std::make_unique<HpHealItem>());
		m_items.back()->SetGraphHandlePath(m_hpHealItemGraphHandle);
		m_items.back()->Init();
	}

}

void ItemManager::End()
{

	for (auto& e : m_items) {
		e->End();
	}
}

void ItemManager::Update()
{
}

void ItemManager::Draw()
{

	for (auto& e : m_items) {
		e->Draw();
	}
}
