#include "Time.h"
#include <DxLib.h>

Time::Time() :
	m_deltaTime(1.0f),
	m_timeScale(1.0f)
{
}

Time& Time::GetInstance()
{
	static Time instance;

	return instance;
}

void Time::CalculateDeltaTime(LONGLONG time)
{
	m_deltaTime = ((GetNowHiPerformanceCount() - time) / 1000000.0f);

	// デルタタイムが大きすぎたら制限する
	if (m_deltaTime > 0.05f)
	{
		m_deltaTime = 0.05f;
	}
}
