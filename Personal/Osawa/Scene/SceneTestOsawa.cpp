#include "SceneTestOsawa.h"
#include <DxLib.h>
#include "../Enemy/EnemyManager.h"
#include "../Personal/Takagi/Player.h"
#include "../Personal/Asai/Camera.h"
#include "../System/ObjectManager.h"

SceneTestOsawa::SceneTestOsawa() :
	m_player(nullptr),
	m_camera(nullptr),
	m_enemyMgr(nullptr)
{
	m_player = std::make_unique<Player>(GetObjectManager());
	m_camera = std::make_unique<Camera>();
	m_enemyMgr = std::make_unique<EnemyManager>(GetObjectManager());
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

	m_enemyMgr->AddEnemy();
	m_enemyMgr->AddEnemy();
}

void SceneTestOsawa::End()
{
	m_enemyMgr->End();
	m_camera->End();
	m_player->End();
}

SceneBase* SceneTestOsawa::Update()
{
	m_enemyMgr->Update();

	m_player->Update();

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
	SetDrawScreen(DX_SCREEN_BACK);
	m_camera->Draw();
}
