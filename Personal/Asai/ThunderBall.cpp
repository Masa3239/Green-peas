#include "ThunderBall.h"
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

ThunderBall::ThunderBall(ObjectManager* objManager):
	BulletBase(objManager),
	m_state(State::Ball),
	m_fieldElapsedTime(0)
{
}

void ThunderBall::Init()
{
}

void ThunderBall::Update()
{

	//非アクティブならリターン
	if (!m_isActive)return;

	switch (m_state)
	{
	case ThunderBall::State::Ball:
		//State::Ballの更新処理
		UpdateBall();
		break;

	case ThunderBall::State::Field:
		//State::Fieldの更新処理
		UpdateField();
		break;

	default:
		break;
	}

}

void ThunderBall::Draw()
{
	//非アクティブならリターン
	if (!m_isActive)return;

}

void ThunderBall::DebugDraw()
{
	//非アクティブならリターン
	if (!m_isActive)return;

}

void ThunderBall::End()
{
}

void ThunderBall::Shot(Transform transform)
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
	m_circle = Collision::Circle(m_transform.position, kCollisionBallSize * m_scale);

}

void ThunderBall::SetScale(float scale)
{
	//m_scaleの変更
	m_scale = scale;
	//当たり判定のサイズを変更
	m_circle = Collision::Circle(m_transform.position, kCollisionBallSize * scale);

}

void ThunderBall::UpdateBall()
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
	m_circle = Collision::Circle(m_transform.position, kCollisionFieldSize * m_scale);
	//タイマーをリセット
	m_fieldElapsedTime = 0;

}

void ThunderBall::UpdateField()
{
	//タイマーを加算
	m_fieldElapsedTime += Time::GetInstance().GetDeltaTime();

	//消える時間じゃないならスルー
	if (m_fieldElapsedTime < kFieldLifetime)return;

	//非アクティブにする
	m_isActive = false;


}
