#include "SceneTestSyoguti.h"
#include <DxLib.h>

#include "ItemManager.h"
#include "EnemyBoss.h"
#include "../../Utility/Input.h"
#include "../../Utility/Transform.h"
#include "../../System/ObjectManager.h"
#include "../Takagi/Player.h"
#include "../Asai/Camera.h"

namespace {

	constexpr Vector3 kTestHealPos = { 100.0f, 100.0f, 0.0f };
	constexpr Vector3 kTestAttackPos = { 300.0f, 300.0f, 0.0f };
	constexpr Vector3 kTestBossPos = { 200.0f, 200.0f, 0.0f };
}

SceneTestSyoguti::SceneTestSyoguti() :
	m_pItemMgr(nullptr),
	m_pEnemyBoss(nullptr),
	m_pPlayer(nullptr),
	m_pCamera(nullptr),
	m_transform(),
	m_buffRandom()
{
	m_pItemMgr = std::make_unique<ItemManager>();
	m_pPlayer = std::make_unique<Player>(GetObjectManager());
	m_pCamera = std::make_unique<Camera>();
	m_transform.Reset();
	m_buffRandom.Init();
}

SceneTestSyoguti::~SceneTestSyoguti()
{
}

void SceneTestSyoguti::Init()
{
	m_pPlayer->Init();
	m_pPlayer->SetCamera(m_pCamera.get());
	m_pPlayer->SetItemManager(m_pItemMgr.get());

	m_pCamera->Init();

	m_pItemMgr->Init();
	m_pItemMgr->SetObjectManager(GetObjectManager());


	 m_pEnemyBoss = std::make_unique<EnemyBoss>( GetObjectManager(), kTestBossPos);
	 m_pEnemyBoss->SetPlayer(m_pPlayer.get());
	 m_pEnemyBoss->Init();
	 
}

void SceneTestSyoguti::End()
{
	
	m_pCamera->End();
	m_pPlayer->End();
	m_pItemMgr->End();
	m_pEnemyBoss->End();

}

SceneBase* SceneTestSyoguti::Update()
{
	// m_pItemMgr->Update();
	// m_pEnemyBoss->Update();

	if (Input::IsPressed(PAD_INPUT_10)) {

		
		 m_pItemMgr->Create(ItemBase::ItemType::Heal, kTestHealPos);
		 m_pItemMgr->Create(ItemBase::ItemType::Attack, kTestAttackPos);
	}

	if (Input::IsPressed(PAD_INPUT_1)) {
		m_testDraw = m_buffRandom.GetRandomBuffs(3);
	}

	if (Input::IsPressed(PAD_INPUT_2)) {
		if (m_pEnemyBoss->SealReleaseFlag(3)) {
			printfDx("封印解除\n");
		}
	}
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

