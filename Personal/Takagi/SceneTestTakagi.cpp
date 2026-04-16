#include "SceneTestTakagi.h"
#include <DxLib.h>
#include"../../Personal/Takagi/Player.h"
#include"../../Personal/Asai/Camera.h"
#include"../../Personal/Osawa/Scene/SceneSelection.h"
#include"../../Chara/Collision.h"
#include"../../Utility/Time.h"
#include"../Kimura/Map/Map.h"
namespace {
	Vector3 kBoxPos = { 200,200 ,0 };
	Vector3 kBoxSize = { 50,70 ,0 };
	Collision::AABB box = Collision::AABB(kBoxPos, kBoxSize);
}

SceneTestTakagi::SceneTestTakagi()
{
	m_pPlayer = std::make_unique<Player>(GetObjectManager());
	m_pCamera = std::make_unique<Camera>();
	m_pMap = new Map();
}

SceneTestTakagi::~SceneTestTakagi()
{
}

void SceneTestTakagi::Init()
{
	m_pPlayer->Init();
	m_pCamera->Init();
	m_pPlayer->SetCamera(m_pCamera.get());
	m_pMap->Init();
}

void SceneTestTakagi::End()
{
	m_pPlayer->End();
	m_pCamera->End();
	m_pMap->End();

}

SceneBase* SceneTestTakagi::Update()
{
	Time::GetInstance().SetTimeScale(1);
	m_pPlayer->Update();
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
	m_pMap->Update();





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
	SetDrawScreen(DX_SCREEN_BACK);
	m_pCamera->Draw();
}
