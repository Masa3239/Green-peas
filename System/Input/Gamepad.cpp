#include "Gamepad.h"
#include <DxLib.h>
#include <cassert>

Gamepad& Gamepad::GetInstance()
{
	static Gamepad instance;

	return instance;
}

void Gamepad::Update()
{
	mConnectedNum = GetJoypadNum();

	for (int i = 0; i < mConnectedNum; i++)
	{
		GetJoypadXInputState(i + 1, &mState[i]);
	}
}

bool Gamepad::IsDown(int keyCode, Input::PadSlot slot)
{
	int s = static_cast<int>(slot);

	if (s > mConnectedNum)
	{
		assert(false && "接続されていないゲームパッドにアクセスしました");
		return false;
	}

	return mState[s].Buttons[keyCode];
}

Gamepad::Gamepad() :
	mState(),
	mConnectedNum(0)
{
	mState.fill(XINPUT_STATE());
}
