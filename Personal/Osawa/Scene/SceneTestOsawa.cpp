#include "SceneTestOsawa.h"
#include <DxLib.h>
#include "../Enemy/EnemyManager.h"

SceneTestOsawa::SceneTestOsawa() :
	m_enemyMgr(nullptr)
{
}

SceneTestOsawa::~SceneTestOsawa()
{
}

void SceneTestOsawa::Init()
{
	m_enemyMgr = std::make_unique<EnemyManager>();
	m_enemyMgr->Init();

	m_enemyMgr->AddEnemy();
	m_enemyMgr->AddEnemy();
}

void SceneTestOsawa::End()
{
	m_enemyMgr->End();
}

SceneBase* SceneTestOsawa::Update()
{
	m_enemyMgr->Update();

	return this;
}

void SceneTestOsawa::Draw()
{
	m_enemyMgr->Draw();

	printfDx("SceneTestOsawa\n");
}
