#include "EnemyShooter.h"
#include <cmath>
#include <DxLib.h>
#include "../Personal/Takagi/Player.h"
#include "../Utility/Time.h"
#include "../Chara/Collision.h"
#include "../Enemy/EnemyBullet.h"

namespace
{
	// 距離をとるときの速度
	constexpr float kDistanceSpeed = 100.0f;
	// 距離を保っているときの速度
	constexpr float kArcSpeed = 20.0f;
	// 追跡するときの速度
	constexpr float kFollowSpeed = 150.0f;

	// プレイヤーを追跡開始する範囲
	constexpr float kStartFollowDistance = 300;

	// プレイヤーからとる基本距離
	constexpr float kBaseDistance = 250;

	// プレイヤーから距離をとり始める距離
	constexpr float kStartBackDistance = 150;

	constexpr float kBulletAttackCooltime = 10.0f;

	// 基礎ステータス
	constexpr EnemyBase::StatusParam kStatus = { 25, 25, 5, 5, 5 };
	// レベルごとの増加量
	constexpr int kHpPerLevel = 8;
	constexpr int kAtkPerLevel = 2;
	constexpr int kDefPerLevel = 5;
}

EnemyShooter::EnemyShooter(ObjectManager* objManager) :
	EnemyBase(objManager),
	m_action(Action::Idle),
	m_attackCooltimeCounter(0.0f)
{
}

EnemyShooter::~EnemyShooter()
{
}

void EnemyShooter::Init()
{
	StatusParam status = kStatus;
	status.hp += kHpPerLevel * GetLevel();
	status.maxHp = status.hp;
	status.attack += kAtkPerLevel * GetLevel();
	status.defence += kDefPerLevel * GetLevel();
	SetStatusParam(status);

	for (auto& bullet : m_bullets)
	{
		bullet = std::make_unique<EnemyBullet>(GetObjectManager(), GetStatusParam().attack);
		bullet->SetPlayer(GetPlayer());
		bullet->Init();
	}
}

void EnemyShooter::End()
{
	for (auto& bullet : m_bullets)
	{
		bullet->End();
	}
}

void EnemyShooter::UpdateEnemy()
{
	auto player = GetPlayer();
	
	const Vector3& targetPos = player->GetTransform().position;
	Vector3& myPos = GetTransform().position;

	float sqDistance = (targetPos - myPos).GetSqLength();

	Vector3 move;

	// 距離を取られたら
	if (sqDistance > kStartFollowDistance * kStartFollowDistance)
	{
		m_action = Action::Follow;
	}
	else if (sqDistance < kStartBackDistance * kStartBackDistance)
	{
		m_action = Action::Back;
	}

	switch (m_action)
	{
	case EnemyShooter::Action::Idle: break;

	case EnemyShooter::Action::Follow:

		move = (targetPos - myPos).GetNormalize() * kFollowSpeed;

		if (sqDistance < kBaseDistance * kBaseDistance)
		{
			m_action = Action::Distance;
		}

		break;

	case EnemyShooter::Action::Distance:
	{
		Vector3 vec = (targetPos - myPos);

		float s = std::sin(DX_PI_F / 2);
		float c = std::cos(DX_PI_F / 2);

		vec = Vector3(vec.x * c - vec.y * s, vec.x * s + vec.y * c, 0.0f);
		move = vec * Time::GetInstance().GetDeltaTime() * kArcSpeed;

		if (m_attackCooltimeCounter <= 0) Attack();

		break;
	}

	case EnemyShooter::Action::Back:

		move = (targetPos - myPos).GetNormalize() * -kDistanceSpeed;

		if (m_attackCooltimeCounter <= 0) Attack();

		break;
	}

	myPos += move * Time::GetInstance().GetDeltaTime();

	if (m_attackCooltimeCounter > 0)
	{
		m_attackCooltimeCounter -= Time::GetInstance().GetDeltaTime();
	}
}

void EnemyShooter::Draw()
{
	auto& transform = GetTransform();

	DrawBox(transform.position.x - 9, transform.position.y - 10, transform.position.x + 9, transform.position.y + 20, 0x0000ff, 1);

	GetCollider().DebugDraw();
}

void EnemyShooter::Attack()
{
	// 一番手前の無効状態の弾を生成
	for (const auto& bullet : m_bullets)
	{
		if (bullet->GetState() == State::Active) continue;

		const Vector3& pos = GetTransform().position - GetPlayer()->GetTransform().position;

		const float dir = std::atan2(pos.y, pos.x);

		const Vector3& rot = Vector3(0.0f, 0.0f, dir);

		bullet->Create(GetTransform().position, rot);

		m_attackCooltimeCounter = kBulletAttackCooltime;

		break;
	}
}
