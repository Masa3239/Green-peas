#include "SceneTestTakagi.h"
#include <DxLib.h>
#include"../../Personal/Takagi/Player.h"
#include"../../Personal/Asai/Camera.h"

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
	return this;
}

void SceneTestTakagi::Draw()
{
	SetDrawScreen(m_pCamera->GetWorldScreen());
	ClearDrawScreen();
	printfDx("SceneTestTakagi\n");
	m_pPlayer->Draw();

	SetDrawScreen(DX_SCREEN_BACK);
	m_pCamera->Draw();
	m_pCamera->DebugDraw();
}
