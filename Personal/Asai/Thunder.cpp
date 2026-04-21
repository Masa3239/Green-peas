#include "Thunder.h"
#include"../Asai/BulletBase.h"
#include"../Osawa/Enemy/EnemyBase.h"
#include"../Osawa/Enemy/EnemyManager.h"

#include<DxLib.h>
#include<math.h>
#include"../../Utility/Time.h"

namespace {
	//当たり判定のサイズ
	constexpr float kCollisionBallSize = 20.0f;
	constexpr float kCollisionFieldSize = 40.0f;

	//移動速度
	constexpr float kSpeed = 60.0f;
	//移動の最大距離
	constexpr float kMaxMoveDistance = 500;

	//フィールドに残る時間
	constexpr float kFieldLifetime = 1.0f;

	//伝染回数
	constexpr int kMaxInfection = 5;
	//伝染感覚
	constexpr float kInterval = 0.1f;

}


Thunder::Thunder(ObjectManager* objManager):
	BulletBase(objManager),
	m_state(State::Ball),
	m_fieldElapsedTime(0),
	m_infectionCount(0),
	m_pEnemyMgr(nullptr),
	m_pEnemies()
{
	m_pEnemies.clear();
}

void Thunder::Init()
{
}

void Thunder::Update()
{

	//非アクティブならリターン
	if (!m_isActive)return;

	switch (m_state)
	{
	case Thunder::State::Ball:
		//State::Ballの更新処理
		UpdateBall();
		break;

	case Thunder::State::Field:
		//State::Fieldの更新処理
		UpdateField();
		break;

	default:
		break;
	}

}

void Thunder::Draw()
{
	//非アクティブならリターン
	if (!m_isActive)return;

}

void Thunder::DebugDraw()
{
	//非アクティブならリターン
	if (!m_isActive)return;

	m_circle.DebugDraw();

}

void Thunder::End()
{
}

void Thunder::Shot(Transform transform)
{
	//セット
	GetTransform() = transform;
	//アクティブにする
	m_isActive = true;
	//スポーン位置を設定
	m_spawnPos = transform.position;
	//玉の状態にする
	m_state = State::Ball;
	//当たり判定を変更する
	m_circle = Collision::Circle(GetTransform().position, kCollisionBallSize * m_scale);

}

void Thunder::SetScale(float scale)
{
	//m_scaleの変更
	m_scale = scale;
	//当たり判定のサイズを変更
	m_circle = Collision::Circle(GetTransform().position, kCollisionBallSize * scale);

}

void Thunder::UpdateBall()
{
	//デルタタイムを取得
	float deltaTime = Time::GetInstance().GetDeltaTime();

	//移動
	GetTransform().position.x += sinf(GetTransform().rotation.z) * kSpeed * deltaTime;
	GetTransform().position.y += -cosf(GetTransform().rotation.z) * kSpeed * deltaTime;

	//当たり判定を更新
	m_circle.SetPosition(GetTransform().position);

	//移動距離を取得
	float distance = (m_spawnPos - GetTransform().position).GetSqLength();
	//移動距離の最大値じゃないならスルー
	if (distance <= kMaxMoveDistance * kMaxMoveDistance)return;

	//移動距離の最大になったら状態を変更
	m_state = State::Field;
	//当たり判定のサイズを変更
	m_circle = Collision::Circle(GetTransform().position, kCollisionFieldSize * m_scale);
	//タイマーをリセット
	m_fieldElapsedTime = 0;

}

void Thunder::UpdateField()
{
	//タイマーを加算
	m_fieldElapsedTime += Time::GetInstance().GetDeltaTime();

	//消える時間じゃないならスルー
	if (m_fieldElapsedTime < kFieldLifetime)return;

	//非アクティブにする
	m_isActive = false;

}
