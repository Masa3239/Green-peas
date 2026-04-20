#include"PlayerStatus.h"
#include "PlayerBuff.h"
#include"../../Utility/Time.h"
namespace {

}

PlayerBuff::PlayerBuff():
m_bufValue(),
m_second(0),
m_isEternal(false)
{
	m_bufValue = { 0,0,0,0,0,0,0,0 };
}

PlayerBuff::PlayerBuff(PlayerStatus bufValue, float second, bool eternal) :
	m_bufValue(bufValue),
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
