#include "SceneTestTakagi.h"
#include <DxLib.h>
#include"../../Personal/Takagi/Player.h"
#include"../../Personal/Asai/Camera.h"
#include"../../Personal/Osawa/Scene/SceneSelection.h"
#include"../../Chara/Collision.h"
namespace {
	Vector3 kBoxPos = { 200,200 ,0 };
	Vector3 kBoxSize = { 50,70 ,0 };
	Collision::AABB box = Collision::AABB(kBoxPos, kBoxSize);
}

SceneTestTakagi::SceneTestTakagi()
{
	m_pPlayer = std::make_unique<Player>();
	m_pCamera = std::make_unique<Camera>();
	
}

SceneTestTakagi::~SceneTestTakagi()
{
}

void SceneTestTakagi::Init()
{
	m_pPlayer->Init();
	m_pCamera->Init();
	m_pPlayer->SetCamera(m_pCamera.get());
}

void SceneTestTakagi::End()
{
	m_pPlayer->End();
	m_pCamera->End();

}

SceneBase* SceneTestTakagi::Update()
{
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







	return this;
}

void SceneTestTakagi::Draw()
{
	SetDrawScreen(m_pCamera->GetWorldScreen());
	ClearDrawScreen();
	printfDx("SceneTestTakagi\n");
	m_pPlayer->Draw();
	box.DebugDraw();

	SetDrawScreen(DX_SCREEN_BACK);
	m_pCamera->Draw();
	//m_pCamera->DebugDraw();
}
