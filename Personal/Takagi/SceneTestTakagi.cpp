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
namespace {
	Vector3 kBoxPos = { 200,200 ,0 };
	Vector3 kBoxSize = { 50,70 ,0 };
	Collision::AABB box = Collision::AABB(kBoxPos, kBoxSize);
}

SceneTestTakagi::SceneTestTakagi():
	m_pPlayer(nullptr),
	m_pCamera(nullptr),
	m_pEnemyManager(nullptr),
	m_pItemManager(nullptr),
	m_pMap(nullptr),
	m_pUIManager(nullptr)
{
	m_pPlayer = std::make_unique<Player>(GetObjectManager());
	m_pCamera = std::make_unique<Camera>();
	m_pEnemyManager = std::make_unique<EnemyManager>(GetObjectManager());
	m_pItemManager = std::make_unique<ItemManager>();
	m_pMap = std::make_unique<Map>();
	m_pUIManager = std::make_unique<UIManager>();
}

SceneTestTakagi::~SceneTestTakagi()
{
}

void SceneTestTakagi::Init()
{
	m_pPlayer->SetEnemyManager(m_pEnemyManager.get());
	m_pPlayer->Init();
	m_pCamera->Init();
	m_pMap->Init();
	m_pPlayer->SetCamera(m_pCamera.get());
	m_pPlayer->SetItemManager(m_pItemManager.get());
	m_pEnemyManager->SetPlayer(m_pPlayer.get());
	m_pEnemyManager->SetUIManager(m_pUIManager.get());
	m_pUIManager->Init();
	m_pCamera->SetMap(m_pMap.get());
	m_pCamera->GenerateWorldScreen();
}

void SceneTestTakagi::End()
{
	m_pPlayer->End();
	m_pCamera->End();
	m_pMap->End();
	m_pItemManager->End();
	m_pUIManager->End();
	
}

SceneBase* SceneTestTakagi::Update()
{
	m_pUIManager->SetPlayer(m_pPlayer.get());
	Time::GetInstance().SetTimeScale(1);
	//m_pPlayer->Update();
	//m_pPlayer->Update();
	if (m_pPlayer->IsDead()) {
		return new SceneSelection();
	}

	//Segment_Point_MinLength()


	if (box.CheckCollision(m_pPlayer->GetCircle())) {
		printfDx("当たってる\n");
	}
	else {
		printfDx("当たってない\n");
	}

	box.SetPosition(kBoxPos);

	if (Pad::IsPressed(Pad::Button::Start)) {
		return new SceneSelection();
	}
	//m_pMap->Update();


	//m_pItemManager->Update();
	//m_pEnemyManager->Update();
	m_pUIManager->Update();


	return this;
}

void SceneTestTakagi::Draw()
{
	printfDx("SceneTestTakagi\n");
	box.DebugDraw();
	
}

void SceneTestTakagi::PreDraw()
{

	SetDrawScreen(m_pCamera->GetWorldScreen());

	ClearDrawScreen();
	m_pMap->Draw();
}

void SceneTestTakagi::PostDraw()
{
	m_pUIManager->WorldDraw();

	SetDrawScreen(DX_SCREEN_BACK);
	m_pCamera->Draw();
	
	m_pUIManager->ScreenDraw();
	m_pUIManager->DebugDraw();

}
