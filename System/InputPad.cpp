#include"../Utility/Vector3.h"
#include<math.h>
#include"InputPad.h"
#include"../Utility/MyMath.h"
//#include<vector>

// 無名名前空間
// この中で宣言された物は同じソースファイルの中でしか扱うことができない
// 外部からのアクセスができない
namespace {

	// 入力を保存する期間
	constexpr int kLogNum = 60;
	// コントローラーの最大個数
	constexpr int kPadNum = static_cast<int>(Pad::Player::Max);

	// 長押ししていると判定する時間
	constexpr int HoldTime = 30;

	// レバーを倒した角度
	float analogAngle[static_cast<int>(Pad::Joystick::Max)];
	// レバーを倒した量
	float analogAmount[static_cast<int>(Pad::Joystick::Max)][kLogNum];
	// 前回の更新時の入力角度
	float analogAngleOld[static_cast<int>(Pad::Joystick::Max)];

	// レバーを倒した量の最大の値
	constexpr float analogMax = 26213;
	// 入力したと判定する値
	constexpr float analogMin = 0.4f;	// スティックを倒した割合
	constexpr int trrgerInput = 75;		// トリガーを倒した量

	// 入力情報
	tagXINPUT_STATE ButtonsLog[kPadNum][kLogNum];

	/// <summary>
	/// 接続されているコントローラーの数
	/// </summary>
	int padNum;

}


namespace Pad {



	void Init()
	{
		// コントローラーの数を取得
		padNum = GetJoypadNum();
	}

	void Update() {
		//XINPUT_BUTTON_A;
		// 入力情報の更新
		// 
		for (int i = 0; i < padNum; i++) {

			// ボタンの数だけ繰り返し
			for (int j = 0; j < kLogNum - 1; j++) {
				// ボタンの入力状況の更新
				ButtonsLog[i][kLogNum - (j + 1)] = ButtonsLog[i][kLogNum - (j + 2)];
			}
			int pad = 0;
			switch (i)
			{
				case 0:
					pad = DX_INPUT_PAD1;
					break;
				case 1:
					pad = DX_INPUT_PAD2;
				case 2:
					pad = DX_INPUT_PAD3;
				case 3:
					pad = DX_INPUT_PAD4;
					break;
			default:
				break;
			}
			// コントローラーの入力状況を保存
			GetJoypadXInputState(pad, &ButtonsLog[i][0]);
		}

	}

	bool IsDown(Pad::Button key, const Pad::Player padNum) {
		
		// トリガーの場合は倒した割合でとる
		if (key == Pad::Button::RT) {
			// 一定量倒していたら
			return (ButtonsLog[static_cast<int>(padNum)][0].RightTrigger > trrgerInput);
		}
		if (key == Pad::Button::LT) {
			// 一定量倒していたら
			return (ButtonsLog[static_cast<int>(padNum)][0].LeftTrigger > trrgerInput);
		}


		// 指定したボタンを押していたらtrue
		return (ButtonsLog[static_cast<int>(padNum)][0].Buttons[static_cast<int>(key)]);
	}

	bool IsPressed(Pad::Button key, const Pad::Player padNum) {

		// 現在の入力情報
		bool isNow = static_cast<bool>(ButtonsLog[static_cast<int>(padNum)][0].Buttons[static_cast<int>(key)]);
		// 1回前の入力情報
		bool isLast = static_cast<bool>(ButtonsLog[static_cast<int>(padNum)][1].Buttons[static_cast<int>(key)]);

		// トリガーの場合は割合でとる
		if (key == Pad::Button::RT) {
			return (ButtonsLog[static_cast<int>(padNum)][0].RightTrigger > trrgerInput &&
				ButtonsLog[static_cast<int>(padNum)][1].RightTrigger < trrgerInput);
		}
		if (key == Pad::Button::LT) {
			return (ButtonsLog[static_cast<int>(padNum)][0].LeftTrigger > trrgerInput &&
				ButtonsLog[static_cast<int>(padNum)][1].LeftTrigger < trrgerInput);
		}



		// 今回の入力があり、前回の入力がなければ
		return (isNow && !isLast);

	}

	bool IsReleased(Pad::Button key, const Pad::Player padNum) {

		// 現在の入力情報
		bool isNow = (ButtonsLog[static_cast<int>(padNum)][0].Buttons[static_cast<int>(key)]);
		// 1回前の入力情報
		bool isLast = (ButtonsLog[static_cast<int>(padNum)][1].Buttons[static_cast<int>(key)]);
		// トリガーの場合は割合でとる
		if (key == Pad::Button::RT) {
			// 前回の更新時に押していて現在の更新時は押されていない場合true
			return (ButtonsLog[static_cast<int>(padNum)][1].RightTrigger > trrgerInput &&
				ButtonsLog[static_cast<int>(padNum)][0].RightTrigger < trrgerInput);
		}
		if (key == Pad::Button::LT) {
			// 前回の更新時に押していて現在の更新時は押されていない場合true
			return (ButtonsLog[static_cast<int>(padNum)][1].LeftTrigger > trrgerInput &&
				ButtonsLog[static_cast<int>(padNum)][0].LeftTrigger < trrgerInput);
		}
		// 前回の入力があり、今回の入力か無い場合true
		return (!isNow && isLast);

	}

