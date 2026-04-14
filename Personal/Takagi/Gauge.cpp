#include "Gauge.h"
#include"../../Utility/MyMath.h"
Gauge::Gauge():
	m_maxValue(kInitialValue),
	m_minValue(0),
	m_currentValue(m_maxValue)
{
}

Gauge::~Gauge()
{
}

void Gauge::Init()
{
}

void Gauge::End()
{
}

void Gauge::Increase(float value)
{
	// 現在の値に加算
	m_currentValue += value;
	// 最大値～最小値の範囲内で固定
	m_currentValue = MyMath::Clamp(m_currentValue, m_minValue, m_maxValue);
}

void Gauge::Decrease(float value)
{
	// 現在の値に減算
	m_currentValue -= value;
	// 最大値～最小値の範囲内で固定
	m_currentValue = MyMath::Clamp(m_currentValue, m_minValue, m_maxValue);
}

void Gauge::Reset(int set)
{
	// リセットの種類によって分岐
	switch (set)
	{
	case Max:
		// 最大値でリセット
		m_currentValue = m_maxValue;
		break;
	case Min:
		// 最小値でリセット
		m_currentValue = m_minValue;
		break;
	case Current:
		break;
	default:
		break;
	}
}

bool Gauge::CheckValue(float value, int check)
{
	// 調べたい値の現在の値を格納する変数
	float checkValue = -1;
	switch (check)
	{
	case Max:
		// checkValueを最大値に設定
		checkValue = m_maxValue;
		break;
	case Min:
		// checkValueを最小値に設定
		checkValue = m_minValue;
		break;
	case Current:
		// checkValueを現在の値に設定
		checkValue = m_currentValue;
		break;
	default:
		break;
	}
	// checkValueが指定した値以上ならtrue
	return checkValue >=value;
}

void Gauge::SetValue(float value, int set)
{
	switch (set)
	{
	case Max:
		// 最大値を設定
		m_maxValue = value;
		break;
	case Min:
		// 最小値を設定
		m_minValue = value;
		break;
	case Current:
		// 現在の値を設定
		m_currentValue = value;
		break;
	default:
		break;
	}
}

float Gauge::GetValue(int get)
{
	// 返す値を格納する変数
	float value = -1;
	switch (get)
	{
	case Max:
		// valueを最大値に設定
		value = m_maxValue;
		break;
	case Min:
		// valueを最小値に設定
		value = m_minValue;
		break;
	case Current:
		// valueを現在の値に設定
		value = m_currentValue;
		break;
	default:
		break;
	}
	// 値を返す
	return value;
}
