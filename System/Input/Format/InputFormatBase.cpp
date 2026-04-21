#include "InputFormatBase.h"

void InputFormatBase::RegisterKeyCode(const KeyCode::Button myKeyCode, const unsigned int keyCode)
{
	mLinkToKeyCode.emplace(myKeyCode, keyCode);
}
