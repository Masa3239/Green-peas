#include "EnemyMelee.h"
#include "../Personal/Takagi/Player.h"
#include "../Utility/Time.h"
#include "../Chara/AnimationController2D.h"
#include "../Chara/Collision.h"
#include "../System/SoundManager.h"

namespace
{
	constexpr float kDistanceSpeed = 100.0f;

	constexpr float kMeleeAttackCooltime = 1.0f;

	// 基礎ステータス
	constexpr EnemyBase::StatusParam kStatus = { 25, 25, 5, 5, 5 };
	// レベルごとの増加量
	constexpr int kHpPerLevel = 15;
	constexpr int kAtkPerLevel = 1.03f;
	constexpr int kDefPerLevel = 5;

	Animation::Animation2DData kAnimData[EnemyMelee::AnimType::Length] =
	{
		{ EnemyMelee::AnimType::EIdle, 6.0f, true, false},
		{ EnemyMelee::AnimType::ERun, 6.0f, true, false},
		{ EnemyMelee::AnimType::EAttack, 6.0f, false, true},
	};

	const char* const kGraphPathIdle = "Resource\\Golem Reinforced\\Golem_Armor_Idle.png";
	const char* const kGraphPathRun = "Resource\\Golem Reinforced\\Golem_Armor_Run.png";
	const char* const kGraphPathAttack = "Resource\\Golem Reinforced\\Golem_Armor_AttackB.png";
}

EnemyMelee::EnemyMelee(ObjectManager* objManager) :
	EnemyBase(objManager),
	m_attackCooltimeCounter(0.0f),
	m_animationController(),
	m_currentAnimation(AnimType::EIdle)
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

	m_animationController.Init();
	m_animationController.RegisterGraphHandle(AnimType::EIdle, kGraphPathIdle, 4, 4, 1, 64, 64);
	m_animationController.RegisterGraphHandle(AnimType::ERun, kGraphPathRun, 4, 4, 1, 64, 64);
	m_animationController.RegisterGraphHandle(AnimType::EAttack, kGraphPathAttack, 8, 4, 2, 64, 64);

	EnemyBase::Init();
}

void EnemyMelee::End()
{
	m_animationController.End();
}

void EnemyMelee::UpdateEnemy()
{
	UpdateAnimation();

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

			SoundManager::GetInstance().PlaySe(Sound::SE::Damage2);

			m_attackCooltimeCounter = kMeleeAttackCooltime;
		}
	}
}

void EnemyMelee::Draw()
{
	Vector3 pos = GetTransform().position;
	
	unsigned int color = (GetMyState() & EnemyBase::kStatePalsy) ? 0xffff00 : 0xff0000;

	DrawRotaGraph(pos.x, pos.y, 1, 0, m_animationController.GetCurrentGraph(), 1, GetPlayer()->GetTransform().position.x < pos.x);

#ifdef _DEBUG
	GetCollider().DebugDraw();
#endif
}

void EnemyMelee::Attack()
{
	GetPlayer()->Damage(GetStatusParam().attack);
}

void EnemyMelee::UpdateAnimation()
{
	if (m_animationController.IsForcePlay())
	{
		m_animationController.Update();
		return;
	}

	AnimType next = AnimType::EIdle;

	if (m_attackCooltimeCounter <= 0)
	{
		// 攻撃してたら
		if (GetCollider().CheckCollision(GetPlayer()->GetCircle()))
		{
			next = AnimType::EAttack;
		}
		// 移動してたら
		else next = AnimType::ERun;
	}

	if (m_currentAnimation != next)
	{
		ChangeAnimation(next);
	}

	m_animationController.Update();
}

void EnemyMelee::ChangeAnimation(AnimType next)
{
	m_currentAnimation = next;

	m_animationController.PlayAnimation(kAnimData[next]);
}
