#pragma once

#include "IInputModifier.h"

/// <summary>
/// ’l‚ð“ü‚ê‘Ö‚¦‚é
/// </summary>
class InputModifierSwizzleAxis : public IInputModifier
{
public:

	InputModifierSwizzleAxis() = default;
	~InputModifierSwizzleAxis() = default;

	void ModifyRaw(Vector2* rawValue) override;
};
