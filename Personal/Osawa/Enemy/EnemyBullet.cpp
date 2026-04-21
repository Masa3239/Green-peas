#include "EnemyBullet.h"
#include <cmath>
#include "../Utility/Time.h"

namespace
{
	// 弾の速度
	constexpr float kSpeed = 200.0f;

	// 弾が残る時間
	constexpr float kLiveTime = 2.0f;

	constexpr float kColliderRadius = 7.5f;
}

EnemyBullet::EnemyBullet(ObjectManager* objManager) :
	GameObject(objManager),
	m_liveCounter(0.0f),
	m_collider(Collision::Circle{ Vector3::zero, kColliderRadius })
{
}

void EnemyBullet::Init()
{
	SetState(State::Deactive);
}

void EnemyBullet::End()
{

}

void EnemyBullet::Update()
{
	auto& transform = GetTransform();

	Vector3 move;

	move.x = std::sin(transform.rotation.z) * kSpeed;
	move.y = -std::cos(transform.rotation.z) * kSpeed;
	move *= Time::GetInstance().GetDeltaTime();

	transform.Translate(move);

	m_collider.SetPosition(transform.position);

	if (m_liveCounter > 0)
	{
		m_liveCounter -= Time::GetInstance().GetDeltaTime();
	}
	else
	{
		SetState(State::Deactive);
	}
}

void EnemyBullet::Draw()
{
	const auto& transform = GetTransform();

	DrawCircle(transform.position.x, transform.position.y, 10, 0xffffff);

	m_collider.DebugDraw();
}

void EnemyBullet::Create(const Vector3& position, const Vector3& rotation)
{
	m_liveCounter = kLiveTime;

	SetState(State::Active);

	GetTransform().position = position;
	GetTransform().rotation = rotation;
}

void EnemyBullet::Remove()
{
	SetState(State::Deactive);
}
