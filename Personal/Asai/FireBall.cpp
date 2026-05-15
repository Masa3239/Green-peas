#include "FireBall.h"
#include"../Asai/BulletBase.h"

#include<DxLib.h>
#include<math.h>
#include"../../System/SoundManager.h"
#include"../../Utility/Time.h"

namespace {

	const char* const kGraphHandlePath = ".\\Resource\\FIREBALL EFFECT 1.png";

	//当たり判定と表示位置を一致させる
	constexpr int kOffSetDraw = 25;

	//ボール状態での画像の表示倍率
	constexpr float kBallGraphScale = 0.7;
	//フィールド状態での画像の表示倍率
	constexpr float kFiFieldGraphScale = 1.4f;
	//画像変更までの時間
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
	constexpr float kFieldDamageInterval = 0.2f;

}

FireBall::FireBall(ObjectManager* objManager) :
	BulletBase(objManager),
	m_state(State::Ball),
	m_fieldElapsedTime(0),
	m_fieldDamageIntervalTimer(0),
	m_graphFrame(0),
	m_graphCounter(0)
{
}

void FireBall::Init()
{
}

void FireBall::Update()
{

	if (!m_isActive)return;

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

	SetDrawOrder(0);

}

void FireBall::Draw()
{

	if (!m_isActive)return;

	//当たり判定の大きさ
	float graphScale = 0;

	switch (m_state)
	{
	case FireBall::State::Ball:
		graphScale = kBallGraphScale;
		break;
	case FireBall::State::Field:
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

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

	//画像の描画
	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y - kOffSetDraw, graphScale * m_scale, 0, m_graphHandle[m_graphFrame], TRUE);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

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
	//トータルの移動量をリセット
	m_totalDistance = 0;
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

	Vector3 move = Vector3::zero;
	move.x = cosf(GetTransform().rotation.z);
	move.y= sinf(GetTransform().rotation.z);
	move = move.GetNormalize();
	move *= kSpeed * deltaTime;

	//移動
	GetTransform().position.x += move.x;
	GetTransform().position.y += move.y;

	//当たり判定を更新
	m_circle.SetPosition(GetTransform().position);

	//移動距離を取得
	m_totalDistance += kSpeed * deltaTime;
	//移動距離の最大値じゃないならスルー
	if (m_totalDistance <= kMaxMoveDistance)return;

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
