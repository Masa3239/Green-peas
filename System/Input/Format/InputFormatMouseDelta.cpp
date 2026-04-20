#define NOMINMAX

#include "InputFormatMouseDelta.h"
#include <cmath>
#include "../System/Input/Mouse.h"
#include "../Utility/Vector3.h"

void InputFormatMouseDelta::Init()
{
	RegisterKeyCode(KeyCode::Button::MbDeltaUp, 0);
	RegisterKeyCode(KeyCode::Button::MbDeltaDown, 1);
	RegisterKeyCode(KeyCode::Button::MbDeltaLeft, 2);
	RegisterKeyCode(KeyCode::Button::MbDeltaRight, 3);
	RegisterKeyCode(KeyCode::Button::MbDelta, 4);
}

bool InputFormatMouseDelta::CheckButtonState(const KeyCode::Button keyCode)
{
	switch (keyCode)
	{
	case KeyCode::Button::MbDeltaUp:		return Mouse::GetInstance().GetRelative().y < 0.0f;
	case KeyCode::Button::MbDeltaDown:		return Mouse::GetInstance().GetRelative().y > 0.0f;
	case KeyCode::Button::MbDeltaLeft:		return Mouse::GetInstance().GetRelative().x < 0.0f;
	case KeyCode::Button::MbDeltaRight:		return Mouse::GetInstance().GetRelative().x > 0.0f;
	case KeyCode::Button::MbDelta:			return Mouse::GetInstance().GetRelative() != Vector2::zero;
	}

	return false;
}

Vector2 InputFormatMouseDelta::GetValue(const KeyCode::Button keyCode)
{
	switch (keyCode)
	{
	case KeyCode::Button::MbDeltaUp:		return Vector2(std::min(Mouse::GetInstance().GetRelative().y, 0.0f), 0.0f);
	case KeyCode::Button::MbDeltaDown:		return Vector2(std::max(Mouse::GetInstance().GetRelative().y, 0.0f), 0.0f);
	case KeyCode::Button::MbDeltaLeft:		return Vector2(std::min(Mouse::GetInstance().GetRelative().x, 0.0f), 0.0f);
	case KeyCode::Button::MbDeltaRight:		return Vector2(std::max(Mouse::GetInstance().GetRelative().x, 0.0f), 0.0f);
	case KeyCode::Button::MbDelta:			return Mouse::GetInstance().GetRelative();
	}

	return Vector2::zero;
}
