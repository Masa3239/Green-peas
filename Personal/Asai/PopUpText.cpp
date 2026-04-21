#include "PopUpText.h"
#include"../../Utility/Transform.h"

#include"../../Utility/Color.h"
#include"../../Utility/Time.h"
#include<array>
#include<string>

namespace {

	//表示される時間
	constexpr float kActiveTime = 0.5f;
	//速度
	constexpr float kSpeed = 30.0f;
	//動く方向
	constexpr Vector3 kMoveDirection{ 0.0f,-1.0f,0.0f };

	int kDamageColor = Color::kWhite;

}

PopUpText::PopUpText():
	m_transform(),
	m_amount(0),
	m_fontHandle(-1),
	m_color(0),
	m_timer(0),
	m_isActive(false)
{
}

PopUpText::~PopUpText()
{
}

void PopUpText::Init()
{
	//タイマーをリセット
	m_timer = 0;
	//アクティブにする
	m_isActive = true;

}

void PopUpText::Update()
{

	//デルタタイムを取得
	float deltaTime = Time::GetInstance().GetDeltaTime();

	//タイマーを加算
	m_timer += deltaTime;
	//移動
	m_transform.position += kMoveDirection * kSpeed * deltaTime;

	//時間になったら
	if (m_timer >= kActiveTime) {
		//active状態をfalseにする
		m_isActive = false;

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

	//printfDx("PopUpText timer %f\n", m_timer);

}

void PopUpText::End()
{

	DeleteGraph(m_fontHandle);

}

void PopUpText::SetData(int amount, int fontHandle, PopUpText::Type type)
{
	//セットする
	m_amount = amount;
	m_fontHandle = fontHandle;
	m_color = kDamageColor;

}
