#include "EnemyMiniBoss.h"
#include <DxLib.h>
#include "../Personal/Takagi/Player.h"
#include "../Enemy/EnemyBullet.h"
#include "../Utility/Time.h"
#include "../Utility/MyMath.h"
#include "../BossKey.h"

namespace
{
	// 距離をとるときの速度
	constexpr float kDistanceSpeed = 100.0f;
	// 距離を保っているときの速度
	constexpr float kArcSpeed = 20.0f;
	// 追跡するときの速度
	constexpr float kFollowSpeed = 200.0f;

	constexpr float kMeleeAttackCooltime = 0.5f;

	// プレイヤーを追跡開始する範囲
	constexpr float kStartFollowDistance = 300;

	// プレイヤーからとる基本距離
	constexpr float kBaseDistance = 250;

	// プレイヤーから距離をとり始める距離
	constexpr float kStartBackDistance = 150;

	constexpr float kBulletAttackCooltime = 0.5f;

	// 基礎ステータス
	constexpr EnemyBase::StatusParam kStatus = { 100, 100, 1, 1, 250 };
	// レベルごとの増加量
	constexpr int kHpPerLevel = 100;
	constexpr int kAtkPerLevel = 2;
	constexpr int kDefPerLevel = 1;
}

EnemyMiniBoss::EnemyMiniBoss(ObjectManager* objManager) :
	EnemyBase(objManager),
	m_action(Action::Idle),
	m_attackCooltimeCounter(0.0f)
{
}

EnemyMiniBoss::~EnemyMiniBoss()
{
}

void EnemyMiniBoss::Init()
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

void EnemyMiniBoss::End()
{
	for (auto& bullet : m_bullets)
	{
		bullet->End();
	}
}

void EnemyMiniBoss::UpdateEnemy()
{
	auto player = GetPlayer();
	
	const Vector3& targetPos = player->GetTransform().position;
	Vector3& myPos = GetTransform().position;

	float sqDistance = (targetPos - myPos).GetSqLength();

	Vector3 move;

	// HPが半分より上なら近接攻撃
	if (MyMath::Rate(GetStatusParam().hp, GetStatusParam().maxHp) > 0.5f)
	{
		m_action = Action::Melee;
	}
	// HPが半分以下なら遠距離攻撃
	else
	{
		// 距離を取られたら
		if (sqDistance > kStartFollowDistance * kStartFollowDistance)
		{
			m_action = Action::Follow;
		}
		else if (sqDistance < kStartBackDistance * kStartBackDistance)
		{
			m_action = Action::Back;
		}
	}

	switch (m_action)
	{
	case EnemyMiniBoss::Action::Idle: break;

	case EnemyMiniBoss::Action::Melee:

		if (m_attackCooltimeCounter <= 0)
		{
			const Vector3& targetPos = player->GetTransform().position;
			Vector3& myPos = GetTransform().position;

			if (targetPos == myPos) return;

			Vector3 vec = (targetPos - myPos).GetNormalize();

			move = vec * kFollowSpeed;

			if (GetCollider().CheckCollision(GetPlayer()->GetCircle()))
			{
				Attack();
			}

		}
		break;

	case EnemyMiniBoss::Action::Follow:

		move = (targetPos - myPos).GetNormalize() * kFollowSpeed;

		if (sqDistance < kBaseDistance * kBaseDistance)
		{
			m_action = Action::Distance;
		}

		break;

	case EnemyMiniBoss::Action::Distance:
	{
		Vector3 vec = (targetPos - myPos);

		float s = std::sin(DX_PI_F / 2);
		float c = std::cos(DX_PI_F / 2);

		vec = Vector3(vec.x * c - vec.y * s, vec.x * s + vec.y * c, 0.0f);
		move = vec * Time::GetInstance().GetDeltaTime() * kArcSpeed;

		if (m_attackCooltimeCounter <= 0) Attack();

		break;
	}

	case EnemyMiniBoss::Action::Back:

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

void EnemyMiniBoss::Draw()
{
	auto& transform = GetTransform();
	
	unsigned int color = (GetMyState() & EnemyBase::kStatePalsy) ? 0xffff00 : 0xff0000;

	DrawBox(transform.position.x - 30, transform.position.y - 60, transform.position.x + 30, transform.position.y + 20, color, 1);

	GetCollider().DebugDraw();
}

void EnemyMiniBoss::Dead()
{
	EnemyBase::Dead();

	// 鍵を生成
	auto key = new BossKey(GetObjectManager());
	key->SetPlayer(GetPlayer());
	key->SetEnemyManager(GetEnemyManager());
	key->GetTransform() = GetTransform();
	key->Init();
}

void EnemyMiniBoss::Attack()
{
	if (m_action == Action::Melee)
	{
		GetPlayer()->Damage(GetStatusParam().attack);

		m_attackCooltimeCounter = kMeleeAttackCooltime;
	}
	else
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
}
