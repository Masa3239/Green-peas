#include "SceneTestSyoguti.h"
#include <DxLib.h>

#include "ItemManager.h"
#include "EnemyBoss.h"
#include "../../Utility/Input.h"
#include "../../Utility/Transform.h"

namespace {

	constexpr Vector3 kTestHealPos = { 100.0f, 100.0f, 0.0f };
	constexpr Vector3 kTestAttackPos = { 300.0f, 300.0f, 0.0f };
	constexpr Vector3 kTestBossPos = { 200.0f, 200.0f, 0.0f };
}

SceneTestSyoguti::SceneTestSyoguti() :
	m_pItemMgr(nullptr),
	m_pEnemyBoss(nullptr),
	m_transform()
{
	m_transform.Reset();
}

SceneTestSyoguti::~SceneTestSyoguti()
{
}

void SceneTestSyoguti::Init()
{
	

	 m_pItemMgr = std::make_unique<ItemManager>();
	 m_pItemMgr->Init();
	 m_pEnemyBoss = std::make_unique<EnemyBoss>(kTestBossPos);
	 m_pEnemyBoss->Init();

}

void SceneTestSyoguti::End()
{
	m_pItemMgr->End();
	m_pEnemyBoss->End();
}

SceneBase* SceneTestSyoguti::Update()
{
	m_pEnemyBoss->Update();
	if (Input::IsPressed(PAD_INPUT_10)) {
		 m_pItemMgr->Create(ItemBase::ItemType::Heal, kTestHealPos);
		 m_pItemMgr->Create(ItemBase::ItemType::Attack, kTestAttackPos);
	}
	return this;
}

void SceneTestSyoguti::Draw()
{
	m_pItemMgr->Draw();
	m_pEnemyBoss->Draw();
	printfDx("SceneTestSyoguti\n");
}
