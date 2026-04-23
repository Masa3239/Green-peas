#include "BossBullet.h"
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include <DxLib.h>
#include "../Takagi/Player.h"

namespace {

	//画像のサイズ
	constexpr float kGraphScale = 0.1f;

	// 円の当たり判定の半径
	constexpr float kCircleRadius = 50.0f;

    // 弾のスピード
    constexpr float kBulletSpeed = 5.0f;
}

BossBullet::BossBullet(ObjectManager* objManager) :
	BossBulletBase(objManager)
{

	m_collision = Collision::Circle(GetTransform().position, kCircleRadius);
}

BossBullet::~BossBullet()
{
}

void BossBullet::Init()
{
    if (!m_pPlayer)
    {
        printfDx("Player is null!\n");
        return;
    }
    // 自分の位置
    Vector3 myPos = GetTransform().position;

    // プレイヤーの位置
    Vector3 playerPos = m_pPlayer->GetTransform().position;

    // 方向ベクトルを作る
    Vector3 dir = playerPos - myPos;

    // 正規化
    dir = dir.GetNormalize();

    // 弾の発射方向を決める
    m_velocity = dir * kBulletSpeed;

    // 当たり判定
    m_collision.SetRadius(50.0f);
}

void BossBullet::End()
{
}

void BossBullet::Update()
{

    // 座標の更新
    GetTransform().position += m_velocity;

	// 中心座標をセット
	m_collision.SetPosition(GetTransform().position);
}

void BossBullet::Draw()
{

	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y, kGraphScale, 0.0f, m_graphHandle, TRUE);

    // 弾の当たり判定を描画
	m_collision.DebugDraw();
}
