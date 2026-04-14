#include "SceneTestSyoguti.h"
#include <DxLib.h>

#include "ItemManager.h"

SceneTestSyoguti::SceneTestSyoguti() :
	m_pItemMgr(nullptr)
{
}

SceneTestSyoguti::~SceneTestSyoguti()
{
}

void SceneTestSyoguti::Init()
{

	 m_pItemMgr = std::make_unique<ItemManager>();
	 m_pItemMgr->Init();
}

void SceneTestSyoguti::End()
{
	m_pItemMgr->End();
}

SceneBase* SceneTestSyoguti::Update()
{
	return this;
}

void SceneTestSyoguti::Draw()
{
	printfDx("SceneTestSyoguti\n");
}
