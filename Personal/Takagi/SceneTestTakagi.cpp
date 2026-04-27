#include "SceneTestTakagi.h"
#include <DxLib.h>
#include"../../Personal/Takagi/Player.h"
#include"../../Personal/Asai/Camera.h"
#include"../../Personal/Osawa/Scene/SceneSelection.h"
#include"../../Chara/Collision.h"
#include"../../Utility/Time.h"
#include"../Kimura/Map/Map.h"
#include"../Syoguti/ItemManager.h"
#include"../Osawa/Enemy/EnemyManager.h"
#include"../Asai/UIManager.h"
#include"BuffManager.h"
#include"WeaponManager.h"
#include"Warrior.h"
#include"Hunter.h"
#include"Wizard.h"
#include"Result/ResultShow.h"
#include"../../Scene/CharacterSelectScene.h"
#include"../../System/InputManager.h"
#include"../../System/Input/Gamepad.h"
#include"../../System/PauseManager.h"
#include"../Osawa/PauseMenu.h"

SceneTestTakagi::SceneTestTakagi():
	m_pPlayer(nullptr),
	m_pCamera(nullptr),
	m_pEnemyManager(nullptr),
	m_pItemManager(nullptr),
	m_pMap(nullptr),
	m_pUIManager(nullptr),
	m_pWeaponManager(nullptr),
	m_pResultShow(nullptr)
{
	//m_pPlayer = std::make_unique<Player>(GetObjectManager());
	//m_pPlayer = std::make_unique<Wizard>(GetObjectManager());

	m_pCamera = std::make_unique<Camera>();
	m_pEnemyManager = std::make_unique<EnemyManager>(GetObjectManager());
	m_pItemManager = std::make_unique<ItemManager>();
	m_pMap = std::make_unique<Map>();
	m_pUIManager = std::make_unique<UIManager>();
	m_pWeaponManager = std::make_unique<WeaponManager>();
	m_pPauseMenu = std::make_unique<PauseMenu>();
	m_pBuffManager = std::make_unique<BuffManager>();
	m_pResultShow = std::make_unique <ResultShow>();
}

SceneTestTakagi::~SceneTestTakagi()
{
}

void SceneTestTakagi::Init()
{
	switch (GetCarryOver().characterJob)
	{
	case Character::Job::Warrior:
		m_pPlayer = std::make_unique<Warrior>(GetObjectManager());
		break;
	case Character::Job::Hunter:
		m_pPlayer = std::make_unique<Hunter>(GetObjectManager());
		break;
	case Character::Job::Wizard:
		m_pPlayer = std::make_unique<Wizard>(GetObjectManager());
		break;
	default:
		m_pPlayer = std::make_unique<Warrior>(GetObjectManager());
		break;
	}
	m_pPlayer->SetEnemyManager(m_pEnemyManager.get());
	m_pPlayer->Init();
	m_pPlayer->SetCamera(m_pCamera.get());
	m_pPlayer->SetItemManager(m_pItemManager.get());
	m_pPlayer->SetBuffManager(m_pBuffManager.get());
	m_pCamera->Init();
	m_pMap->Init();
	m_pEnemyManager->SetPlayer(m_pPlayer.get());
	m_pEnemyManager->SetUIManager(m_pUIManager.get());
	m_pEnemyManager->Init();
	m_pUIManager->Init();
	m_pCamera->SetMap(m_pMap.get());
	m_pCamera->GenerateWorldScreen();
	m_pItemManager->Init();
	m_pItemManager->SetObjectManager(GetObjectManager());
	m_pItemManager->SetPlayer(m_pPlayer.get());
	m_pWeaponManager->SetPlayer(m_pPlayer.get());
	m_pWeaponManager->SetObjManager(GetObjectManager());
	m_pWeaponManager->SetEnemyManager(m_pEnemyManager.get());
	m_pWeaponManager->Init();

	m_pPauseMenu->Init();
	PauseManager::GetInstance().SetObjectManager(GetObjectManager());
	m_pBuffManager->SetPlayer(m_pPlayer.get());
}

void SceneTestTakagi::End()
{
	m_pPlayer->End();
	m_pCamera->End();
	m_pMap->End();
	m_pItemManager->End();
	m_pUIManager->End();
	m_pWeaponManager->End();
	m_pResultShow->End();
}

SceneBase* SceneTestTakagi::Update()
{
	SceneBase* nextScene = nullptr;
	if (m_pBuffManager->IsSelect()) {
		m_pBuffManager->Update();
	}
	else if (m_pResultShow->IsResult()) {
		nextScene = m_pResultShow->Update();
	}
	else {
		nextScene = m_pPauseMenu->Update();
		
	}
	if (nextScene != nullptr)
	{
		return nextScene;
	}

	if (PauseManager::GetInstance().IsPause()) return this;

	m_pUIManager->SetPlayer(m_pPlayer.get());
	Time::GetInstance().SetTimeScale(1);
	if (m_pPlayer->IsDead()) {
		m_carryOver.isClear = Score::Result::Failed;
		m_pResultShow->Init(m_carryOver);

	}
	m_pWeaponManager->Update();

	if (Gamepad::GetInstance().IsDown(XINPUT_BUTTON_BACK)) {
		return new CharacterSelectScene;
	}
	m_pUIManager->Update();


	return this;
}

void SceneTestTakagi::Draw()
{
	printfDx("SceneTestTakagi\n");
}

void SceneTestTakagi::PreDraw()
{

	if (PauseManager::GetInstance().IsPause())return;
	SetDrawScreen(m_pCamera->GetWorldScreen());

	ClearDrawScreen();
	m_pMap->Draw();
}

void SceneTestTakagi::PostDraw()
{
	if (!PauseManager::GetInstance().IsPause()) {
	m_pUIManager->WorldDraw();

	SetDrawScreen(DX_SCREEN_BACK);
	m_pCamera->Draw();
	
	m_pUIManager->ScreenDraw();
	m_pUIManager->DebugDraw();

	}

	
	else {
		if (m_pBuffManager->IsSelect()) {
			m_pBuffManager->Draw();
		}
		else if (m_pResultShow->IsResult()) {
			m_pResultShow->Draw();
		}
		else {
			m_pPauseMenu->Draw();
		}
	}
}
