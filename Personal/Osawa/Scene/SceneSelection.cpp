#include "SceneSelection.h"
#include <DxLib.h>
#include "../Personal/Asai/SceneTestAsai.h"
#include "../Personal/Kimura/SceneTestKimura.h"
#include "../Personal/Osawa/Scene/SceneTestOsawa.h"
#include "../Personal/Osawa/Scene/SceneTestOBB.h"
#include "../Personal/Syoguti/SceneTestSyoguti.h"
#include "../Personal/Takagi/SceneTestTakagi.h"
#include "../Scene/SceneInGame.h"
#include "../Scene/SceneTitle.h"

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
	if (CheckHitKey(KEY_INPUT_1))
	{
		return new SceneTestAsai();
	}
	if (CheckHitKey(KEY_INPUT_2))
	{
		return new SceneTestKimura();
	}
	if (CheckHitKey(KEY_INPUT_3))
	{
		return new SceneTestOsawa();
	}
	if (CheckHitKey(KEY_INPUT_4))
	{
		return new SceneTestSyoguti();
	}
	if (CheckHitKey(KEY_INPUT_5))
	{
		return new SceneTestTakagi();
	}
	if (CheckHitKey(KEY_INPUT_6))
	{
		return new SceneInGame();
	}
	if (CheckHitKey(KEY_INPUT_7))
	{
		return new SceneTitle();
	}
	if (CheckHitKey(KEY_INPUT_G))
	{
		return new SceneTestOBB();
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
	printfDx("6 - InGame Scene (Main)\n");
	printfDx("7 - Title Scene\n");
	printfDx("G - OBB Test\n");
}
