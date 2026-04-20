#include "FireBall.h"
#include"../Asai/BulletBase.h"

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
	constexpr float kFieldLifetime = 3.0f;

}

FireBall::FireBall(ObjectManager* objManager) :
	BulletBase(objManager),
	m_state(State::Ball),
	m_fieldElapsedTime(0)
{
}

void FireBall::Init()
{
}

void FireBall::Update()
{

	switch (m_state)
	{
	case FireBall::State::Ball:
		//State::Ballの更新処理
		UpdateBall();
		break;

	case FireBall::State::Field:
		//State::Fieldの更新処理
		UpdateField();
		break;

	default:
		break;
	}

}

void FireBall::Draw()
{
}

void FireBall::DebugDraw()
{
	//当たり判定を表示
	m_circle.DebugDraw();

}

void FireBall::End()
{
}

void FireBall::Shot(Transform transform)
{
	//セット
	m_transform = transform;
	//アクティブにする
	m_isActive = true;
	//スポーン位置を設定
	m_spawnPos = transform.position;
	//玉の状態にする
	m_state = State::Ball;
	//当たり判定を変更する
	m_circle = Collision::Circle(m_transform.position, kCollisionBallSize);

}

void FireBall::UpdateBall()
{
	//デルタタイムを取得
	float deltaTime = Time::GetInstance().GetDeltaTime();

	//移動
	m_transform.position.x += sinf(m_transform.rotation.z) * kSpeed * deltaTime;
	m_transform.position.y += -cosf(m_transform.rotation.z) * kSpeed * deltaTime;

	//当たり判定を更新
	m_circle.SetPosition(m_transform.position);

	//移動距離を取得
	float distance = (m_spawnPos - m_transform.position).GetSqLength();
	//移動距離の最大値じゃないならスルー
	if (distance <= kMaxMoveDistance * kMaxMoveDistance)return;

	//移動距離の最大になったら状態を変更
	m_state = State::Field;
	//当たり判定のサイズを変更
	m_circle = Collision::Circle(m_transform.position, kCollisionFieldSize);
	//タイマーをリセット
	m_fieldElapsedTime = 0;

}

void FireBall::UpdateField()
{
	//タイマーを加算
	m_fieldElapsedTime += Time::GetInstance().GetDeltaTime();

	//消える時間じゃないならスルー
	if (m_fieldElapsedTime < kFieldLifetime)return;

	//非アクティブにする
	m_isActive = false;

}
