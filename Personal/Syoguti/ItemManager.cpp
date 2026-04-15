#include "ItemManager.h"
#include "HpHealItem.h"

#include "DxLib.h"

namespace {

	// 画像のファイルパス
	const char* const kHpHealItemGraphHandlePath = "Personal\\Syoguti\\Resource\\ItemTest1.png";

}

ItemManager::ItemManager() :
	m_hpHealItemGraphHandle(-1)
{
}

void ItemManager::Init()
{

	// 画像のファイルパスを取得
	m_hpHealItemGraphHandle = LoadGraph(kHpHealItemGraphHandlePath);
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
	//printfDx("数 : %d\n",m_items.size());

	for (auto& e : m_items) {
		e->Draw();
	}
}

void ItemManager::Create(ItemBase::ItemType type, Vector3 position)
{

	std::unique_ptr<ItemBase> items;
	int graphHandle = -1;

	switch (type)
	{
	case ItemBase::ItemType::Heal:
		items = std::make_unique<HpHealItem>();
		graphHandle = m_hpHealItemGraphHandle;
		break;
	case ItemBase::ItemType::Attack:
		items = std::make_unique<HpHealItem>();
		graphHandle = m_hpHealItemGraphHandle;
		break;
	default:
		break;
	}

	// 画像のグラフハンドルをセット
	items->SetGraphHandle(graphHandle);

	items->Init();
	m_items.push_back(std::move(items));
}

void ItemManager::Remove(int index)
{

	// インデックスの値が配列の範囲内かチェック
	if (index < 0 || index >= m_items.size()) {

		return;
	}

	// 指定したアイテムを削除
	m_items[index]->End();

	// eraseを使うと配列のindex番目の要素を削除しても
	// 自動で後ろにある要素を前詰めされる
	m_items.erase(m_items.begin() + index);
}

void ItemManager::CheckHitCircle(const Collision::Circle other)
{

	// 空きがあれば前詰めする前提の処理
	for (int i = m_items.size() - 1; i >= 0; i--) {

		if (!m_items[i]->GetCollision().CheckCollision(other)) continue;

		Remove(i);
	}
}
