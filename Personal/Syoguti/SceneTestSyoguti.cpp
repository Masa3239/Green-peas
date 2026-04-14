#include "SceneTestSyoguti.h"
#include <DxLib.h>

#include "ItemManager.h"
#include "EnemyBoss.h"

SceneTestSyoguti::SceneTestSyoguti() :
	m_pItemMgr(nullptr),
	m_pEnemyBoss(nullptr)
{
}

SceneTestSyoguti::~SceneTestSyoguti()
{
}

void SceneTestSyoguti::Init()
{

	 m_pItemMgr = std::make_unique<ItemManager>();
	 m_pItemMgr->Init();
	 m_pEnemyBoss = std::make_unique<EnemyBoss>();
	 m_pEnemyBoss->Init();
}

void SceneTestSyoguti::End()
{
	m_pItemMgr->End();
	m_pEnemyBoss->End();
}

SceneBase* SceneTestSyoguti::Update()
{
	return this;
}

void SceneTestSyoguti::Draw()
{
	m_pItemMgr->Draw();
	m_pEnemyBoss->Draw();
	printfDx("SceneTestSyoguti\n");
}
