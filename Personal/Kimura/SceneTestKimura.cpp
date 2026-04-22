#include "SceneTestKimura.h"
#include"../Kimura/Map/Map.h"
#include <DxLib.h>


SceneTestKimura::SceneTestKimura():
	m_pMap(nullptr)
{
	m_pMap = new Map;
}

SceneTestKimura::~SceneTestKimura()
{
}

void SceneTestKimura::Init()
{
	m_pMap->Init();
}

void SceneTestKimura::End()
{
	m_pMap->End(); 
	delete m_pMap;
	m_pMap = nullptr;
}

SceneBase* SceneTestKimura::Update()
{
	
	m_pMap->Update();
	return this;
}

void SceneTestKimura::Draw()
{
	m_pMap->Draw();
	printfDx("SceneTestKimura\n");
}
