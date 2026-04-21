#include "InputDeviceMouse.h"
#include "../System/Input/Format/InputFormatMouseButton.h"
#include "../System/Input/Format/InputFormatMouseDelta.h"
#include "../System/Input/Format/InputFormatMouseWheel.h"

void InputDeviceMouse::InitDevice()
{
	RegisterFormat<InputFormatMouseButton>();
	RegisterFormat<InputFormatMouseDelta>();
	RegisterFormat<InputFormatMouseWheel>();
}
