#include"PlayerStatus.h"
#include "PlayerBuff.h"
#include"../../Utility/Time.h"
namespace {

}

PlayerBuff::PlayerBuff():
m_buffValue({0,0,0,0,0,0,0,0}),
m_second(0),
m_isEternal(false)
{
}

PlayerBuff::PlayerBuff(PlayerStatus bufValue, float second, bool eternal) :
	m_buffValue(bufValue),
	m_second(second),
	m_isEternal(eternal)
{
}



void PlayerBuff::Update()
{
	float deltaTime = Time::GetInstance().GetDeltaTime();
	if (m_isEternal)return;
	m_second -= deltaTime;
}

bool PlayerBuff::IsFinish()
{
	if (m_isEternal)return false;
	return (m_second <= 0);
}
