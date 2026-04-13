#include "GameSetting.h"

#include <DxLib.h>
#include "Game.h"

void GameSetting::InitWindow()
{
	// ウィンドウ名を設定
	SetMainWindowText(Game::kWindowText);

	// ウィンドウサイズを指定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorBit);

	// ウィンドウモードで起動
	ChangeWindowMode(Game::kWindowMode);

}

void GameSetting::InitDxLib3D()
{
	// Zバッファを使用する
	SetUseZBuffer3D(true);
	// Zバッファへの書き込みを行う
	SetWriteZBuffer3D(true);
	// ポリゴンの裏面を描画しない
	SetUseBackCulling(true);

	// 確認用に背景色を設定
	SetBackgroundColor(112, 128, 128);
}

