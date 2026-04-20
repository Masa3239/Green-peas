#include "InputDeviceKeyboard.h"
#include "../System/Input/Format/InputFormatKeyboard.h"

void InputDeviceKeyboard::InitDevice()
{
	RegisterFormat<InputFormatKeyboard>();
}
