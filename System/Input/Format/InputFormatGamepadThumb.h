#pragma once

#include "InputFormatBase.h"
#include <DxLib.h>
#include "../System/Input/Gamepad.h"

struct Vector2;

class InputFormatGamepadThumb : public InputFormatBase
{
public:

	InputFormatGamepadThumb() = default;
	~InputFormatGamepadThumb() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) override;

	Vector2 GetValue(const KeyCode::Button keyCode) override;

private:

	/// <summary>
	/// 1D軸の値をデッドゾーン内の割合にフィルタリングする
	/// </summary>
	float Filter1D(int axis);
	
	/// <summary>
	/// 2D軸の値をデッドゾーン内の割合にフィルタリングする
	/// </summary>
	Vector2 Filter2D(int axisX, int axisY);
};
