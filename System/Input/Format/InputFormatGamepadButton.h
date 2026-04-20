#pragma once

#include "InputFormatBase.h"

class InputFormatGamepadButton : public InputFormatBase
{
public:

	InputFormatGamepadButton() = default;
	~InputFormatGamepadButton() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) override;

	const Vector2& GetValue(const KeyCode::Button keyCode) override;
};
