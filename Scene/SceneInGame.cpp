#include "SceneInGame.h"
#include <DxLib.h>
#include "../Personal/Asai/Camera.h"
#include "../Personal/Asai/UIManager.h"
#include "../Personal/Kimura/Map/Map.h"
#include "../Personal/Kimura/EnemyMap/EnemyMap.h"
#include "../Personal/Osawa/Enemy/EnemyManager.h"
#include "../Personal/Osawa/PauseMenu.h"
#include "../Personal/Syoguti/ItemManager.h"
#include "../Personal/Syoguti/ChestManager.h"
#include "../Personal/Takagi/Player.h"
#include "../Personal/Takagi/WeaponManager.h"
#include "../Personal/Takagi/BuffManager.h"
#include "../Personal/Takagi/Warrior.h"
#include "../Personal/Takagi/Hunter.h"
#include "../Personal/Takagi/Wizard.h"
#include "../Personal/Takagi/Result/ResultShow.h"
#include "../Personal/Syoguti/EnemyBoss.h"
#include "../System/PauseManager.h"
#include "../System/InputManager.h"

#include "../Personal/Osawa/Scene/SceneSelection.h"
#include "../Personal/Osawa/Scene/SceneTempResult.h"

namespace
{
}

SceneInGame::SceneInGame() :
	m_pPlayer(nullptr),
	m_pCamera(nullptr),
	m_pEnemyMgr(nullptr),
	m_pUIMgr(nullptr),
	m_pItemMgr(nullptr),
	m_pMap(nullptr),
	m_pEnemyMap(nullptr),
	m_pWeaponManager(nullptr),
	m_pPauseMenu(nullptr),
	m_pBuffManager(nullptr),
	m_pResultShow(nullptr)
{
	m_pCamera = std::make_unique<Camera>();
	m_pEnemyMgr = std::make_unique<EnemyManager>(GetObjectManager());
	m_pUIMgr = std::make_unique<UIManager>();
	m_pItemMgr = std::make_unique<ItemManager>();
	m_pMap = std::make_unique<Map>();
	m_pEnemyMap = std::make_unique<EnemyMap>();
	m_pWeaponManager = std::make_unique<WeaponManager>();
	m_pPauseMenu = std::make_unique<PauseMenu>();
	m_pBuffManager = std::make_unique<BuffManager>();
	m_pChestManager = std::make_unique<ChestManager>();
	m_pResultShow = std::make_unique <ResultShow>();
}

SceneInGame::~SceneInGame()
{
}

void SceneInGame::Init()
{
	switch (GetCarryOver().characterJob)
	{
	case Character::Job::Warrior:	m_pPlayer = std::make_unique<Warrior>(GetObjectManager());	break;
	case Character::Job::Hunter:	m_pPlayer = std::make_unique<Hunter>(GetObjectManager());	break;
	case Character::Job::Wizard:	m_pPlayer = std::make_unique<Wizard>(GetObjectManager());	break;
	default:						m_pPlayer = std::make_unique<Warrior>(GetObjectManager());	break;
	}

	m_pPlayer->SetCamera(m_pCamera.get());
	m_pPlayer->SetEnemyManager(m_pEnemyMgr.get());
	m_pPlayer->SetItemManager(m_pItemMgr.get());
	m_pPlayer->SetBuffManager(m_pBuffManager.get());
	m_pPlayer->Init();

	m_pMap->Init();
	m_pEnemyMap->Init();

	m_pCamera->SetMap(m_pMap.get());
	m_pCamera->GenerateWorldScreen();
	m_pCamera->Init();

	m_pEnemyMgr->SetPlayer(m_pPlayer.get());
	m_pEnemyMgr->SetUIManager(m_pUIMgr.get());
	m_pEnemyMgr->SetWeaponManager(m_pWeaponManager.get());
	m_pEnemyMgr->SetChestManager(m_pChestManager.get());
	m_pEnemyMgr->SetMap(m_pMap.get());
	m_pEnemyMgr->Init();
	m_pEnemyMgr->InitGenerate(m_pEnemyMap.get());

	m_pUIMgr->Init();
	m_pUIMgr->SetEnemyManager(m_pEnemyMgr.get());
	m_pUIMgr->SetPlayer(m_pPlayer.get());
	m_pUIMgr->SetItemManager(m_pItemMgr.get());
	m_pUIMgr->GenerateMinimap(m_pCamera.get(), m_pMap.get());

	m_pItemMgr->SetObjectManager(GetObjectManager());
	m_pItemMgr->SetPlayer(m_pPlayer.get());
	m_pItemMgr->Init();

	m_pWeaponManager->SetPlayer(m_pPlayer.get());
	m_pWeaponManager->SetObjManager(GetObjectManager());
	m_pWeaponManager->SetEnemyManager(m_pEnemyMgr.get());
	m_pWeaponManager->Init();

	m_pBuffManager->SetPlayer(m_pPlayer.get());
	m_pBuffManager->Init();

	m_pChestManager->SetObjectManager(GetObjectManager());
	m_pChestManager->SetWeaponManager(m_pWeaponManager.get());
	m_pChestManager->SetItemManager(m_pItemMgr.get());
	m_pChestManager->Init();

	m_pPauseMenu->Init();
	PauseManager::GetInstance().SetObjectManager(GetObjectManager());
}

