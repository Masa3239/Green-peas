#include "DxLib.h"
#include "Input.h"

namespace {

	// 入力情報を保持する期間
	constexpr int kLogNum = 2;
	// 入力情報 0番目のデータが最新
	int inputLog[kLogNum];
}

namespace Input {

	void Update() {

		int inputState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		// 入力情報の更新
		inputLog[1] = inputLog[0];
		inputLog[0] = inputState;
	}

	bool IsDown(int key) {

		return (inputLog[0] & key);
	}

	bool IsPressed(int key) {

		// 現在の入力状況
		bool isNow = (inputLog[0] & key);
		// 1F前の入力状況
		bool isLast = (inputLog[1] & key);

		return (isNow && !isLast);

	}

	bool IsReleased(int key) {

		bool isNow = (inputLog[0] & key);
		bool isLast = (inputLog[1] & key);

		return (!isNow && isLast);
	}
}