#include "SceneTestOsawa.h"
#include <DxLib.h>
#include "../Personal/Asai/Camera.h"
#include "../Personal/Asai/UIManager.h"
#include "../Personal/Kimura/Map/Map.h"
#include "../Personal/Osawa/Enemy/EnemyManager.h"
#include "../Personal/Osawa/PauseMenu.h"
#include "../Personal/Syoguti/ItemManager.h"
#include "../Personal/Takagi/Player.h"
#include "../Personal/Takagi/WeaponManager.h"
#include "../System/ObjectManager.h"
#include "../System/PauseManager.h"
#include "../System/InputManager.h"
#include "../System/Input/Keyboard.h"
#include "../Scene/SceneSelection.h"

SceneTestOsawa::SceneTestOsawa() :
	m_pPlayer(nullptr),
	m_pCamera(nullptr),
	m_pEnemyMgr(nullptr),
	m_pUIMgr(nullptr),
	m_pItemMgr(nullptr),
	m_pMap(nullptr),
	m_pWeaponManager(nullptr),
	m_pPauseMenu(nullptr)
{
	m_pPlayer = std::make_unique<Player>(GetObjectManager());
	m_pCamera = std::make_unique<Camera>();
	m_pEnemyMgr = std::make_unique<EnemyManager>(GetObjectManager());
	m_pUIMgr = std::make_unique<UIManager>();
	m_pItemMgr = std::make_unique<ItemManager>();
	m_pMap = std::make_unique<Map>();
	m_pWeaponManager = std::make_unique<WeaponManager>();
	m_pPauseMenu = std::make_unique<PauseMenu>();
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

	m_pMap->Init();

	m_pCamera->Init();
	m_pCamera->SetMap(m_pMap.get());
	m_pCamera->GenerateWorldScreen();

	m_pEnemyMgr->SetPlayer(m_pPlayer.get());
	m_pEnemyMgr->SetUIManager(m_pUIMgr.get());
	m_pEnemyMgr->Init();

	m_pUIMgr->Init();

	m_pItemMgr->Init();
	m_pItemMgr->SetObjectManager(GetObjectManager());
	m_pItemMgr->SetPlayer(m_pPlayer.get());

	m_pWeaponManager->SetPlayer(m_pPlayer.get());
	m_pWeaponManager->SetObjManager(GetObjectManager());
	m_pWeaponManager->SetEnemyManager(m_pEnemyMgr.get());
	m_pWeaponManager->Init();

	m_pPauseMenu->Init();

	PauseManager::GetInstance().SetObjectManager(GetObjectManager());
}

void SceneTestOsawa::End()
{
	m_pPauseMenu->End();
	m_pWeaponManager->End();
	m_pMap->End();
	m_pItemMgr->End();
	m_pUIMgr->End();
	m_pEnemyMgr->End();
	m_pCamera->End();
	m_pPlayer->End();
}

SceneBase* SceneTestOsawa::Update()
{
	auto nextScene = m_pPauseMenu->Update();
	if (nextScene != nullptr)
	{
		return nextScene;
	}

	if (PauseManager::GetInstance().IsPause()) return this;

	m_pUIMgr->SetPlayer(m_pPlayer.get());

	m_pEnemyMgr->Update();

	m_pUIMgr->Update();

	m_pItemMgr->Update();

	m_pMap->Update();

	m_pWeaponManager->Update();

	if (Keyboard::GetInstance().IsDown(KEY_INPUT_R))
	{
		return new SceneSelection();
	}

	return this;
}

void SceneTestOsawa::Draw()
{
	m_pItemMgr->Draw();
	m_pPauseMenu->Draw();
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

	//clsDx();
}