void SceneInGame::End()
{
	m_pResultShow->End();
	m_pChestManager->End();
	m_pBuffManager->End();
	m_pPauseMenu->End();
	m_pWeaponManager->End();
	m_pEnemyMap->End();
	m_pMap->End();
	m_pItemMgr->End();
	m_pUIMgr->End();
	m_pEnemyMgr->End();
	m_pCamera->End();
	m_pPlayer->End();

	m_carryOver.Reset();
}

SceneBase* SceneInGame::Update()
{
	if (m_pBuffManager->IsSelect())
	{
		m_pBuffManager->Update();
	}
	else if (m_pResultShow->IsResult())
	{
		auto nextScene = m_pResultShow->Update();;
		if (nextScene != nullptr)
		{
			return nextScene;
		}
	}
	else
	{
		auto nextScene = m_pPauseMenu->Update();
		if (nextScene != nullptr)
		{
			return nextScene;
		}
	}

	//m_pBuffManager->Update();

	if (!PauseManager::GetInstance().IsPause())
	{
		m_pEnemyMgr->Update();
		m_pItemMgr->Update();
		m_pMap->Update();
		m_pWeaponManager->Update();

		m_pUIMgr->SetPlayer(m_pPlayer.get());
		m_pUIMgr->Update();

		m_pChestManager->Update();
		m_pChestManager->CheckHitCollision(m_pPlayer->GetCircle());

		if (m_pEnemyMgr->GetEnemyBoss()->GetIsDead())
		{
			m_carryOver.isClear = Score::Result::Clear;
			m_pResultShow->Init(m_carryOver);
		}

		// プレイヤーが死亡していたら
		if (m_pPlayer->IsDead())
		{
			m_carryOver.isClear = Score::Result::Failed;
			m_pResultShow->Init(m_carryOver);
		}
	}

	return this;
}

void SceneInGame::Draw()
{
	if (!PauseManager::GetInstance().IsPause())
	{
		m_pItemMgr->Draw();
	}
}

void SceneInGame::PreDraw()
{
	if (!PauseManager::GetInstance().IsPause())
	{
		SetDrawScreen(m_pCamera->GetWorldScreen());
		ClearDrawScreen();

		m_pMap->Draw();
	}
}

void SceneInGame::PostDraw()
{
	if (!PauseManager::GetInstance().IsPause())
	{
		m_pUIMgr->WorldDraw();

		SetDrawScreen(DX_SCREEN_BACK);
		m_pCamera->Draw();

		m_pUIMgr->ScreenDraw();
	}
	else
	{
		if (m_pBuffManager->IsSelect())
		{
			m_pBuffManager->Draw();
		}
		else if (m_pResultShow->IsResult())
		{
			m_pResultShow->Draw();
		}
		else
		{
			m_pPauseMenu->Draw();
		}
	}

	clsDx();
}
