#pragma once

#include "InputFormatBase.h"

class InputFormatGamepadTrigger : public InputFormatBase
{
public:

	InputFormatGamepadTrigger() = default;
	~InputFormatGamepadTrigger() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) override;

	const Vector2& GetValue(const KeyCode::Button keyCode) override;
};
