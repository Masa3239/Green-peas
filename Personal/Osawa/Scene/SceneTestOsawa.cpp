#include "SceneTestOsawa.h"
#include <DxLib.h>
#include "../Enemy/EnemyManager.h"
#include "../Personal/Takagi/Player.h"
#include "../Personal/Asai/Camera.h"
#include "../Personal/Asai/UIManager.h"
#include "../System/ObjectManager.h"

SceneTestOsawa::SceneTestOsawa() :
	m_player(nullptr),
	m_camera(nullptr),
	m_enemyMgr(nullptr),
	m_uiMgr(nullptr)
{
	m_player = std::make_unique<Player>(GetObjectManager());
	m_camera = std::make_unique<Camera>();
	m_enemyMgr = std::make_unique<EnemyManager>(GetObjectManager());
	m_uiMgr = std::make_unique<UIManager>();
}

SceneTestOsawa::~SceneTestOsawa()
{
}

void SceneTestOsawa::Init()
{
	m_player->Init();
	m_player->SetCamera(m_camera.get());
	m_camera->Init();

	m_enemyMgr->Init();
	m_enemyMgr->SetPlayer(m_player.get());
	m_enemyMgr->SetUIManager(m_uiMgr.get());

	m_uiMgr->Init();

	m_enemyMgr->AddEnemyTest();
	m_enemyMgr->AddEnemyTest();
}

void SceneTestOsawa::End()
{
	m_uiMgr->End();
	m_enemyMgr->End();
	m_camera->End();
	m_player->End();
}

SceneBase* SceneTestOsawa::Update()
{
	m_uiMgr->SetPlayer(m_player.get());

	m_enemyMgr->Update();

	m_player->Update();

	//m_enemyMgr->CheckHitEnemies(m_player->GetCircle(), 1);

	m_uiMgr->Update();

	return this;
}

void SceneTestOsawa::Draw()
{
	m_enemyMgr->Draw();
}

void SceneTestOsawa::PreDraw()
{
	printfDx("SceneTestOsawa\n");

	SetDrawScreen(m_camera->GetWorldScreen());
	ClearDrawScreen();
}

void SceneTestOsawa::PostDraw()
{
	m_uiMgr->WorldDraw();

	SetDrawScreen(DX_SCREEN_BACK);
	m_camera->Draw();

	m_uiMgr->ScreenDraw();
	m_uiMgr->DebugDraw();
}
