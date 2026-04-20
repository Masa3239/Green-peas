#include "InputFormatGamepadThumb.h"
#include <DxLib.h>
#include <algorithm>
#include <cmath>
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
	case KeyCode::Button::GpLeftThumbUp:		return Filter1D(state.ThumbLY) > 0.0f;
	case KeyCode::Button::GpLeftThumbDown:		return Filter1D(state.ThumbLY) < 0.0f;
	case KeyCode::Button::GpLeftThumbLeft:		return Filter1D(state.ThumbLX) < 0.0f;
	case KeyCode::Button::GpLeftThumbRight:		return Filter1D(state.ThumbLX) > 0.0f;
	case KeyCode::Button::GpRightThumbUp:		return Filter1D(state.ThumbRY) > 0.0f;
	case KeyCode::Button::GpRightThumbDown:		return Filter1D(state.ThumbRY) < 0.0f;
	case KeyCode::Button::GpRightThumbLeft:		return Filter1D(state.ThumbRX) < 0.0f;
	case KeyCode::Button::GpRightThumbRight:	return Filter1D(state.ThumbRX) > 0.0f;

	case KeyCode::Button::GpLeftThumb:			return Filter2D(state.ThumbLX, state.ThumbLY) != Vector2::zero;
	case KeyCode::Button::GpRightThumb:			return Filter2D(state.ThumbRX, state.ThumbRY) != Vector2::zero;
	}
	
	return false;
}

Vector2 InputFormatGamepadThumb::GetValue(const KeyCode::Button keyCode)
{
	const XINPUT_STATE& state = Gamepad::GetInstance().GetState();

	switch (keyCode)
	{
	case KeyCode::Button::GpLeftThumbUp:		return Vector2(Filter1D(state.ThumbLY), 0.0f);
	case KeyCode::Button::GpLeftThumbDown:		return Vector2(Filter1D(state.ThumbLY), 0.0f);
	case KeyCode::Button::GpLeftThumbLeft:		return Vector2(Filter1D(state.ThumbLX), 0.0f);
	case KeyCode::Button::GpLeftThumbRight:		return Vector2(Filter1D(state.ThumbLX), 0.0f);
	case KeyCode::Button::GpRightThumbUp:		return Vector2(Filter1D(state.ThumbRY), 0.0f);
	case KeyCode::Button::GpRightThumbDown:		return Vector2(Filter1D(state.ThumbRY), 0.0f);
	case KeyCode::Button::GpRightThumbLeft:		return Vector2(Filter1D(state.ThumbRX), 0.0f);
	case KeyCode::Button::GpRightThumbRight:	return Vector2(Filter1D(state.ThumbRX), 0.0f);

	case KeyCode::Button::GpLeftThumb:			return Filter2D(state.ThumbLX, state.ThumbLY);
	case KeyCode::Button::GpRightThumb:			return Filter2D(state.ThumbRX, state.ThumbRY);
	}

	return Vector2::zero;
}

float InputFormatGamepadThumb::Filter1D(int axis)
{
	// デッドゾーンを32767の割合に変換
	const int dzMin = 32767 * kDeadzoneMin;
	const int dzMax = 32767 * kDeadzoneMax;

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

Vector2 InputFormatGamepadThumb::Filter2D(int axisX, int axisY)
{
	// デッドゾーンを32767の割合に変換
	const int dzMin = 32767 * kDeadzoneMin;
	const int dzMax = 32767 * kDeadzoneMax;

	// ベクトルに変換
	const Vector2 dir = Vector2(axisX, axisY);

	const float len = dir.GetLength();

	Vector2 result = Vector2::zero;

	// デッドゾーンより小さい入力なら0とする
	if (len < dzMin) return result;

	// デッドゾーンの最小値と最大値の間の割合を取得する
	float rate = static_cast<float>(len - dzMin) / static_cast<float>(dzMax - dzMin);

	// 値を0から1に収める
	rate = std::clamp(rate, 0.0f, 1.0f);

	// スケーリング
	result = dir * (rate / len);

	return result;
}
