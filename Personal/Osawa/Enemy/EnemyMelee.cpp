#include "EnemyMelee.h"
#include "../Personal/Takagi/Player.h"
#include "../Utility/Time.h"

namespace
{
	constexpr float kMoveSpeed = 50.0f;
}

EnemyMelee::EnemyMelee(ObjectManager* objManager) :
	EnemyBase(objManager)
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
	if (auto player = GetPlayer())
	{
		const Vector3& targetPos = player->GetTransform().position;
		Vector3& myPos = GetTransform().position;

		if (targetPos == myPos) return;

		Vector3 vec = (targetPos - myPos).GetNormalize();

		myPos += vec * kMoveSpeed * Time::GetInstance().GetDeltaTime();


	}
}

void EnemyMelee::Draw()
{
	auto& transform = GetTransform();
	
	DrawBox(transform.position.x - 9, transform.position.y  -10, transform.position.x + 9, transform.position.y + 20, 0xff0000, 1);

	GetCollider().DebugDraw();
}
