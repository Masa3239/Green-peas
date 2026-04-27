#include "ChestManager.h"
#include "TreasureChest.h"
#include "../Takagi/WeaponManager.h"
#include "ItemManager.h"
#include <DxLib.h>

namespace {

	constexpr Vector3 kOffsetX = {50.0f, 0.0f, 0.0f};
}

ChestManager::ChestManager() :
	m_pObjectMgr(nullptr),
	m_pWeaponMgr(nullptr),
	m_pItemMgr(nullptr)
{
	for (int i = 0; i < kTreasureChestMotionNum; i++) {

		m_graphHandle[i] = -1;
	}
}

ChestManager::~ChestManager()
{
}

void ChestManager::Init()
{

	LoadDivGraph(".\\Resource\\Chest.png",
		21, 21, 1, 48, 40, m_graphHandle);
}

void ChestManager::End()
{
	for (auto& e : m_chests) {
		e->End();
	}

	for (int i = 0; i < kTreasureChestMotionNum; i++) {

		DeleteGraph(m_graphHandle[i]);
	}
}

void ChestManager::Update()
{

	for (int i = m_chests.size() - 1; i >= 0; i--) {

		m_chests[i]->Update();

		// 開き終わった瞬間に武器生成
		if (m_chests[i]->CanSpawn()) {

			// アイテムを出す位置を決める
			Vector3 posWeapon = m_chests[i]->GetTransform().position + kOffsetX;
			Vector3 posItem = m_chests[i]->GetTransform().position - kOffsetX;
			m_pWeaponMgr->CreateRandom(posWeapon);
			m_pItemMgr->CreateRandom(posItem);

			m_chests[i]->SetSpawned();
			//Remove(i);
		}
	}
}

void ChestManager::Draw()
{
	for (auto& e : m_chests) {

		e->Draw();
	}
}

void ChestManager::Create(Vector3 position)
{

	std::unique_ptr<TreasureChest> chest;
	chest = std::make_unique<TreasureChest>(m_pObjectMgr);
	
	for (int i = 0;i < kTreasureChestMotionNum;i++) {
		chest->SetGraphHandle(m_graphHandle[i], i);
	}
	chest->Init();

	chest->GetTransform().position = position;
	m_chests.push_back(std::move(chest));
}

void ChestManager::Remove(int index)
{

	// インデックスの値が配列の範囲内かチェック
	if (index < 0 || index >= m_chests.size()) {
		return;
	}

	// 指定した宝箱を削除
	m_chests[index]->End();

	m_chests.erase(m_chests.begin() + index);
}

bool ChestManager::CheckHitCollision(const Collision::Shape& other)
{
	// 空きがあれば前詰めする前提の処理
	for (int i = m_chests.size() - 1; i >= 0; i--) {

		// 宝箱のi番目と引数が当たっているかどうか調べる
		if (!m_chests[i]->GetCollision().CheckCollision(other)) continue;

		m_chests[i]->Open();

		// Remove(i);
				
		// 当たっていたらtrueを返す
		return true;
	}
	// 当たっていなければfalseを返す
	return false;
}
