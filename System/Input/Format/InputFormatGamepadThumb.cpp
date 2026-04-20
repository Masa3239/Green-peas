#include "InputFormatGamepadThumb.h"
#include <DxLib.h>
#include "../System/Input/Gamepad.h"
#include "../Utility/MyMath.h"
#include "../Utility/Vector3.h"

namespace
{
	float kDeadzoneMin = 0.125f;
	float kDeadzoneMax = 0.925f;
}

void InputFormatGamepadThumb::Init()
{
	RegisterKeyCode(KeyCode::Button::GpLeftThumbUp,		0);
	RegisterKeyCode(KeyCode::Button::GpLeftThumbDown,	1);
	RegisterKeyCode(KeyCode::Button::GpLeftThumbLeft,	2);
	RegisterKeyCode(KeyCode::Button::GpLeftThumbRight,	3);
	RegisterKeyCode(KeyCode::Button::GpRightThumbUp,	4);
	RegisterKeyCode(KeyCode::Button::GpRightThumbDown,	5);
	RegisterKeyCode(KeyCode::Button::GpRightThumbLeft,	6);
	RegisterKeyCode(KeyCode::Button::GpRightThumbRight,	7);
	RegisterKeyCode(KeyCode::Button::GpLeftThumb,		8);
	RegisterKeyCode(KeyCode::Button::GpRightThumb,		9);
}

bool InputFormatGamepadThumb::CheckButtonState(const KeyCode::Button keyCode)
{
	const XINPUT_STATE& state = Gamepad::GetInstance().GetState();

	switch (keyCode)
	{
	case KeyCode::Button::GpLeftThumbUp:		return MyMath::Filter1D(state.ThumbLY, 32767, kDeadzoneMin, kDeadzoneMax) > 0.0f;
	case KeyCode::Button::GpLeftThumbDown:		return MyMath::Filter1D(state.ThumbLY, 32767, kDeadzoneMin, kDeadzoneMax) < 0.0f;
	case KeyCode::Button::GpLeftThumbLeft:		return MyMath::Filter1D(state.ThumbLX, 32767, kDeadzoneMin, kDeadzoneMax) < 0.0f;
	case KeyCode::Button::GpLeftThumbRight:		return MyMath::Filter1D(state.ThumbLX, 32767, kDeadzoneMin, kDeadzoneMax) > 0.0f;
	case KeyCode::Button::GpRightThumbUp:		return MyMath::Filter1D(state.ThumbRY, 32767, kDeadzoneMin, kDeadzoneMax) > 0.0f;
	case KeyCode::Button::GpRightThumbDown:		return MyMath::Filter1D(state.ThumbRY, 32767, kDeadzoneMin, kDeadzoneMax) < 0.0f;
	case KeyCode::Button::GpRightThumbLeft:		return MyMath::Filter1D(state.ThumbRX, 32767, kDeadzoneMin, kDeadzoneMax) < 0.0f;
	case KeyCode::Button::GpRightThumbRight:	return MyMath::Filter1D(state.ThumbRX, 32767, kDeadzoneMin, kDeadzoneMax) > 0.0f;

	case KeyCode::Button::GpLeftThumb:			return MyMath::Filter2D(state.ThumbLX, state.ThumbLY, 32767, kDeadzoneMin, kDeadzoneMax) != Vector2::zero;
	case KeyCode::Button::GpRightThumb:			return MyMath::Filter2D(state.ThumbRX, state.ThumbRY, 32767, kDeadzoneMin, kDeadzoneMax) != Vector2::zero;
	}
	
	return false;
}

const Vector2& InputFormatGamepadThumb::GetValue(const KeyCode::Button keyCode)
{
	const XINPUT_STATE& state = Gamepad::GetInstance().GetState();

	switch (keyCode)
	{
	case KeyCode::Button::GpLeftThumbUp:		return Vector2(MyMath::Filter1D(state.ThumbLY, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f);
	case KeyCode::Button::GpLeftThumbDown:		return Vector2(MyMath::Filter1D(state.ThumbLY, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f);
	case KeyCode::Button::GpLeftThumbLeft:		return Vector2(MyMath::Filter1D(state.ThumbLX, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f);
	case KeyCode::Button::GpLeftThumbRight:		return Vector2(MyMath::Filter1D(state.ThumbLX, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f);
	case KeyCode::Button::GpRightThumbUp:		return Vector2(MyMath::Filter1D(state.ThumbRY, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f);
	case KeyCode::Button::GpRightThumbDown:		return Vector2(MyMath::Filter1D(state.ThumbRY, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f);
	case KeyCode::Button::GpRightThumbLeft:		return Vector2(MyMath::Filter1D(state.ThumbRX, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f);
	case KeyCode::Button::GpRightThumbRight:	return Vector2(MyMath::Filter1D(state.ThumbRX, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f);

	case KeyCode::Button::GpLeftThumb:			return MyMath::Filter2D(state.ThumbLX, state.ThumbLY, 32767, kDeadzoneMin, kDeadzoneMax);
	case KeyCode::Button::GpRightThumb:			return MyMath::Filter2D(state.ThumbRX, state.ThumbRY, 32767, kDeadzoneMin, kDeadzoneMax);
	}

	return Vector2::zero;
}
