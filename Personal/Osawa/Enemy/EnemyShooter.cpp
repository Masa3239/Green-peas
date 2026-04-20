#include "EnemyShooter.h"
#include <cmath>
#include <DxLib.h>
#include "../Personal/Takagi/Player.h"
#include "../Utility/Time.h"
#include "../Chara/Collision.h"

namespace
{
	// 距離をとるときの速度
	constexpr float kDistanceSpeed = 100.0f;
	// 距離を保っているときの速度
	constexpr float kArcSpeed = 20.0f;
	// 追跡するときの速度
	constexpr float kFollowSpeed = 200.0f;

	constexpr float kAttackCooltime = 1.0f;

	// プレイヤーを追跡開始する範囲
	constexpr float kStartFollowDistance = 300;

	// プレイヤーからとる基本距離
	constexpr float kBaseDistance = 250;

	// プレイヤーから距離をとり始める距離
	constexpr float kStartBackDistance = 150;
}

EnemyShooter::EnemyShooter(ObjectManager* objManager) :
	EnemyBase(objManager),
	mAction(Action::Idle)
{
	SetAttackCooltime(kAttackCooltime);
}

EnemyShooter::~EnemyShooter()
{
}

void EnemyShooter::Init()
{
}

void EnemyShooter::End()
{
}

void EnemyShooter::UpdateEnemy()
{
	if (auto player = GetPlayer())
	{
		const Vector3& targetPos = player->GetTransform().position;
		Vector3& myPos = GetTransform().position;

		float sqDistance = (targetPos - myPos).GetSqLength();

		Vector3 move;

		// 距離を取られたら
		if (sqDistance > kStartFollowDistance * kStartFollowDistance)
		{
			mAction = Action::Follow;
		}
		else if (sqDistance < kStartBackDistance * kStartBackDistance)
		{
			mAction = Action::Back;
		}

		switch (mAction)
		{
		case EnemyShooter::Action::Idle: break;

		case EnemyShooter::Action::Follow:

			move = (targetPos - myPos).GetNormalize() * kFollowSpeed;

			if (sqDistance < kBaseDistance * kBaseDistance)
			{
				mAction = Action::Distance;
			}

			break;

		case EnemyShooter::Action::Distance:
		{
			Vector3 vec = (targetPos - myPos);

			float s = std::sin(DX_PI_F / 2);
			float c = std::cos(DX_PI_F / 2);

			vec = Vector3(vec.x * c - vec.y * s, vec.x * s + vec.y * c, 0.0f);
			move = vec * Time::GetInstance().GetDeltaTime() * kArcSpeed;

			break;
		}

		case EnemyShooter::Action::Back:

			move = (targetPos - myPos).GetNormalize() * -kDistanceSpeed;

			break;
		}

		myPos += move * Time::GetInstance().GetDeltaTime();
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
	//GetPlayer()->Damage(1);
}
