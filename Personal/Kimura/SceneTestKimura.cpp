#include "SceneTestKimura.h"
#include"Map/Map.h"
#include <DxLib.h>


SceneTestKimura::SceneTestKimura()
{
}

SceneTestKimura::~SceneTestKimura()
{
}

void SceneTestKimura::Init()
{
	m_map.Init();
	
}

void SceneTestKimura::End()
{
	m_map.End();
}

SceneBase* SceneTestKimura::Update()
{
	m_map.Update();
	return this;
}

void SceneTestKimura::Draw()
{
	m_map.Draw();
	printfDx("SceneTestKimura\n");
}
