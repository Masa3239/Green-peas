#pragma once

#include "InputFormatBase.h"

class InputFormatGamepadButton : public InputFormatBase
{
public:

	InputFormatGamepadButton() = default;
	~InputFormatGamepadButton() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) override;

	Vector2 GetValue(const KeyCode::Button keyCode) override;
};
