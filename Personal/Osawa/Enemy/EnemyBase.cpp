#include "EnemyBase.h"
#include "../Chara/Collision.h"
#include "../Utility/Transform.h"
#include "../Utility/Time.h"
#include "../Personal/Takagi/Player.h"
#include "../Personal/Osawa/ExpOrb.h"

namespace
{
	constexpr Vector3 kColliderSize{ 25, 40, 0 };

	constexpr int kMaxHp = 30;
}

EnemyBase::EnemyBase(ObjectManager* objManager) :
	GameObject(objManager),
	m_hp(kMaxHp),
	m_collider(Collision::AABB{ Vector3(), kColliderSize }),
	m_variableStatus(0),
	m_pPlayer(nullptr)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
	m_collider.SetPosition(GetTransform().position);
	
	UpdateEnemy();

	// 当たり判定の座標更新
	m_collider.SetPosition(GetTransform().position);
}

bool EnemyBase::Damage(const int damage)
{
	m_hp -= damage;

	return true;
}

bool EnemyBase::Damage(const int damage, int weapon, int index)
{
	// 雷攻撃を受けたなら
	if (weapon == Weapon::Thunder)
	{
		// 痺れ状態ならダメージを受けない
		if (GetMyState() & kStatePalsy) return false;

		// 痺れ状態にする
		AddState(kStatePalsy);
	}

	// 足りない分を追加
	CheckDamageFlagSize(weapon, index);

	// すでにその武器がダメージを与えていたら失敗
	if (m_damageFlag[weapon][index]) return false;

	m_damageFlag[weapon][index] = true;

	m_hp -= damage;

	return true;
}

void EnemyBase::Dead()
{
	for (int i = 0; i < 10; i++)
	{
		auto exp = new ExpOrb(GetObjectManager());
		exp->Init();
		exp->SetPlayer(m_pPlayer);
		exp->GetTransform().position = GetTransform().position;
	}
}

bool EnemyBase::ResetDamageFlag(int weapon, int index)
{
	if (index >= m_damageFlag[weapon].size()) return false;

	m_damageFlag[weapon][index] = false;

	return true;
}

void EnemyBase::CheckDamageFlagSize(int weapon, int index)
{
	if (index < m_damageFlag[weapon].size()) return;

	for (int i = m_damageFlag[weapon].size() - 1; i < index; i++)
	{
		m_damageFlag[weapon].emplace_back(false);
	}
}
