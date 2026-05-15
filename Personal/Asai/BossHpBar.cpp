#include "BossHpBar.h"
#include"../Osawa/Enemy/EnemyManager.h"
#include"../Syoguti/EnemyBoss.h"
#include<string>

#include<DxLib.h>
#include"../../Utility/Game.h"
#include"../../Utility/MyMath.h"

namespace {

	constexpr int kGaugeLeft = 70;

	constexpr int kGaugeRight = Game::kScreenWidth - 140;

	constexpr int kGaugeTop = 10;

	constexpr int kGaugeBottom = kGaugeTop + 30;

	constexpr int kHpGaugeWidth = kGaugeRight - kGaugeLeft;

}

BossHpBar::BossHpBar():
	m_pEnemyMgr(nullptr),
	m_currentHp(),
	m_maxHp(0),
	m_rate(0),
	m_hpFont(-1),
	m_maxHpFont("")
{
}

void BossHpBar::Init()
{
	m_hpFont = CreateFontToHandle(NULL, 15, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
}

void BossHpBar::Update()
{

	if (!m_pEnemyMgr)return;

	//封印されていたらスルー
	if (!m_pEnemyMgr->GetEnemyBoss()->GetSealReleaseFlag())return;

	//現在のHPを取得
	m_currentHp = m_pEnemyMgr->GetEnemyBoss()->GetBossCurrentHp();

	if (m_currentHp <= 0)m_currentHp = 0;

	m_rate = MyMath::Rate(m_currentHp, m_maxHp);

}

void BossHpBar::Draw()
{
	if (!m_pEnemyMgr)return;

	//封印されていたらスルー
	if (!m_pEnemyMgr->GetEnemyBoss()->GetSealReleaseFlag())return;

	//ゲームの視認性を上げるために薄くする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

	//HPゲージの枠を描画
	DrawBox(kGaugeLeft, kGaugeTop, kGaugeRight, kGaugeBottom, 0xffffff, TRUE);

	//HPゲージを描画
	DrawBox(kGaugeLeft + 10,
		kGaugeTop,
		kGaugeLeft + 10 + (kHpGaugeWidth * m_rate),
		kGaugeBottom,
		0xff0000, TRUE
	);

	//元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//HPを文字に変換
	std::string hp = std::to_string(m_currentHp);
	//描画する文字を作成
	std::string draw = hp + "/" + m_maxHpFont;
	//現在HPと最大HPを描画
	DrawStringToHandle(kGaugeRight / 2 + 99, kGaugeTop + 10, draw.c_str(), 0xffffff, m_hpFont);

}

void BossHpBar::DebugDraw()
{

	printfDx("rate %f\n", m_rate);
	printfDx("maxHp %d\n",m_maxHp);

}

void BossHpBar::End()
{
}

void BossHpBar::SetEnemyManager(EnemyManager* pEnemyManager)
{
	//セット
	m_pEnemyMgr = pEnemyManager;

	//最大体力をセット
	m_maxHp = m_pEnemyMgr->GetEnemyBoss()->GetBossMaxHp();
	//最大HPを文字に変換
	m_maxHpFont = std::to_string(m_maxHp);

}
