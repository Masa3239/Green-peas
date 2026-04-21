#include "EnemyMelee.h"
#include "../Personal/Takagi/Player.h"
#include "../Utility/Time.h"
#include "../Chara/Collision.h"

namespace
{
	constexpr float kDistanceSpeed = 50.0f;

	constexpr float kMeleeAttackCooltime = 1.0f;
}

EnemyMelee::EnemyMelee(ObjectManager* objManager) :
	EnemyBase(objManager),
	m_attackCooltimeCounter(0.0f)
{
}

EnemyMelee::~EnemyMelee()
{
}

void EnemyMelee::Init()
{
}

void EnemyMelee::End()
{
}

void EnemyMelee::UpdateEnemy()
{
	auto player = GetPlayer();
	
	const Vector3& targetPos = player->GetTransform().position;
	Vector3& myPos = GetTransform().position;

	if (targetPos == myPos) return;

	Vector3 vec = (targetPos - myPos).GetNormalize();

	myPos += vec * kDistanceSpeed * Time::GetInstance().GetDeltaTime();

	if (m_attackCooltimeCounter > 0)
	{
		m_attackCooltimeCounter -= Time::GetInstance().GetDeltaTime();
	}
	else
	{
		if (GetCollider().CheckCollision(GetPlayer()->GetCircle()))
		{
			Attack();

			m_attackCooltimeCounter = kMeleeAttackCooltime;
		}
	}
}

void EnemyMelee::Draw()
{
	auto& transform = GetTransform();
	
	unsigned int color = (GetMyState() & EnemyBase::kStatePalsy) ? 0xffff00 : 0xff0000;

	DrawBox(transform.position.x - 9, transform.position.y  -10, transform.position.x + 9, transform.position.y + 20, color, 1);

	GetCollider().DebugDraw();
}

void EnemyMelee::Attack()
{
	GetPlayer()->Damage(1);
}
