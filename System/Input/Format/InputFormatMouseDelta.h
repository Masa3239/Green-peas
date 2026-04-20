#pragma once

#include "InputFormatBase.h"

class InputFormatMouseDelta : public InputFormatBase
{
public:

	InputFormatMouseDelta() = default;
	~InputFormatMouseDelta() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) override;

	const Vector2& GetValue(const KeyCode::Button keyCode) override;
};
