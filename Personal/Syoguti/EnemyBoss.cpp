#include "EnemyBoss.h"
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include "DxLib.h"

namespace {

	// 画像のファイルパス
	const char* const kSealBossGraphHandlePath = ".\\Personal\\Syoguti\\Resource\\EnemyBossTest1.png";
	const char* const kBossGraphHandlePath = ".\\Personal\\Syoguti\\Resource\\EnemyBossTest2.png";

	// 画像のサイズ
	constexpr float kGraphScale = 0.1f;

	// 円の当たり判定の半径
	constexpr float kCircleRadius = 50.0f;

}

EnemyBoss::EnemyBoss() :
	m_graphHandle(-1),
	m_transform(),
	m_collsion(m_transform.position, kCircleRadius),
	m_state(BossStatus::Seal)
{
	m_transform.Reset();
}

EnemyBoss::EnemyBoss(Vector3 position) :
	m_graphHandle(-1),
	m_transform(),
	m_collsion(m_transform.position, kCircleRadius),
	m_state(BossStatus::Seal)
{
	m_transform.Reset();
	m_transform.position = position;
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

	m_collsion.SetPosition(m_transform.position);
}

void EnemyBoss::Draw()
{

	// 画像の描画
	DrawRotaGraph(m_transform.position.x, m_transform.position.y, kGraphScale, 0.0f, m_graphHandle, TRUE);

	// 円の当たり判定の描画
	m_collsion.DebugDraw();
}
