#include "Combo.h"

#include"../../Utility/Time.h"

#include"../Osawa/Enemy/EnemyManager.h"

namespace {
	//コンボの受付時間
	constexpr float kReceptionTime = 5;


}

Combo::Combo():
	m_fontHandle(-1),
	m_combo(0),
	m_prevDefeatedNum(0),
	m_receptionTimer(0),
	m_isVisible(false),
	m_pEnemyMgr(nullptr)
{
}

void Combo::Init()
{
}

void Combo::Update()
{
	//倒した敵の数を取得
	int defeatedNum = m_pEnemyMgr->GetDefeatedNum();
	
	//1F前と違ったら倒している
	if (m_prevDefeatedNum != defeatedNum) {
		//コンボを加算
		m_combo += defeatedNum - m_prevDefeatedNum;
		//タイマーをリセット
		m_receptionTimer = 0;
		//表示状態にする
		m_isVisible = true;
	}

	//受付時間を加算
	m_receptionTimer += Time::GetInstance().GetDeltaTime();

	//受付時間を超えたら
	if (m_receptionTimer > kReceptionTime) {
		//コンボをリセットする
		m_combo = 0;
		//非表示にする
		m_isVisible = false;
	}

	//倒した数を設定
	m_prevDefeatedNum = defeatedNum;

}

void Combo::Draw()
{
	//表示されていないならリターン
	if (!m_isVisible)return;



}

void Combo::DebugDraw()
{
}

void Combo::End()
{
}
