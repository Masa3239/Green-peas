#include "InputDeviceGamepad.h"
#include "../System/Input/Format/InputFormatGamepadButton.h"
#include "../System/Input/Format/InputFormatGamepadTrigger.h"
#include "../System/Input/Format/InputFormatGamepadThumb.h"

void InputDeviceGamepad::InitDevice()
{
	RegisterFormat<InputFormatGamepadButton>();
	RegisterFormat<InputFormatGamepadTrigger>();
	RegisterFormat<InputFormatGamepadThumb>();
}
