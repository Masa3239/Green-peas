#include "SceneTestOsawa.h"
#include <DxLib.h>
#include "../Personal/Asai/Camera.h"
#include "../Personal/Asai/UIManager.h"
#include "../Personal/Kimura/Map/Map.h"
#include "../Personal/Osawa/Enemy/EnemyManager.h"
#include "../Personal/Syoguti/ItemManager.h"
#include "../Personal/Takagi/Player.h"
#include "../System/ObjectManager.h"

#include "../Personal/Osawa/Scene/SceneSelection.h"

SceneTestOsawa::SceneTestOsawa() :
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

SceneTestOsawa::~SceneTestOsawa()
{
}

void SceneTestOsawa::Init()
{
	m_pPlayer->Init();
	m_pPlayer->SetCamera(m_pCamera.get());
	m_pPlayer->SetEnemyManager(m_pEnemyMgr.get());
	m_pPlayer->SetItemManager(m_pItemMgr.get());

	m_pCamera->Init();
	m_pCamera->SetMap(m_pMap.get());

	m_pEnemyMgr->Init();
	m_pEnemyMgr->SetPlayer(m_pPlayer.get());
	m_pEnemyMgr->SetUIManager(m_pUIMgr.get());

	m_pUIMgr->Init();

	m_pItemMgr->Init();
	m_pItemMgr->SetObjectManager(GetObjectManager());
	m_pItemMgr->SetPlayer(m_pPlayer.get());

	m_pMap->Init();

	m_pCamera->GenerateWorldScreen();
}

void SceneTestOsawa::End()
{
	m_pMap->End();
	m_pItemMgr->End();
	m_pUIMgr->End();
	m_pEnemyMgr->End();
	m_pCamera->End();
	m_pPlayer->End();
}

SceneBase* SceneTestOsawa::Update()
{
	m_pUIMgr->SetPlayer(m_pPlayer.get());

	m_pEnemyMgr->Update();

	m_pUIMgr->Update();

	m_pItemMgr->Update();

	m_pMap->Update();

	return this;
}

void SceneTestOsawa::Draw()
{
	m_pItemMgr->Draw();
}

void SceneTestOsawa::PreDraw()
{
	printfDx("SceneTestOsawa\n");

	SetDrawScreen(m_pCamera->GetWorldScreen());
	ClearDrawScreen();

	m_pMap->Draw();
}

void SceneTestOsawa::PostDraw()
{
	m_pUIMgr->WorldDraw();

	SetDrawScreen(DX_SCREEN_BACK);
	m_pCamera->Draw();

	m_pUIMgr->ScreenDraw();
	m_pUIMgr->DebugDraw();
}
