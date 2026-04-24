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

	// プレイヤーが怒り状態で倒された場合の回復量
	constexpr int kHealNum = 1;

	// プレイヤーを認識する距離
	constexpr float kStartRecognitionDistance = 600;
}

EnemyBase::EnemyBase(ObjectManager* objManager) :
	GameObject(objManager),
	m_collider(Collision::AABB{ Vector3(), kColliderSize }),
	m_level(0),
	m_statusParam(StatusParam{ 0, 0, 0, 0, 0 }),
	m_variableStatus(0),
	m_pPlayer(nullptr),
	m_pEnemyMgr(nullptr),
	m_isFixSpawn(false)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
	m_collider.SetPosition(GetTransform().position);
	
	// 固定生成なら認識範囲を適用する
	if (m_isFixSpawn)
	{
		auto player = GetPlayer();

		const Vector3& playerPos = player->GetTransform().position;
		Vector3& myPos = GetTransform().position;

		float sqDistance = (playerPos - myPos).GetSqLength();

		// 認識範囲外なら終了
		if (sqDistance >= kStartRecognitionDistance * kStartRecognitionDistance) return;
	}

	UpdateEnemy();

	// 当たり判定の座標更新
	m_collider.SetPosition(GetTransform().position);
}

bool EnemyBase::Damage(const int damage)
{
	m_statusParam.hp -= damage;

	return true;
}

bool EnemyBase::Damage(const int damage, int weapon, int index)
{
	// 雷攻撃を受けたなら
	if (weapon == Weapon::Volt)
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

	m_statusParam.hp -= damage;

	return true;
}

void EnemyBase::Dead()
{
	// もしプレイヤーが怒り状態だったら回復させる
	if (m_pPlayer->CheckAnger())
	{
		m_pPlayer->Heal(kHealNum);
	}

	int num10 = m_statusParam.exp / 10;
	int num1 = m_statusParam.exp % 10;
	for (int i = 0; i < num10; i++)
	{
		auto exp = new ExpOrb(GetObjectManager(), 10);
		exp->Init();
		exp->SetPlayer(m_pPlayer);
		exp->GetTransform().position = GetTransform().position;
	}
	for (int i = 0; i < num1; i++)
	{
		auto exp = new ExpOrb(GetObjectManager(), 1);
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
