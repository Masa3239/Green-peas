#include "SceneTestSyoguti.h"
#include <DxLib.h>

#include "ItemManager.h"
#include "EnemyBoss.h"
#include "../../Utility/Input.h"
#include "../../Utility/Transform.h"
#include "../../System/ObjectManager.h"

namespace {

	constexpr Vector3 kTestHealPos = { 100.0f, 100.0f, 0.0f };
	constexpr Vector3 kTestAttackPos = { 300.0f, 300.0f, 0.0f };
	constexpr Vector3 kTestBossPos = { 200.0f, 200.0f, 0.0f };
}

SceneTestSyoguti::SceneTestSyoguti() :
	m_pItemMgr(nullptr),
	m_pEnemyBoss(nullptr),
	m_transform(),
	m_buffRandom()
{
	m_transform.Reset();
	m_buffRandom.Init();
}

SceneTestSyoguti::~SceneTestSyoguti()
{
}

void SceneTestSyoguti::Init()
{

	 m_pItemMgr = std::make_unique<ItemManager>();

	 m_pItemMgr->SetObjectManager(GetObjectManager());

	 m_pItemMgr->Init();

	 m_pEnemyBoss = std::make_unique<EnemyBoss>( GetObjectManager(), kTestBossPos);
	 m_pEnemyBoss->Init();

}

void SceneTestSyoguti::End()
{
	
	m_pItemMgr->End();
	m_pEnemyBoss->End();
}

SceneBase* SceneTestSyoguti::Update()
{
	m_pItemMgr->Update();
	m_pEnemyBoss->Update();
	if (Input::IsPressed(PAD_INPUT_10)) {

		
		 m_pItemMgr->Create(ItemBase::ItemType::Heal, kTestHealPos);
		 m_pItemMgr->Create(ItemBase::ItemType::Attack, kTestAttackPos);
	}

	if (Input::IsPressed(PAD_INPUT_1)) {
		m_testDraw = m_buffRandom.GetRandomBuffs(3);
	}
	return this;
}

void SceneTestSyoguti::Draw()
{
	
	for (auto e : m_testDraw) {
		printfDx("Buff: %d\n", (int)e);
	}

	m_pItemMgr->Draw();
	m_pEnemyBoss->Draw();
	printfDx("SceneTestSyoguti\n");
}
