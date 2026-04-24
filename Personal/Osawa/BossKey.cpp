#include "BossKey.h"
#include <cmath>
#include "../Personal/Takagi/Player.h"
#include "../Utility/MyMath.h"
#include "../Utility/Time.h"
#include "../Osawa/Enemy/EnemyManager.h"
#include "../Syoguti/EnemyBoss.h"

namespace
{
	constexpr float kInitSpeed = -400.0f;

	constexpr float kMoveAccel = 10.0f;

	constexpr float kRadianAccel = 0.01f;
}

BossKey::BossKey(ObjectManager* objManager) :
	GameObject(objManager),
	m_action(Action::Appear),
	m_pPlayer(nullptr),
	m_color(),
	m_moveRadian(0.0f)
{
}

BossKey::~BossKey()
{
}

void BossKey::Init()
{
	m_animationTimer = 2.0f;
}

void BossKey::End()
{
}

void BossKey::Update()
{
	switch (m_action)
	{
	case BossKey::Action::Appear:

		if (m_animationTimer > 0) m_animationTimer -= Time::GetInstance().GetDeltaTime();
		else
		{
			Vector3 vec = GetTransform().position - m_pPlayer->GetTransform().position;
			m_moveRadian = std::atan2(vec.y, vec.x);
			m_moveDistance = vec.GetLength();
			m_moveSpeed = kInitSpeed;

			m_action = Action::Move;
		}

		break;

	case BossKey::Action::Move:

		GetTransform().position = m_pPlayer->GetTransform().position + Vector3(std::cos(m_moveRadian), std::sin(m_moveRadian), 0.0f) * m_moveDistance;
		m_moveDistance = MyMath::Approach(m_moveDistance, 0.0f, m_moveSpeed * Time::GetInstance().GetDeltaTime());
		m_moveRadian += kRadianAccel;
		m_moveSpeed += kMoveAccel;

		if (MyMath::IsNearZero(m_moveDistance)) m_action = Action::Follow;

		break;

	case BossKey::Action::Follow:
	{
		Vector3& pos = GetTransform().position;
		const Vector3& playerPos = m_pPlayer->GetTransform().position;

		pos.x = MyMath::Lerp(pos.x, playerPos.x, 0.05f);
		pos.y = MyMath::Lerp(pos.y, playerPos.y, 0.05f);

		m_animationTimer += Time::GetInstance().GetDeltaTime();

		break;
	}

	case BossKey::Action::Use:

		m_pEnemyMgr->GetEnemyBoss()->SealReleaseFlag(4);

		break;
	}
}

void BossKey::Draw()
{
	Vector3 pos = GetTransform().position;
	DrawCircle(pos.x, pos.y + std::sin(m_animationTimer * 2.0f) * 20.0f, 10, 0xffff00);
}
