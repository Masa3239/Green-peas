#include "BossKey.h"
#include <cmath>
#include "../Personal/Takagi/Player.h"
#include "../Utility/MyMath.h"
#include "../Utility/Time.h"
#include "../Osawa/Enemy/EnemyManager.h"
#include "../Syoguti/EnemyBoss.h"
#include "../Osawa/Easing/Tween.h"

#include "../System/Input/Keyboard.h"

namespace
{
	constexpr float kInitSpeed = -400.0f;

	constexpr float kMoveAccel = 10.0f;

	constexpr float kRadianAccel = 0.01f;

	// 鍵を使用する範囲
	constexpr float kUseRange = 300.0f;

	const char* const kGraphPath = "Resource\\key_32x32_24f.png";
}

BossKey::BossKey(ObjectManager* objManager) :
	GameObject(objManager),
	m_action(Action::Appear),
	m_pPlayer(nullptr),
	m_pEnemyMgr(nullptr),
	m_pTween(nullptr),
	m_color(),
	m_moveRadian(0.0f),
	m_moveDistance(0.0f),
	m_moveSpeed(0.0f),
	m_animationTimer(0.0f),
	m_currentGraph(0),
	m_graphAnimTimer(0.0f)
{
}

BossKey::~BossKey()
{
}

void BossKey::Init()
{
	m_pTween = std::make_unique<Tween>();

	m_animationTimer = 2.0f;

	Vector3& pos = GetTransform().position;
	m_pTween->StartAnim(&pos.y, {
		Animation::Keyframe{pos.y, 0.0f, Animation::Ease::QuartOut},
		Animation::Keyframe{pos.y - 60, 1.0f, Animation::Ease::QuadIn},
		Animation::Keyframe{pos.y - 40, 2.0f},
		});

	LoadDivGraph(kGraphPath, 24, 24, 1, 32, 32, m_graphsKey);
}

void BossKey::End()
{
}

void BossKey::Update()
{
	m_graphAnimDuration = 0.08f;

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

		// ボスに近づいたら鍵を使用する
		Collision::Circle range = { pos, kUseRange };
		if (m_pEnemyMgr->GetEnemyBoss()->GetCollider().CheckCollision(range))
		{
			UseKey();
		}

		break;
	}

	case BossKey::Action::Use:

		m_graphAnimDuration = 0.001f;

		if (m_animationTimer > 0.0f) break;

		m_pEnemyMgr->GetEnemyBoss()->SealReleaseFlag();

		SetState(State::Dead);

		break;
	}

	m_pTween->Update();

	if (m_graphAnimTimer > 0.0f) m_graphAnimTimer -= Time::GetInstance().GetDeltaTime();
	else
	{
		m_currentGraph++;
		m_currentGraph = (m_currentGraph + 24) % 24;
		m_graphAnimTimer = m_graphAnimDuration;
	}
}

void BossKey::Draw()
{
	Vector3& pos = GetTransform().position;
	//DrawCircle(pos.x, pos.y, 10, 0xffff00);
	DrawGraph(pos.x, pos.y, m_graphsKey[m_currentGraph], 1);
}

void BossKey::UseKey()
{
	Vector3& pos = GetTransform().position;
	Vector3& bossPos = m_pEnemyMgr->GetEnemyBoss()->GetTransform().position;

	m_pTween->StartAnim(&pos.x, {
		Animation::Keyframe{pos.x, 0.0f, Animation::Ease::BackInOut},
		Animation::Keyframe{bossPos.x, 2.0f},
		});
	m_pTween->StartAnim(&pos.y, {
		Animation::Keyframe{pos.y, 0.0f, Animation::Ease::BackInOut},
		Animation::Keyframe{bossPos.y, 2.0f},
		});
	m_pTween->StartAnim(&m_animationTimer, {
		Animation::Keyframe{2.0f, 0.0f},
		Animation::Keyframe{0.0f, 2.0f},
		});

	m_action = Action::Use;
}
