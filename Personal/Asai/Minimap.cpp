#include "Minimap.h"

#include<DxLib.h>

#include"../../Utility/Game.h"

namespace {
	//ミニマップのサイズ
	int kSizeX = 100;
	int kSizeY = 100;
	//画面端からずらす大きさ
	int kOffSet = 15;

}

void Minimap::Init()
{
}

void Minimap::Update()
{
}

void Minimap::Draw()
{

	//DrawRectGraph(0, 0,
	//	-1, -1,
	//	kSizeX, kSizeX);

	DrawBox(Game::kScreenWidth - kSizeX - kOffSet, 0 + kOffSet, Game::kScreenWidth - kOffSet, 0 + kSizeY + kOffSet, 0xffffff, TRUE);

}

void Minimap::DebugDraw()
{
}

void Minimap::End()
{
}
