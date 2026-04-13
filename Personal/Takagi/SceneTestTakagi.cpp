#include "SceneTestTakagi.h"
#include <DxLib.h>
#include"../../Personal/Takagi/Player.h"

SceneTestTakagi::SceneTestTakagi()
{
	m_pPlayer = std::make_unique<Player>();
}

SceneTestTakagi::~SceneTestTakagi()
{
}

void SceneTestTakagi::Init()
{
	m_pPlayer->Init();
}

void SceneTestTakagi::End()
{
	m_pPlayer->End();

}

SceneBase* SceneTestTakagi::Update()
{
	m_pPlayer->Update();
	return this;
}

void SceneTestTakagi::Draw()
{
	printfDx("SceneTestTakagi\n");
	m_pPlayer->Draw();
}
