#include "ExpGauge.h"
#include<math.h>
#include<DxLib.h>

namespace {
	constexpr float kIncleaseAmount = 1.05f;
	constexpr int kInitMax = 30;
}

ExpGauge::ExpGauge():
	m_level(1),
	m_totalExp(0),
	m_maxExp(kInitMax),
	m_minExp(0)
{
}

ExpGauge::~ExpGauge()
{
}

void ExpGauge::Init()
{
}

void ExpGauge::End()
{
}

void ExpGauge::Update()
{
	CheckCurrent();
}

void ExpGauge::Increase(float value)
{
	m_totalExp += value;
}

void ExpGauge::Decrease(float value)
{
	m_totalExp -= value;
}

void ExpGauge::Clamp()
{
}

void ExpGauge::Debug()
{
	printfDx("level : %d\n", m_level);
	printfDx("total : %f\n", m_totalExp);
	printfDx("max   : %f\n", m_maxExp);
	printfDx("min   : %f\n", m_minExp);
}

void ExpGauge::Reset(int set)
{

}

void ExpGauge::LevelUp()
{
	// レベルに応じてレベルアップまでの最大値を求める
	m_minExp = m_maxExp;
	m_level++;
	// レベルが1のとき
	if(m_level==1) {
		// 最小経験値を0にする
		m_minExp = 0;
	}


	m_maxExp = (kInitMax * m_level) * (pow(kIncleaseAmount, m_level));
	CheckLimit();
}

void ExpGauge::CheckLimit()
{
	
}

void ExpGauge::CheckCurrent()
{
	// ゲージで表示するための現在の経験値量を求める
	m_currentValue = m_totalExp - m_minExp;

	// 経験値の最大量を求める
	SetValue(m_maxExp - m_minExp, Max);
	// 最大経験値量を越したらレベルアップ
	if (m_totalExp >= m_maxExp)LevelUp();
}
