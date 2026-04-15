#include "PlayerUIBase.h"
#include"../../Utility/MyMath.h"

PlayerUIBase::PlayerUIBase():
	m_graphHandle(-1),
	m_isVisible(false),
	m_value(0),
	m_max(0),
	m_rate(0)
{
}

void PlayerUIBase::CalculateRate()
{
	//割合を計算
	m_rate = MyMath::Rate(m_value, m_max);
}

void PlayerUIBase::NormalizeRate()
{

	if (m_rate < 0) {
		m_rate = 0;
	}
	if (m_rate > 1.0f) {
		m_rate = 1.0f;
	}

}
