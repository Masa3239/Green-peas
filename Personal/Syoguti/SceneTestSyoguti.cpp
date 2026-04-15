#include "SceneTestSyoguti.h"
#include <DxLib.h>

#include "ItemManager.h"
#include "EnemyBoss.h"
#include "../../Utility/Input.h"
#include "../../Utility/Transform.h"

namespace {

	constexpr float kTestPos = 100.0f;
}

SceneTestSyoguti::SceneTestSyoguti() :
	m_pItemMgr(nullptr),
	m_pEnemyBoss(nullptr),
	m_transform()
{
	m_transform.Reset();
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

	 m_transform.position.x = kTestPos;
	 m_transform.position.y = kTestPos;
}

void SceneTestSyoguti::End()
{
	m_pItemMgr->End();
	m_pEnemyBoss->End();
}

SceneBase* SceneTestSyoguti::Update()
{
	
	if (Input::IsPressed(PAD_INPUT_10)) {
		 m_pItemMgr->Create(ItemBase::ItemType::Heal, m_transform.position);
		 m_pItemMgr->Create(ItemBase::ItemType::Attack, m_transform.position);
	}
	return this;
}

void SceneTestSyoguti::Draw()
{
	m_pItemMgr->Draw();
	m_pEnemyBoss->Draw();
	printfDx("SceneTestSyoguti\n");
	printfDx("posX : %f\n", m_transform.position.x);
	printfDx("posY : %f\n", m_transform.position.x);
}
