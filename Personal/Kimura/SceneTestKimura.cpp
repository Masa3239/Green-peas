#include "SceneTestKimura.h"
#include <DxLib.h>

SceneTestKimura::SceneTestKimura()
{
}

SceneTestKimura::~SceneTestKimura()
{
}

void SceneTestKimura::Init()
{
}

void SceneTestKimura::End()
{
}

SceneBase* SceneTestKimura::Update()
{
	return this;
}

void SceneTestKimura::Draw()
{
	printfDx("SceneTestKimura\n");
}