	// 長押しを判定する関数
	bool Hold(Pad::Button key, const Pad::Player padNum) {

		for (int i = 0; i < HoldTime; i++) {
			// 押してたらスキップ
			if (ButtonsLog[static_cast<int>(padNum)][i].Buttons[static_cast<int>(key)])continue;
			// 長押ししていない判定
			return false;
		}

		// 長押ししている判定
		return true;
	}

	// コントローラーのアナログのレバー入力を調べる

	// レバーの角度
	float AnalogAngle(Pad::Joystick stick, const Pad::Player padNum) {
		int Stick = static_cast<int>(stick);
		// 入力量を保存する変数を用意
		Vector3 checkVec;
		// 左右上下の入力量を取得
		if (stick == Pad::Joystick::Right) {
			checkVec.x = (ButtonsLog[static_cast<int>(padNum)][0].ThumbRX);
			checkVec.y = (ButtonsLog[static_cast<int>(padNum)][0].ThumbRY);
		}
		else {
			checkVec.x = (ButtonsLog[static_cast<int>(padNum)][0].ThumbLX);
			checkVec.y = (ButtonsLog[static_cast<int>(padNum)][0].ThumbLY);
		}
		// Zはないので0
		checkVec.z = 0;

		// 入力量が0なら0度を返す
		if (!PadAnalogAmount(stick,padNum))return analogAngleOld[Stick];
		// 入力量から角度を調べる
		analogAngle[Stick] = atan2(checkVec.x, checkVec.y);
		// デグリー角に変換する
		analogAngle[Stick] = MyMath::RadToDeg(analogAngle[Stick]);
		analogAngleOld[Stick] = analogAngle[Stick];

		// 角度を返す
		return analogAngle[Stick];
	}

	// レバーの入力量
	float PadAnalogAmount(Pad::Joystick stick, const Pad::Player padNum) {
		int Stick = static_cast<int>(stick);
		// 入力量を保存する変数を用意
		Vector3 checkVec;
		// 左右上下の入力量を取得
		if (stick == Pad::Joystick::Right) {
			checkVec.x = (ButtonsLog[static_cast<int>(padNum)][0].ThumbRX);
			checkVec.y = (ButtonsLog[static_cast<int>(padNum)][0].ThumbRY);
		}
		else {
			checkVec.x = (ButtonsLog[static_cast<int>(padNum)][0].ThumbLX);
			checkVec.y = (ButtonsLog[static_cast<int>(padNum)][0].ThumbLY);
		}
		// Zはないので0
		checkVec.z = 0;

		// 入力ベクトルの更新
		Vector3 inputVec = { checkVec.x, checkVec.y, 0.0f };
		// 入力量を一定の値域内に収める
		analogAmount[Stick][0] = MyMath::Clamp((inputVec.GetLength()), -analogMax, analogMax);
		// 入力量の割合を求める
		analogAmount[Stick][0] = MyMath::Rate(analogAmount[Stick][0], analogMax);
		if (analogAmount[Stick][0] < analogMin) {
			analogAmount[Stick][0] = 0;
		}


		return analogAmount[Stick][0];
	}

	MyMath::FourDirection AnalogDirection(const Pad::Joystick stick, const Pad::Player padNum)
	{
		// 入力されていない判定ならどの方向も返さない
		if (!PadAnalogAmount(stick, padNum))return MyMath::FourDirection::Max;
		float angle = AnalogAngle(stick, padNum);
		return MyMath::Direction(angle * MyMath::ToRadian);

	}

	void Debug() {
		// 画面に XINPUT_STATE の中身を描画
		int Color = GetColor(255, 255, 255);
		for (int i = 0; i < static_cast<int>(Pad::Player::Max); i++) {
		DrawFormatString(0, 184, Color, "ThumbLX:%d度 ThumbLX:%d",
			ButtonsLog[i][0].ThumbLX, ButtonsLog[i][0].ThumbLY);
		DrawFormatString(0, 200, Color, "LeftTrigger:%d RightTrigger:%d",
			ButtonsLog[i][0].LeftTrigger, ButtonsLog[i][0].RightTrigger);
		DrawFormatString(0, 216, Color, "ThumbLX:%d ThumbLY:%d",
			ButtonsLog[i][0].ThumbLX, ButtonsLog[i][0].ThumbLY);
		DrawFormatString(0, 232, Color, "ThumbRX:%d ThumbRY:%d",
			ButtonsLog[i][0].ThumbRX, ButtonsLog[i][0].ThumbRY);
		DrawString(0, 264, "Button", Color);
		for (int j = 0; j < 16; j++)
		{
			DrawFormatString(64 + j % 8 * 64, 64 + j / 8 * 16 + 200, Color,
				"%2d:%d", j, ButtonsLog[i][0].Buttons[j]);
		}
		}

	}

}

