#include "Mouse.h"
#include <DxLib.h>

Mouse& Mouse::GetInstance()
{
	static Mouse instance;

	return instance;
}

void Mouse::Update()
{
	mState = GetMouseInput();
}

bool Mouse::IsDown(int keyCode)
{
	return mState & keyCode;
}
