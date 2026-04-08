#include "InputKey.h"
#include "DxLib.h"


// キーバッファ
namespace InputKey {

	bool downBuf[256];					// 押された瞬間をチェックするためのキーバッファ
	bool upBuf[256];					// 離された瞬間をチェックするためのキーバッファ
}

// 押された瞬間を調べる関数
int CheckDownKey(int keyCode) {

	// 戻り値用の変数を用意
	int result = 0;

	// 引数で指定されたキーの現在の状態を取得
	int keyState = CheckHitKey(keyCode);

	// 前回キーが押されておらず、かつ、現在キーが押されていたら
	if ((InputKey::downBuf[keyCode] == 0) && (keyState == 1)) {

		result = 1;
	}

	// 現在のキー状態をバッファに反映
	InputKey::downBuf[keyCode] = keyState;

	return result;
}

// 離された瞬間を調べる関数
int CheckUpKey(int keyCode) {

	// 戻り値用の変数を用意
	int result = 0;

	// 引数で指定されたキーの現在の状態を取得
	int keyState = CheckHitKey(keyCode);

	// 前回キーが押されていて、かつ、現在キーが押されていなかったら
	if ((InputKey::upBuf[keyCode] == 1) && (keyState == 0)) {

		result = 1;
	}

	// 現在のキー状態をバッファに反映
	InputKey::upBuf[keyCode] = keyState;

	return result;
}


