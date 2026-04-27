#include "EnemyMelee.h"
#include "../Personal/Takagi/Player.h"
#include "../Utility/Time.h"
#include "../Chara/Collision.h"

namespace
{
	constexpr float kDistanceSpeed = 100.0f;

	constexpr float kMeleeAttackCooltime = 1.0f;

	// 基礎ステータス
	constexpr EnemyBase::StatusParam kStatus = { 25, 25, 5, 5, 5 };
	// レベルごとの増加量
	constexpr int kHpPerLevel = 8;
	constexpr int kAtkPerLevel = 1.03f;
	constexpr int kDefPerLevel = 5;

	const char* const kGraphPath = "";
}

EnemyMelee::EnemyMelee(ObjectManager* objManager) :
	EnemyBase(objManager),
	m_attackCooltimeCounter(0.0f),
	m_animFrame(0),
	m_animFrameCounter(0)
{
}

EnemyMelee::~EnemyMelee()
{
}

void EnemyMelee::Init()
{
	StatusParam status = kStatus;
	status.hp += kHpPerLevel * GetLevel();
	status.maxHp = status.hp;
	status.attack += std::pow(kAtkPerLevel, GetLevel());
	status.defence += kDefPerLevel * GetLevel();
	SetStatusParam(status);

	//LoadDivGraph(kGraphPath, kAnimFrameNum, kAnimFrameNum, 1, 384, 128, m_graphs);
}

void EnemyMelee::End()
{
	for (auto& graph : m_graphs)
	{
		DeleteGraph(graph);
	}
}

void EnemyMelee::UpdateEnemy()
{
	if (m_attackCooltimeCounter > 0)
	{
		m_attackCooltimeCounter -= Time::GetInstance().GetDeltaTime();
	}
	else
	{
		auto player = GetPlayer();
	
		const Vector3& targetPos = player->GetTransform().position;
		Vector3& myPos = GetTransform().position;

		if (targetPos == myPos) return;

		Vector3 vec = (targetPos - myPos).GetNormalize();

		myPos += vec * kDistanceSpeed * Time::GetInstance().GetDeltaTime();

		if (GetCollider().CheckCollision(GetPlayer()->GetCircle()))
		{
			Attack();

			m_attackCooltimeCounter = kMeleeAttackCooltime;
		}
	}

	if (m_animFrameCounter > 0)
	{
		m_animFrameCounter -= Time::GetInstance().GetDeltaTime();
	}
	else
	{
		m_animFrame++;
		m_animFrameCounter = 0.1f;

		if (m_animFrame >= kAnimFrameNum) m_animFrame = 0;
	}
}

void EnemyMelee::Draw()
{
	Vector3 pos = GetTransform().position;
	
	unsigned int color = (GetMyState() & EnemyBase::kStatePalsy) ? 0xffff00 : 0xff0000;

	DrawBox(pos.x - 9, pos.y - 30, pos.x + 9, pos.y, color, 1);

	//DrawRotaGraph(pos.x, pos.y - 32, 1, 0, m_graphs[m_animFrame], 1, GetPlayer()->GetTransform().position.x < pos.x);

#ifdef _DEBUG
	GetCollider().DebugDraw();
#endif
}

void EnemyMelee::Attack()
{
	GetPlayer()->Damage(GetStatusParam().attack);
}
