#include "SceneTestKimura.h"
#include"../Kimura/Map/Map.h"
#include <DxLib.h>


SceneTestKimura::SceneTestKimura():
	m_pMap(nullptr),
	m_pEnemymap(nullptr)
{
	m_pMap = new Map;
	m_pEnemymap = new EnemyMap;
}

SceneTestKimura::~SceneTestKimura()
{
}

void SceneTestKimura::Init()
{
	m_pMap->Init();
	m_pEnemymap->Init();
}

void SceneTestKimura::End()
{
	m_pMap->End(); 
	delete m_pMap;
	m_pMap = nullptr;

	m_pEnemymap->End();
	delete m_pEnemymap;
	m_pEnemymap = nullptr;

}

SceneBase* SceneTestKimura::Update()
{
	
	m_pMap->Update();
	m_pEnemymap->Update();
	return this;
}

void SceneTestKimura::Draw()
{
	m_pMap->Draw();
	m_pEnemymap->Draw();
	printfDx("SceneTestKimura\n");
}
