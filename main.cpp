#include "Literal.h"
#include "DxLib.h"
#include "InputKey.h"

//========================================================
// プロトタイプ宣言
//========================================================
void AppInit();
void AppProc();
void MainProc();
void MainDraw();

//========================================================
// グローバル変数宣言
//========================================================

// FPSチェック用の変数を用意
int time;
int elapsedTime = 16;			// とりあえず60FPS想定

//========================================================
// WinMain関数　ここからプログラムが始まる
//========================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	// ウィンドウのサイズを指定
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT,WINDOW_COLORBIT);

	// ウィンドウモードで起動
	ChangeWindowMode(true);

	if (DxLib_Init() == -1) {	// DXライブラリ初期化処理

		return -1;				// 初期化に失敗したら強制終了
	}

	// プログラムの初期化
	AppInit();

	// プログラムの処理
	AppProc();

	DxLib_End();				// DXライブラリの終了処理
	return 0;					// ソフトの終了 
}

//========================================================
// 関数の定義
//========================================================

// プログラムの初期化
void AppInit() {

	// 描画先を裏面にセット
	SetDrawScreen(DX_SCREEN_BACK);
}

// プログラムの処理
void AppProc() {

	// プログラムの処理
	// メインループ
	while (ProcessMessage() == 0) {

		time = GetNowCount();	// 現在のカウントを取得

		ClearDrawScreen();		// 画面の初期化
		clsDx();				// デバッグ文字の初期化

		// メインループの処理
		MainProc();

		// メインループの描画
		MainDraw();

		// 描画先を切り替える
		ScreenFlip();			

		// FPS調整
		// 1フレームあたりの経過時間が経過するため待機
		while (GetNowCount() - time < elapsedTime) {

		}
	}

}

// ゲームループの処理
void MainProc() {

}

// ゲームループの描画
void MainDraw() {

}

