#define NOMINMAX

#include "InputFormatMouseWheel.h"
#include <cmath>
#include "../System/Input/Mouse.h"
#include "../Utility/Vector3.h"

void InputFormatMouseWheel::Init()
{
	RegisterKeyCode(KeyCode::Button::MbWheelUp, 0);
	RegisterKeyCode(KeyCode::Button::MbWheelDown, 1);
	RegisterKeyCode(KeyCode::Button::MbWheelLeft, 2);
	RegisterKeyCode(KeyCode::Button::MbWheelRight, 3);
	RegisterKeyCode(KeyCode::Button::MbWheel, 4);
}

bool InputFormatMouseWheel::CheckButtonState(const KeyCode::Button keyCode)
{
	switch (keyCode)
	{
	case KeyCode::Button::MbWheelUp:		return Mouse::GetInstance().GetWheelRot().y > 0.0f;
	case KeyCode::Button::MbWheelDown:		return Mouse::GetInstance().GetWheelRot().y < 0.0f;
	case KeyCode::Button::MbWheelLeft:		return Mouse::GetInstance().GetWheelRot().x < 0.0f;
	case KeyCode::Button::MbWheelRight:		return Mouse::GetInstance().GetWheelRot().x > 0.0f;
	case KeyCode::Button::MbWheel:			return Mouse::GetInstance().GetWheelRot() != Vector2::zero;
	}

	return false;
}

Vector2 InputFormatMouseWheel::GetValue(const KeyCode::Button keyCode)
{
	switch (keyCode)
	{
	case KeyCode::Button::MbWheelUp:		return Vector2(std::max(Mouse::GetInstance().GetWheelRot().y, 0.0f), 0.0f);
	case KeyCode::Button::MbWheelDown:		return Vector2(std::min(Mouse::GetInstance().GetWheelRot().y, 0.0f), 0.0f);
	case KeyCode::Button::MbWheelLeft:		return Vector2(std::min(Mouse::GetInstance().GetWheelRot().x, 0.0f), 0.0f);
	case KeyCode::Button::MbWheelRight:		return Vector2(std::max(Mouse::GetInstance().GetWheelRot().x, 0.0f), 0.0f);
	case KeyCode::Button::MbWheel:			return Mouse::GetInstance().GetWheelRot();
	}

	return Vector2::zero;
}
