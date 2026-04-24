#define NOMINMAX

#include "InputManager.h"
#include <cmath>
#include <memory>
#include "../System/Input/Keyboard.h"
#include "../System/Input/Mouse.h"
#include "../System/Input/Gamepad.h"
#include "../System/Input/Device/InputDeviceKeyboard.h"
#include "../System/Input/Device/InputDeviceMouse.h"
#include "../System/Input/Device/InputDeviceGamepad.h"
#include "../System/Input/Literal/InputProperty.h"
#include "../System/Input/Literal/InputActions.h"
#include "../System/Input/Modifier/InputModifierDeadzone.h"
#include "../System/Input/Modifier/InputModifierNegate.h"
#include "../System/Input/Modifier/InputModifierSwizzleAxis.h"
#include "../System/Input/Modifier/InputModifierConcurrent.h"
#include "../Utility/MyMath.h"
#include "../Utility/Vector3.h"

InputManager& InputManager::GetInstance()
{
	static InputManager instance;
	
	return instance;
}

bool InputManager::Initialize()
{
	// 入力デバイスを登録
	RegisterDevice<InputDeviceKeyboard>(Input::Device::Keyboard);
	RegisterDevice<InputDeviceMouse>(Input::Device::Mouse);
	RegisterDevice<InputDeviceGamepad>(Input::Device::Gamepad);

	// アクションデータを初期化
	for (int i = 0; i < static_cast<int>(Input::Action::Length); i++)
	{
		mActions.emplace(static_cast<Input::Action>(i), Input::ActionProperty());
	}

	Bind(Input::Action::Up, Input::Device::Keyboard, KeyCode::Button::UpArrow);
	Bind(Input::Action::Down, Input::Device::Keyboard, KeyCode::Button::DownArrow);
	Bind(Input::Action::Left, Input::Device::Keyboard, KeyCode::Button::LeftArrow);
	Bind(Input::Action::Right, Input::Device::Keyboard, KeyCode::Button::RightArrow);
	Bind(Input::Action::Up, Input::Device::Gamepad, KeyCode::Button::GpDPadUp);
	Bind(Input::Action::Down, Input::Device::Gamepad, KeyCode::Button::GpDPadDown);
	Bind(Input::Action::Left, Input::Device::Gamepad, KeyCode::Button::GpDPadLeft);
	Bind(Input::Action::Right, Input::Device::Gamepad, KeyCode::Button::GpDPadRight);
	Bind(Input::Action::Up, Input::Device::Gamepad, KeyCode::Button::GpLeftThumbUp);
	Bind(Input::Action::Down, Input::Device::Gamepad, KeyCode::Button::GpLeftThumbDown);
	Bind(Input::Action::Left, Input::Device::Gamepad, KeyCode::Button::GpLeftThumbLeft);
	Bind(Input::Action::Right, Input::Device::Gamepad, KeyCode::Button::GpLeftThumbRight);

	Bind(Input::Action::Move, Input::Device::Gamepad, KeyCode::Button::GpLeftThumb,
		{
			std::make_shared<InputModifierNegate>(false, true),
		});
	Bind(Input::Action::Move, Input::Device::Keyboard, KeyCode::Button::W,
		{
			std::make_shared<InputModifierNegate>(true, true),
			std::make_shared<InputModifierSwizzleAxis>()
		});
	Bind(Input::Action::Move, Input::Device::Keyboard, KeyCode::Button::S,
		{
			std::make_shared<InputModifierSwizzleAxis>()
		});
	Bind(Input::Action::Move, Input::Device::Keyboard, KeyCode::Button::A,
		{
			std::make_shared<InputModifierNegate>(true, true)
		});
	Bind(Input::Action::Move, Input::Device::Keyboard, KeyCode::Button::D);

	Bind(Input::Action::Dash, Input::Device::Keyboard, KeyCode::Button::LShift);
	Bind(Input::Action::Dash, Input::Device::Gamepad, KeyCode::Button::GpFaceDown);

	Bind(Input::Action::Attack, Input::Device::Mouse, KeyCode::Button::MbLeftClick);
	Bind(Input::Action::Attack, Input::Device::Gamepad, KeyCode::Button::GpFaceLeft);
	
	Bind(Input::Action::PickUp, Input::Device::Keyboard, KeyCode::Button::F);
	Bind(Input::Action::PickUp, Input::Device::Gamepad, KeyCode::Button::GpFaceRight);

	Bind(Input::Action::Weapon, Input::Device::Keyboard, KeyCode::Button::Q);
	Bind(Input::Action::Weapon, Input::Device::Gamepad, KeyCode::Button::GpFaceUp);

	//Bind(Input::Action::Anger1, Input::Device::Gamepad, KeyCode::Button::GpLeftTrigger);
	Bind(Input::Action::Anger2, Input::Device::Gamepad, KeyCode::Button::GpRightTrigger);
	Bind(Input::Action::Anger3, Input::Device::Gamepad, KeyCode::Button::GpRightShoulder);
	Bind(Input::Action::Anger4, Input::Device::Gamepad, KeyCode::Button::GpLeftShoulder);

	Bind(Input::Action::Anger1, Input::Device::Gamepad, KeyCode::Button::GpLeftTrigger,
		{
			std::make_shared<InputModifierConcurrent>(std::vector
				{ KeyCode::Button::GpRightTrigger, KeyCode::Button::GpLeftShoulder, KeyCode::Button::GpRightShoulder }
			)
		}
	);
	Bind(Input::Action::Anger1, Input::Device::Keyboard, KeyCode::Button::LControl,
		{ std::make_shared<InputModifierConcurrent>(std::vector{ KeyCode::Button::Space })
		});

	Bind(Input::Action::Pause, Input::Device::Keyboard, KeyCode::Button::Escape);
	Bind(Input::Action::Pause, Input::Device::Gamepad, KeyCode::Button::GpStart);

	Bind(Input::Action::Confirm, Input::Device::Keyboard, KeyCode::Button::F);
	Bind(Input::Action::Confirm, Input::Device::Mouse, KeyCode::Button::MbLeftClick);
	Bind(Input::Action::Confirm, Input::Device::Gamepad, KeyCode::Button::GpFaceRight);

	Bind(Input::Action::Cancel, Input::Device::Keyboard, KeyCode::Button::LShift);
	Bind(Input::Action::Cancel, Input::Device::Gamepad, KeyCode::Button::GpFaceDown);

	return true;
}

