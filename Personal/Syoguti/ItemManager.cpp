#include "ItemManager.h"
#include "HpHealItem.h"
#include "AttackUpItem.h"

#include "DxLib.h"

namespace {

	// 画像のファイルパス
	const char* const kHpHealItemGraphHandlePath = ".\\Resource\\ItemTest1.png";
	const char* const kAttackUpItemGraphHandlePath = ".\\Resource\\ItemTest2.png";
}

ItemManager::ItemManager() :
	m_hpHealItemGraphHandle(-1),
	m_attackUpItemGraphHandle(-1),
	m_pObjectMgr(nullptr),
	m_pPlayer(nullptr)
{
}

void ItemManager::Init()
{

	// 画像のファイルパスを取得
	m_hpHealItemGraphHandle = LoadGraph(kHpHealItemGraphHandlePath);
	m_attackUpItemGraphHandle = LoadGraph(kAttackUpItemGraphHandlePath);
}

void ItemManager::End()
{

	for (auto& e : m_items) {
		e->End();
	}

	// 可変長配列を綺麗にする
	m_items.clear();
}

void ItemManager::Update()
{
	for (auto& e : m_items) {
		e->Update();
	}
}

void ItemManager::Draw()
{
	// printfDx("数 : %d\n",m_items.size());

	for (auto& e : m_items) {
		e->Draw();
	}
}

void ItemManager::Create(ItemBase::ItemType type, Vector3 position)
{

	std::unique_ptr<ItemBase> items;
	int graphHandle = -1;

	// 引数でもらったItemTypeを調べる
	switch (type)
	{

		// Healなら
	case ItemBase::ItemType::Heal:
		// HpHealItemのコンストラクタを呼んで座標を指定
		items = std::make_unique<HpHealItem>( m_pObjectMgr, position);
		// グラフハンドルを回復アイテムの画像に設定
		graphHandle = m_hpHealItemGraphHandle;
		break;

		// Attackなら
	case ItemBase::ItemType::Attack:
		// AttackUpItemのコンストラクタを呼んで座標を指定
		items = std::make_unique<AttackUpItem>(m_pObjectMgr, position);
		// グラフハンドルを攻撃力アップアイテムに設定
		graphHandle = m_attackUpItemGraphHandle;
		break;

	default:
		printfDx("エラー\n");
		break;
	}

	// itemsまたはgraphHandeの値がおかしかったらreturn
	if (!items || graphHandle == -1) return;

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

void ItemManager::CheckHitCollision(const Collision::Shape& other)
{

	// 空きがあれば前詰めする前提の処理
	for (int i = m_items.size() - 1; i >= 0; i--) {

		// アイテムのi番目と引数が当たっているか調べる
		if (!m_items[i]->GetCollision().CheckCollision(other)) continue;

		m_items[i]->ItemAbility(m_pPlayer);

		Remove(i);
		return;
	}
}
