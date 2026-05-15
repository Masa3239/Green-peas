#include "ItemManager.h"
#include "HpHealItem.h"
#include "AttackUpItem.h"
#include "../Osawa/DefenceItem.h"
#include "../Osawa/WipeOutItem.h"
#include "../../Utility/MyRandom.h"
#include "../Osawa/Enemy/EnemyManager.h"

#include "DxLib.h"

namespace {

	// 画像のファイルパス
	const char* const kHpHealItemGraphHandlePath = ".\\Resource\\Item\\small Potions2.png";
	const char* const kAttackUpItemGraphHandlePath = ".\\Resource\\Item\\small Potions.png";
	const char* const kDefenceUpItemGraphHandlePath = "Resource\\Item\\DifenceUp Potions.png";
	const char* const kWipeOutItemGraphHandlePath = ".\\Resource\\Item\\tile_0105.png";
}

ItemManager::ItemManager() :
	m_hpHealItemGraphHandle(-1),
	m_attackUpItemGraphHandle(-1),
	m_defenceUpItemGraphHandle(-1),
	m_wipeoutItemGraphHandle(-1),
	m_pObjectMgr(nullptr),
	m_pPlayer(nullptr),
	m_pEnemyMgr(nullptr)
{
}

void ItemManager::Init()
{

	// 画像のファイルパスを取得
	m_hpHealItemGraphHandle = LoadGraph(kHpHealItemGraphHandlePath);
	m_attackUpItemGraphHandle = LoadGraph(kAttackUpItemGraphHandlePath);
	m_defenceUpItemGraphHandle = LoadGraph(kDefenceUpItemGraphHandlePath);
	m_wipeoutItemGraphHandle = LoadGraph(kWipeOutItemGraphHandlePath);
}

void ItemManager::End()
{

	for (auto& e : m_items) {
		e->End();
	}

	// 可変長配列を綺麗にする
	m_items.clear();

	DeleteGraph(m_hpHealItemGraphHandle);
	DeleteGraph(m_attackUpItemGraphHandle);
	DeleteGraph(m_defenceUpItemGraphHandle);
	DeleteGraph(m_wipeoutItemGraphHandle);
}

void ItemManager::Update()
{
	for (auto& e : m_items) {
		e->Update();
	}
}

void ItemManager::Draw()
{

	for (auto& e : m_items) {
		e->Draw();
	}
}

void ItemManager::CreateRandom(Vector3 position)
{

	int type = MyRandom::Int(0, static_cast<int>(ItemBase::ItemType::Max) - 1);
	type = static_cast<int>(ItemBase::ItemType::WipeOut);

	Create(static_cast<ItemBase::ItemType>(type), position);

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

		// Defenceなら
	case ItemBase::ItemType::Defence:
		// DefenceItemのコンストラクタを呼んで座標を指定
		items = std::make_unique<DefenceItem>(m_pObjectMgr, position);
		// グラフハンドルを防御力アップアイテムに設定
		graphHandle = m_defenceUpItemGraphHandle;
		break;

		// WipeOutなら
	case ItemBase::ItemType::WipeOut:
		// WipeOutItemのコンストラクタを呼んで座標を指定
		items = std::make_unique<WipeOutItem>(m_pObjectMgr, position, m_pEnemyMgr);
		// グラフハンドルを敵を一層するアイテムに設定
		graphHandle = m_wipeoutItemGraphHandle;
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
	// eraseを使うと配列のindex番目の要素を削除しても
	// 自動で後ろにある要素を前詰めされる
	m_items.erase(m_items.begin() + index);
}

bool ItemManager::CheckHitCollision(const Collision::Shape& other)
{

	// 空きがあれば前詰めする前提の処理
	for (int i = m_items.size() - 1; i >= 0; i--) {

		// アイテムのi番目と引数が当たっているか調べる
		if (!m_items[i]->GetCollision().CheckCollision(other)) continue;

		m_items[i]->ItemAbility(m_pPlayer);

		Remove(i);
		// 当たっていたらtrueを返す
		return true;
	}
	// 当たっていなければfalseを返す
	return false;
}
