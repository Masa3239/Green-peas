#include "EnemyBoss.h"

#include "Dxlib.h"
namespace {

	// 画像のファイルパス
	const char* const kSealBossGraphHandlePath = ".\\Personal\\Syoguti\\Resource\\EnemyBossTest1.png";
	const char* const kBossGraphHandlePath = ".\\Personal\\Syoguti\\Resource\\EnemyBossTest2.png";

	// 画像のサイズ
	constexpr float kGraphScale = 0.1f;

}

EnemyBoss::EnemyBoss() :
	m_graphHandle(-1),
	m_posX(0),
	m_posY(0)
{
}

void EnemyBoss::Init()
{

	m_graphHandle = LoadGraph(kSealBossGraphHandlePath);
}

void EnemyBoss::End()
{
	// 画像の破棄
	DeleteGraph(m_graphHandle);
}

void EnemyBoss::Update()
{
}

void EnemyBoss::Draw()
{

	// 仮の座標
	m_posX = 200;
	m_posY = 200;
	// 画像の描画
	DrawRotaGraph(m_posX, m_posY, kGraphScale, 0.0f, m_graphHandle, TRUE);
}
