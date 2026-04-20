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
	mWheelRot.x = GetMouseHWheelRotVolF();
	mWheelRot.y = GetMouseWheelRotVolF();

	UpdatePosition();

	// 相対座標モードならマウスカーソルを固定する
	if (mMode == Mode::Relative)
	{
		SetMousePoint(0, 0);
		mPosition = Vector2::zero;
	}
}

bool Mouse::IsDown(int keyCode)
{
	return mState & keyCode;
}

void Mouse::SetMode(Mode mode)
{
	mMode = mode;

	if (mode == Mode::Relative) SetMouseDispFlag(false);
	else SetMouseDispFlag(true);
}

Mouse::Mouse() :
	mState(0),
	mPosition(Vector2::zero),
	mRelative(Vector2::zero),
	mWheelRot(Vector2::zero),
	mMode(Mode::Absolute)
{
}

void Mouse::UpdatePosition()
{
	// マウスの座標を取得
	int x, y;
	GetMousePoint(&x, &y);
	Vector2 pos = Vector2(x, y);
	
	// 相対座標を更新
	mRelative = pos - mPosition;

	// 絶対座標を更新
	mPosition = pos;
}
