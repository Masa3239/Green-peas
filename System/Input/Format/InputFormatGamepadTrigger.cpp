#include "InputFormatGamepadTrigger.h"
#include <DxLib.h>
#include <algorithm>
#include <cmath>
#include "../System/Input/Gamepad.h"
#include "../Utility/MyMath.h"

namespace
{
	float kDeadzoneMin = 0.125f;
	float kDeadzoneMax = 0.925f;
}

void InputFormatGamepadTrigger::Init()
{
	RegisterKeyCode(KeyCode::Button::GpLeftTrigger,		0);
	RegisterKeyCode(KeyCode::Button::GpRightTrigger,	1);
}

bool InputFormatGamepadTrigger::CheckButtonState(const KeyCode::Button keyCode)
{ 
	switch (keyCode)
	{
	case KeyCode::Button::GpLeftTrigger:	return Filter1D(Gamepad::GetInstance().GetState().LeftTrigger) > 0.0f;
	case KeyCode::Button::GpRightTrigger:	return Filter1D(Gamepad::GetInstance().GetState().RightTrigger) > 0.0f;
	}
	
	return false;
}

Vector2 InputFormatGamepadTrigger::GetValue(const KeyCode::Button keyCode)
{
	switch (keyCode)
	{
	case KeyCode::Button::GpLeftTrigger:	return Vector2(Filter1D(Gamepad::GetInstance().GetState().LeftTrigger), 0.0f);
	case KeyCode::Button::GpRightTrigger:	return Vector2(Filter1D(Gamepad::GetInstance().GetState().RightTrigger), 0.0f);
	}

	return Vector2::zero;
}

float InputFormatGamepadTrigger::Filter1D(int axis)
{
	// デッドゾーンを255の割合に変換
	const int dzMin = 255 * kDeadzoneMin;
	const int dzMax = 255 * kDeadzoneMax;

	// 計算しやすくするために絶対値を取得する
	const int absAxis = std::abs(axis);

	float result = 0.0f;

	// デッドゾーンより小さい入力なら0とする
	if (absAxis < dzMin) return result;

	// デッドゾーンの最小値と最大値の間の割合を取得する
	result = static_cast<float>(absAxis - dzMin) / static_cast<float>(dzMax - dzMin);

	// 符号を復元する
	result *= MyMath::Sign(axis);

	// 値を-1から1に収める
	result = std::clamp(result, -1.0f, 1.0f);

	return result;
}
