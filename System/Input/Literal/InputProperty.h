#pragma once

#include <vector>
#include <memory>
#include "../System/Input/Literal/KeyCodes.h"

class IInputModifier;

namespace Input
{
	// デバイスの種類
	enum class Device
	{
		Keyboard,
		Mouse,
		Gamepad,
		Length
	};

	// バインド情報
	struct BindProperty
	{
		// キーコード
		KeyCode::Button keyCode;

		// デバイスの種類
		Device device = Device::Keyboard;

		// 修飾子
		std::vector<std::shared_ptr<IInputModifier>> modifiers;

		// スロット番号（ゲームパッド用、他では無視される）
		int slot = 1;
	};

	// アクション情報
	struct ActionProperty
	{
		// バインド
		std::vector<BindProperty> binds;
	};
}
