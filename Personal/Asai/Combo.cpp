#include "Combo.h"
#include"../Osawa/Enemy/EnemyManager.h"

#include<string>
#include"../../Utility/Time.h"

namespace {
	//コンボの受付時間
	constexpr float kReceptionTime = 5;
	//表示するX座標
	constexpr int kPosX = 30;
	//表示するY座標
	constexpr int kPosY = 10;

	constexpr float kFadeStartTime = 2.0f;

	//最大のアルファ値
	constexpr int kMaxAlpha = 255;

}

Combo::Combo():
	m_fontHandle(-1),
	m_combo(0),
	m_prevDefeatedNum(0),
	m_receptionTimer(0),
	m_alpha(0),
	m_isVisible(false),
	m_pEnemyMgr(nullptr)
{
}

void Combo::Init()
{
	//フォントを生成
	m_fontHandle = CreateFontToHandle(NULL, 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
}

void Combo::Update()
{
	//nullチェック
	if (!m_pEnemyMgr)return;

	//倒した敵の数を取得
	const int defeatedNum = m_pEnemyMgr->GetDefeatedNum();
	
	//1F前と違ったら倒している
	if (m_prevDefeatedNum != defeatedNum) {
		//コンボを加算
		m_combo += defeatedNum - m_prevDefeatedNum;
		//タイマーをリセット
		m_receptionTimer = 0;
		//表示状態にする
		m_isVisible = true;

		m_alpha = kMaxAlpha;
	}

	//受付時間を加算
	m_receptionTimer += Time::GetInstance().GetDeltaTime();

	if (m_receptionTimer > kFadeStartTime) {

		float rate = MyMath::Rate(m_receptionTimer - kFadeStartTime, kReceptionTime - kFadeStartTime);

		m_alpha = kMaxAlpha * (1.0f - rate);
	}

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

	//コンボを文字に変換
	std::string combo = "Combo : " + std::to_string(m_combo);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);

	DrawStringToHandle(kPosX, kPosY, combo.c_str(), 0xffffff, m_fontHandle);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void Combo::DebugDraw()
{
}

void Combo::End()
{
	//破棄
	DeleteFontToHandle(m_fontHandle);

}
