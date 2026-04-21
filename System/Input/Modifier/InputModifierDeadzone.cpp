#include "InputModifierDeadzone.h"
#include "../Utility/MyMath.h"

namespace
{
	constexpr float kDefaultDeadzoneMin = 0.125f;
	constexpr float kDefaultDeadzoneMax = 0.925f;
}

InputModifierDeadzone::InputModifierDeadzone() :
	mDeadzoneMin(kDefaultDeadzoneMin),
	mDeadzoneMax(kDefaultDeadzoneMax)
{
}

InputModifierDeadzone::InputModifierDeadzone(float dzMin, float dzMax) :
	mDeadzoneMin(dzMin),
	mDeadzoneMax(dzMax)
{
}

void InputModifierDeadzone::ModifyRaw(Vector2* rawValue)
{
	*rawValue = MyMath::Filter2D(rawValue->x, rawValue->y, 1.0f, mDeadzoneMin, mDeadzoneMax);
}
