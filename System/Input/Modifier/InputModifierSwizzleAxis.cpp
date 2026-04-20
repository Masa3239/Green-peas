#include "InputModifierSwizzleAxis.h"

void InputModifierSwizzleAxis::ModifyRaw(Vector2* rawValue)
{
	Vector2 buf = *rawValue;

	rawValue->x = buf.y;
	rawValue->y = buf.x;
}
