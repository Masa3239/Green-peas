#include "InputModifierNegate.h"

InputModifierNegate::InputModifierNegate(bool x, bool y) :
	IInputModifier(),
	mX(x),
	mY(y)
{
}

void InputModifierNegate::ModifyRaw(Vector2* rawValue)
{
	if (mX) rawValue->x *= -1;
	if (mY) rawValue->y *= -1;
}
