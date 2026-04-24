#include "ChestManager.h"
#include "TreasureChest.h"

#include <DxLib.h>

ChestManager::ChestManager() :
	m_motionCounter(0),
	m_motionFrame(0),
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
	for (auto& e : m_chests) {

		e->Init();
	}

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

	m_motionCounter++;

	if (m_motionCounter >= 5) {
		m_motionCounter = 0;
		m_motionFrame++;

		if (m_motionFrame >= kTreasureChestMotionNum) {
			m_motionFrame = 0;
		}
	}

	for (auto& e : m_chests) {
		e->SetFrame(m_motionFrame);
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

	auto chest = std::make_unique<TreasureChest>(m_pObjectMgr);
	
	for (int i = 0;i < kTreasureChestMotionNum;i++) {
		chest->SetGraphHandle(m_graphHandle[i], i);
	}
	chest->Init();

	chest->GetTransform().position = position;
	m_chests.push_back(std::move(chest));
}
