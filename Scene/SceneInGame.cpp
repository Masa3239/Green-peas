#include "SceneInGame.h"
#include <DxLib.h>
#include "../Personal/Asai/Camera.h"
#include "../Personal/Asai/UIManager.h"
#include "../Personal/Kimura/Map/Map.h"
#include "../Personal/Osawa/Enemy/EnemyManager.h"
#include "../Personal/Syoguti/ItemManager.h"
#include "../Personal/Takagi/Player.h"
#include "../System/ObjectManager.h"

#include "../Personal/Osawa/Scene/SceneSelection.h"
#include "../Personal/Osawa/Scene/SceneTempResult.h"

namespace {

	constexpr Vector3 kTestHealPos = { 100.0f, 300.0f, 0.0f };
	constexpr Vector3 kTestAttackPos = { 500.0f, 300.0f, 0.0f };
}

SceneInGame::SceneInGame() :
	m_pPlayer(nullptr),
	m_pCamera(nullptr),
	m_pEnemyMgr(nullptr),
	m_pUIMgr(nullptr),
	m_pItemMgr(nullptr),
	m_pMap(nullptr)
{
	m_pPlayer = std::make_unique<Player>(GetObjectManager());
	m_pCamera = std::make_unique<Camera>();
	m_pEnemyMgr = std::make_unique<EnemyManager>(GetObjectManager());
	m_pUIMgr = std::make_unique<UIManager>();
	m_pItemMgr = std::make_unique<ItemManager>();
	m_pMap = std::make_unique<Map>();
}

SceneInGame::~SceneInGame()
{
}

void SceneInGame::Init()
{
	m_pPlayer->Init();
	m_pPlayer->SetCamera(m_pCamera.get());
	m_pPlayer->SetEnemyManager(m_pEnemyMgr.get());
	m_pPlayer->SetItemManager(m_pItemMgr.get());

	m_pCamera->Init();

	m_pEnemyMgr->Init();
	m_pEnemyMgr->SetPlayer(m_pPlayer.get());
	m_pEnemyMgr->SetUIManager(m_pUIMgr.get());

	m_pUIMgr->Init();

	m_pItemMgr->Init();
	m_pItemMgr->SetObjectManager(GetObjectManager());

	m_pMap->Init();

	// α版用
	m_pItemMgr->Create(ItemBase::ItemType::Heal, kTestHealPos);
	m_pItemMgr->Create(ItemBase::ItemType::Attack, kTestAttackPos);
}

void SceneInGame::End()
{
	m_pMap->End();
	m_pItemMgr->End();
	m_pUIMgr->End();
	m_pEnemyMgr->End();
	m_pCamera->End();
	m_pPlayer->End();
}

SceneBase* SceneInGame::Update()
{
	m_pUIMgr->SetPlayer(m_pPlayer.get());

	m_pEnemyMgr->Update();

	m_pPlayer->Update();

	m_pUIMgr->Update();

	m_pItemMgr->Update();

	m_pMap->Update();

	// プレイヤーが死亡していたら
	if (m_pPlayer->IsDead())
	{
		// 仮でシーン選択画面へ戻す
		return new SceneTempResult("GAME OVER");
	}

	if (m_pEnemyMgr->GetDefeatedNum() >= 100)
	{
		return new SceneTempResult("GAME CLEAR");
	}

	return this;
}

void SceneInGame::Draw()
{
	m_pItemMgr->Draw();
}

void SceneInGame::PreDraw()
{
	SetDrawScreen(m_pCamera->GetWorldScreen());
	ClearDrawScreen();

	m_pMap->Draw();
}

void SceneInGame::PostDraw()
{
	m_pUIMgr->WorldDraw();

	SetDrawScreen(DX_SCREEN_BACK);
	m_pCamera->Draw();

	m_pUIMgr->ScreenDraw();
	m_pUIMgr->DebugDraw();

	DrawString(200, 200, "倒した数", 0xffffff);
	DrawString(280, 200, std::to_string(m_pEnemyMgr->GetDefeatedNum()).c_str(), 0xffffff);
}
