#pragma once

#include "../Utility/Vector3.h"

/// <summary>
/// 値を加工するクラスのインターフェイス
/// </summary>
class IInputModifier
{
public:

	IInputModifier() = default;
	virtual ~IInputModifier() = default;

	virtual void ModifyRaw(Vector2* rawValue) = 0;
};
