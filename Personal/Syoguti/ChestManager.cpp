#include "ChestManager.h"
#include "TreasureChest.h"

#include <DxLib.h>

ChestManager::ChestManager() :
	m_pObjectMgr(nullptr)

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

	for (auto& e : m_chests) {
		e->Update();
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
