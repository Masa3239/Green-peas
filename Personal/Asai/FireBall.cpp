#include "FireBall.h"
#include"../Asai/BulletBase.h"

#include<DxLib.h>
#include<math.h>
#include"../../Utility/Time.h"

namespace {

	const char* const kGraphHandlePath = ".\\Personal\\Asai\\Graph\\FIREBALL EFFECT 1.png";

	constexpr int kOffSetDraw = 25;

	constexpr float kBallGraphScale = 0.7;

	constexpr float kFiFieldGraphScale = 1.4f;

	constexpr float kGraphFrameChangeTime = 0.1f;

	//当たり判定のサイズ
	constexpr float kCollisionBallSize = 30.0f;
	constexpr float kCollisionFieldSize = 60.0f;

	//移動速度
	constexpr float kSpeed = 180.0f;
	//移動の最大距離
	constexpr float kMaxMoveDistance = 500;

	//フィールドに残る時間
	constexpr float kFieldLifetime = 3.0f;
	//フィールド状態でのダメージ間隔
	constexpr float kFieldDamageInterval = 0.5f;

}

FireBall::FireBall(ObjectManager* objManager) :
	BulletBase(objManager),
	m_state(State::Ball),
	m_fieldElapsedTime(0),
	m_fieldDamageIntervalTimer(0),
	m_graphHandle(),
	m_graphFrame(0),
	m_graphCounter(0)
{
}

void FireBall::Init()
{

	int buf[81];

	LoadDivGraph(kGraphHandlePath, 81, 9, 9, 190, 190, buf);

	for (int i = 0;i < 63;i++) {

		if (i <= 8)continue;

		m_graphHandle.push_back(buf[i]);

	}

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

	SetDrawOrder(GetTransform().position.y);

}

void FireBall::Draw()
{

	if (!m_isActive)return;

	//当たり判定の大きさ
	float collisionSize = 0;
	float graphScale = 0;

	switch (m_state)
	{
	case FireBall::State::Ball:
		collisionSize = kCollisionBallSize;
		graphScale = kBallGraphScale;
		break;
	case FireBall::State::Field:
		collisionSize = kCollisionFieldSize;
		graphScale = kFiFieldGraphScale;
		break;
	default:
		break;
	}

	//画像変更のタイマーを加算
	m_graphCounter += Time::GetInstance().GetDeltaTime();

	//フレーム変更のタイミングになったら
	if (m_graphCounter >= kGraphFrameChangeTime) {
		//フレームを加算
		m_graphFrame++;
		//カウンターをリセット
		m_graphCounter = 0;

		//次の画像がなかったら
		if (m_graphHandle.size() <= m_graphFrame) {
			//画像を最初からにする
			m_graphFrame = 0;
		}

	}

	//画像の描画
	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y - kOffSetDraw, graphScale * m_scale, 0, m_graphHandle[m_graphFrame], TRUE);

	//丸を描画
	//DrawCircle(GetTransform().position.x, GetTransform().position.y, collisionSize * m_scale, TRUE, 0xff0000);

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

void FireBall::SetScale(float scale)
{
	//m_scaleの変更
	m_scale = scale;
	//当たり判定のサイズを変更
	m_circle = Collision::Circle(GetTransform().position, kCollisionBallSize * scale);

}

void FireBall::ChangeStateField()
{
	//既にState::Fieldならリターン
	if (m_state == State::Field)return;

	//状態を変更
	m_state = State::Field;
	//当たり判定のサイズを変更
	m_circle = Collision::Circle(GetTransform().position, kCollisionFieldSize * m_scale);
	//タイマーをリセット
	m_fieldElapsedTime = 0;
	//ダメージ間隔タイマーをリセット
	m_fieldDamageIntervalTimer = 0;

}

bool FireBall::CanFieldDamage()
{
	return m_fieldDamageIntervalTimer > kFieldDamageInterval;
}

void FireBall::UpdateBall()
{
	//デルタタイムを取得
	float deltaTime = Time::GetInstance().GetDeltaTime();

	//移動
	GetTransform().position.x += cosf(GetTransform().rotation.z) * kSpeed * deltaTime;
	GetTransform().position.y += sinf(GetTransform().rotation.z) * kSpeed * deltaTime;

	//当たり判定を更新
	m_circle.SetPosition(GetTransform().position);

	//移動距離を取得
	float distance = (m_spawnPos - GetTransform().position).GetSqLength();
	//移動距離の最大値じゃないならスルー
	if (distance <= kMaxMoveDistance * kMaxMoveDistance)return;

	//移動距離の最大になったら状態を変更
	ChangeStateField();

}

void FireBall::UpdateField()
{
	//デルタタイムを取得
	float deltaTime = Time::GetInstance().GetDeltaTime();

	//タイマーを加算
	m_fieldElapsedTime += deltaTime;
	//ダメージ間隔タイマーを加算
	m_fieldDamageIntervalTimer += deltaTime;

	//消える時間じゃないならスルー
	if (m_fieldElapsedTime < kFieldLifetime)return;

	//非アクティブにする
	m_isActive = false;

}
