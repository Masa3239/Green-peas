#include "SceneTestOsawa.h"
#include <DxLib.h>

SceneTestOsawa::SceneTestOsawa()
{
}

SceneTestOsawa::~SceneTestOsawa()
{
}

void SceneTestOsawa::Init()
{
}

void SceneTestOsawa::End()
{
}

SceneBase* SceneTestOsawa::Update()
{
	return this;
}

void SceneTestOsawa::Draw()
{
	printfDx("OsawaTestScene\n");
}