void InputManager::Finalize()
{
}

void InputManager::Update()
{
	Keyboard::GetInstance().Update();
	Mouse::GetInstance().Update();
	Gamepad::GetInstance().Update();

	for (const auto& device : mDevices)
	{
		device.second->Update();
	}
}

bool InputManager::IsDown(Input::Action action) const
{
	return GetState(action, InputType::Down);
}

bool InputManager::IsPressed(Input::Action action) const
{
	return GetState(action, InputType::Pressed);
}

bool InputManager::IsReleased(Input::Action action) const
{
	return GetState(action, InputType::Released);
}

bool InputManager::IsHeld(Input::Action action, int frame) const
{
	return GetState(action, InputType::Held, frame);
}

bool InputManager::GetAsBool(Input::Action action) const
{
	const Input::ActionProperty& actionProperty = mActions.at(action);

	bool result = false;

	// アクションに割り当てられたボタンをすべてチェックする
	for (const auto& bind : actionProperty.binds)
	{
		auto device = mDevices.at(bind.device).get();
		
		// 値を取得する
		Vector2 value = device->GetValue(bind.keyCode);

		// バインドに割り当てられた加工をする
		for (const auto& modifier : bind.modifiers)
		{
			modifier->ModifyRaw(&value);
		}
		
		// 一度trueにしたらfalseにならないようにする
		if (!result) result = value.x > 0;
	}

	return result;
}

float InputManager::GetAsFloat(Input::Action action) const
{
	const Input::ActionProperty& actionProperty = mActions.at(action);

	float result = 0.0f;

	// アクションに割り当てられたボタンをすべてチェックする
	for (const auto& bind : actionProperty.binds)
	{
		auto device = mDevices.at(bind.device).get();
		
		// 値を取得する
		Vector2 value = device->GetValue(bind.keyCode);

		// バインドに割り当てられた加工をする
		for (const auto& modifier : bind.modifiers)
		{
			modifier->ModifyRaw(&value);
		}
		
		// 絶対値が大きい方を使用する
		if (std::abs(result) < std::abs(value.x)) result = value.x;
	}

	return result;
}

const Vector2& InputManager::GetAsVector2(Input::Action action) const
{
	const Input::ActionProperty& actionProperty = mActions.at(action);

	Vector2 result = Vector2::zero;

	// アクションに割り当てられたボタンをすべてチェックする
	for (const auto& bind : actionProperty.binds)
	{
		auto device = mDevices.at(bind.device).get();
		
		// 値を取得する
		Vector2 value = device->GetValue(bind.keyCode);

		// バインドに割り当てられた加工をする
		for (const auto& modifier : bind.modifiers)
		{
			modifier->ModifyRaw(&value);
		}
		
		// 絶対値が大きい方を使用する
		if (std::abs(result.x) < std::abs(value.x)) result.x = value.x;
		if (std::abs(result.y) < std::abs(value.y)) result.y = value.y;
	}

	if (result != Vector2::zero) result = result.GetNormalize();

	return result;
}

float InputManager::GetAnalog2DAngle(Input::Action action) const
{
	Vector2 vec = GetAsVector2(action);

	float angle = std::atan2(vec.y, vec.x) * MyMath::ToDegree;

	return angle;
}

float InputManager::GetAnalog2DAmount(Input::Action action) const
{
	float amount = GetAsVector2(action).GetLength();

	return amount;
}

bool InputManager::GetState(Input::Action action, InputType inputType, int frame) const
{
	const Input::ActionProperty& actionProperty = mActions.at(action);

	// アクションに割り当てられたボタンをすべてチェックする
	for (const auto& bind : actionProperty.binds)
	{
		auto device = mDevices.at(bind.device).get();

		// 押下状態を取得する
		// 割り当てられたボタンのどれかが押されていたらtrueとする
		switch (inputType)
		{
		case InputType::Down:
			if (device->IsDown(bind.keyCode)) return true;
			break;

		case InputType::Pressed:
			if (device->IsPressed(bind.keyCode)) return true;
			break;

		case InputType::Released:
			if (device->IsReleased(bind.keyCode)) return true;
			break;

		case InputType::Held:
			if (device->IsHeld(bind.keyCode, frame)) return true;
			break;
		}
	}

	// ここまで来たら押されていないためfalse
	return false;
}

void InputManager::Bind(Input::Action action, Input::Device device, KeyCode::Button button, std::vector<std::shared_ptr<IInputModifier>> modifiers, Input::PadSlot slot)
{
	Input::BindProperty bind;
	bind.device = device;
	bind.keyCode = button;
	bind.modifiers = modifiers;
	bind.slot = slot;
	mActions.at(action).binds.emplace_back(bind);
}
