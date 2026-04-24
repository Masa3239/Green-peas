#include "SceneTestSyoguti.h"
#include <DxLib.h>

#include "ItemManager.h"
#include "EnemyBoss.h"
#include "../../Utility/Input.h"
#include "../../Utility/Transform.h"
#include "../../System/ObjectManager.h"
#include "../Takagi/Player.h"
#include "../Takagi/WeaponManager.h"
#include"../Takagi/Warrior.h"
#include"../Takagi/Hunter.h"
#include"../Takagi/Wizard.h"
#include "../Asai/Camera.h"
#include"../../Personal/Osawa/Scene/SceneSelection.h"
#include"../../Chara/Collision.h"
#include"../../Utility/Time.h"
#include"../Kimura/Map/Map.h"
#include"../Osawa/Enemy/EnemyManager.h"
#include"../Asai/UIManager.h"
#include "../Syoguti/ChestManager.h"

namespace {

	constexpr Vector3 kTestHealPos = { 100.0f, 100.0f, 0.0f };
	constexpr Vector3 kTestAttackPos = { 300.0f, 300.0f, 0.0f };
	constexpr Vector3 kTestBossPos = { 5000.0f, 9640.0f, 0.0f };
	constexpr Vector3 kTestPos = { 5100.0f, 9640.0f, 0.0f };
}

SceneTestSyoguti::SceneTestSyoguti() :
	m_pItemMgr(nullptr),
	m_pEnemyBoss(nullptr),
	m_pPlayer(nullptr),
	m_pCamera(nullptr),
	m_pWeaponMgr(nullptr),
	m_pEnemyManager(nullptr),
	m_pMap(nullptr),
	m_pUIManager(nullptr),
	m_pChest(nullptr),
	m_transform(),
	m_buffRandom()
{
	m_pItemMgr = std::make_unique<ItemManager>();
	m_pEnemyBoss = std::make_unique<EnemyBoss>(GetObjectManager(), kTestBossPos);

	m_pCamera = std::make_unique<Camera>();
	m_pWeaponMgr = std::make_unique<WeaponManager>();
	m_pEnemyManager = std::make_unique<EnemyManager>(GetObjectManager());
	m_pMap = std::make_unique<Map>();
	m_pUIManager = std::make_unique<UIManager>();
	m_transform.Reset();
	m_buffRandom.Init();

	m_pChest = std::make_unique<ChestManager>();
	
}

SceneTestSyoguti::~SceneTestSyoguti()
{
}

void SceneTestSyoguti::Init()
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
	m_pPlayer->SetCamera(m_pCamera.get());
	m_pPlayer->Init();
	m_pPlayer->SetItemManager(m_pItemMgr.get());

	 m_pMap->Init();
	m_pCamera->SetMap(m_pMap.get());
	m_pCamera->GenerateWorldScreen();
	m_pCamera->Init();

	m_pItemMgr->SetObjectManager(GetObjectManager());
	m_pItemMgr->SetPlayer(m_pPlayer.get());
	m_pItemMgr->Init();

	m_pEnemyManager->SetPlayer(m_pPlayer.get());
	m_pEnemyManager->SetUIManager(m_pUIManager.get());

	 m_pEnemyBoss->SetPlayer(m_pPlayer.get());
	 m_pEnemyBoss->Init();


	 m_pUIManager->Init();

	 m_pWeaponMgr->SetPlayer(m_pPlayer.get());
	 m_pWeaponMgr->SetObjManager(GetObjectManager());
	 m_pWeaponMgr->SetEnemyManager(m_pEnemyManager.get());
	 m_pWeaponMgr->Init();
	 
	 m_pChest->SetObjectManager(GetObjectManager());
	 m_pChest->Init();
}

void SceneTestSyoguti::End()
{
	
	m_pCamera->End();
	m_pPlayer->End();
	m_pItemMgr->End();
	m_pEnemyBoss->End();
	m_pMap->End();
	m_pUIManager->End();
	m_pWeaponMgr->End();
	m_pChest->End();
}

SceneBase* SceneTestSyoguti::Update()
{
	// m_pItemMgr->Update();
	// m_pEnemyBoss->Update();

	m_pUIManager->SetPlayer(m_pPlayer.get());
	Time::GetInstance().SetTimeScale(1);

	if (m_pPlayer->IsDead()) {
		return new SceneSelection();
	}
	m_pWeaponMgr->Update();

	m_pUIManager->Update();

	if (Input::IsPressed(PAD_INPUT_10)) {

		
		 m_pItemMgr->Create(ItemBase::ItemType::Heal, kTestHealPos);
		 m_pItemMgr->Create(ItemBase::ItemType::Attack, kTestAttackPos);
	}

	if (Input::IsPressed(PAD_INPUT_1)) {
		m_testDraw = m_buffRandom.GetRandomBuffs(3);
	}

	if (Input::IsPressed(PAD_INPUT_2)) {
		if (m_pEnemyBoss->SealReleaseFlag()) {
			printfDx("封印解除\n");
		}
	}

	if (Input::IsPressed(PAD_INPUT_10)) {
		m_pEnemyBoss->Damage(50);
	}

	if (Input::IsPressed(PAD_INPUT_10)) {
		m_pChest->Create(kTestPos);
	}

	m_pChest->CheckHitCollision(m_pPlayer->GetCircle());

	return this;
}

void SceneTestSyoguti::Draw()
{
	// m_pItemMgr->Draw();
	// m_pEnemyBoss->Draw();
	printfDx("SceneTestSyoguti\n");

	m_buffRandom.Draw(m_testDraw);

	//for (auto e : m_testDraw) {
	//	m_buffRandom.CheckBuff(e);
	//}
}

void SceneTestSyoguti::PreDraw()
{
	SetDrawScreen(m_pCamera->GetWorldScreen());

	ClearDrawScreen();
	m_pMap->Draw();
}

void SceneTestSyoguti::PostDraw()
{
	m_pUIManager->WorldDraw();

	SetDrawScreen(DX_SCREEN_BACK);
	m_pCamera->Draw();

	m_pUIManager->ScreenDraw();
	m_pUIManager->DebugDraw();
}

