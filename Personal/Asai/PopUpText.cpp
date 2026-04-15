#include "PopUpText.h"
#include<array>
#include"../../Utility/Transform.h"

#include"../../Utility/Time.h"
#include <string>

namespace {

	constexpr float kActiveTime = 1.0f;

}

PopUpText::PopUpText():
	m_transform(),
	m_amount(0),
	m_fontHandle(-1),
	m_color(0),
	m_timer(0),
	m_isDead(false)
{
}

PopUpText::~PopUpText()
{
}

void PopUpText::Init()
{
}

void PopUpText::Update()
{
	//タイマーを加算
	m_timer += Time::GetInstance().GetDeltaTime();

	//時間になったら
	if (m_timer >= kActiveTime) {
		//死亡フラグをtrueにする
		m_isDead = true;

	}

}

void PopUpText::Draw()
{
	//int型をstring型に変換
	std::string stringAmount = std::to_string(m_amount);

	//テキストの表示
	DrawStringToHandle(m_transform.position.x, m_transform.position.y, stringAmount.c_str(), m_color, m_fontHandle);

}

void PopUpText::DebugDraw()
{

	printfDx("PopUpText timer %f\n", m_timer);

}

void PopUpText::End()
{

	DeleteGraph(m_fontHandle);

}
