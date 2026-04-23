#include "SceneTitle.h"
#include <DxLib.h>
#include "../System/Input/Keyboard.h"
#include "../Personal/Osawa/Scene/SceneSelection.h"

SceneTitle::SceneTitle()
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
}

void SceneTitle::End()
{
}

SceneBase* SceneTitle::Update()
{
	if (Keyboard::GetInstance().IsDown(KEY_INPUT_R))
	{
		return new SceneSelection();
	}

	return this;
}

void SceneTitle::Draw()
{
	printfDx("TITLE SCENE");
}
