#include "InputModifierConcurrent.h"
#include "../System/InputManager.h"
#include "../System/Input/Device/InputDeviceKeyboard.h"
#include "../System/Input/Device/InputDeviceMouse.h"
#include "../System/Input/Device/InputDeviceGamepad.h"

InputModifierConcurrent::InputModifierConcurrent(std::vector<KeyCode::Button> buttons) :
	mButtons(buttons)
{
}

void InputModifierConcurrent::ModifyRaw(Vector2* rawValue)
{
	for (const auto& keyCode : mButtons)
	{
		int castKeyCode = static_cast<int>(keyCode);
		// キーボードの場合
		if (castKeyCode >= static_cast<int>(KeyCode::Button::BackSpace) && castKeyCode <= static_cast<int>(KeyCode::Button::BackSlash))
		{
			if (!InputManager::GetInstance().GetDevice<InputDeviceKeyboard>()->IsDown(keyCode))
			{
				*rawValue = Vector2::zero;
				return;
			}
		}
		// マウスの場合
		if (castKeyCode >= static_cast<int>(KeyCode::Button::MbLeftClick) && castKeyCode <= static_cast<int>(KeyCode::Button::MbWheel))
		{
			if (!InputManager::GetInstance().GetDevice<InputDeviceMouse>()->IsDown(keyCode))
			{
				*rawValue = Vector2::zero;
				return;
			}
		}
		// ゲームパッドの場合
		if (castKeyCode >= static_cast<int>(KeyCode::Button::GpFaceUp) && castKeyCode <= static_cast<int>(KeyCode::Button::GpRightThumb))
		{
			if (!InputManager::GetInstance().GetDevice<InputDeviceGamepad>()->IsDown(keyCode))
			{
				*rawValue = Vector2::zero;
				return;
			}
		}
	}
}
