#include "Keyboard.h"
#include <DxLib.h>

Keyboard& Keyboard::GetInstance()
{
	static Keyboard instance;

	return instance;
}

void Keyboard::Update()
{
	GetHitKeyStateAll(mState);
}

bool Keyboard::IsDown(int keyCode)
{
	return mState[keyCode];
}
