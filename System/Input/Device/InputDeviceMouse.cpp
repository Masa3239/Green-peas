#include "InputDeviceMouse.h"
#include "../System/Input/Format/InputFormatMouseButton.h"

void InputDeviceMouse::InitDevice()
{
	RegisterFormat<InputFormatMouseButton>();
}
