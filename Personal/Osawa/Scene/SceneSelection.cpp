#include "SceneSelection.h"
#include <DxLib.h>
#include "SceneTestOsawa.h"

SceneSelection::SceneSelection()
{
}

SceneSelection::~SceneSelection()
{
}

void SceneSelection::Init()
{
}

void SceneSelection::End()
{
}

SceneBase* SceneSelection::Update()
{
	if (CheckHitKey(KEY_INPUT_3))
	{
		return new SceneTestOsawa();
	}

	return this;
}

void SceneSelection::Draw()
{
	printfDx("1 - Asai Scene\n");
	printfDx("2 - Kimura Scene\n");
	printfDx("3 - Osawa Scene\n");
	printfDx("4 - Syoguti Scene\n");
	printfDx("5 - Takagi Scene\n");
}
