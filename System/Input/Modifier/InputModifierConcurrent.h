#pragma once

#include "IInputModifier.h"
#include <vector>
#include "../System/Input/Literal/KeyCodes.h"

class InputModifierConcurrent : public IInputModifier
{
public:

	InputModifierConcurrent(std::vector<KeyCode::Button> buttons);
	~InputModifierConcurrent() = default;

	void ModifyRaw(Vector2* rawValue) override;

private:

	std::vector<KeyCode::Button> mButtons;
};
