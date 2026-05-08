#include "EnemyBase.h"
#include "../Chara/Collision.h"
#include "../Utility/Transform.h"
#include "../Utility/Time.h"
#include "../Personal/Takagi/Player.h"
#include "../Personal/Osawa/ExpOrb.h"
#include "../Enemy/EnemyManager.h"
#include "../Personal/Kimura/Map/Map.h"
#include "../System/SoundManager.h"

namespace
{
	constexpr Vector3 kColliderSize{ 25, 40, 0 };

	constexpr int kMaxHp = 30;

	// プレイヤーが怒り状態で倒された場合の回復量
	constexpr int kHealNum = 1;

	// プレイヤーを認識する距離
	constexpr float kStartRecognitionDistance = 600;
	
	// デスポーンする範囲
	constexpr float kDespawnDistance = 800;

	constexpr float kMapRangeOffset = 60;
}

EnemyBase::EnemyBase(ObjectManager* objManager) :
	GameObject(objManager),
	m_collider(Collision::AABB{ Vector3(), kColliderSize }),
	m_level(0),
	m_statusParam(StatusParam{ 0, 0, 0, 0, 0 }),
	m_variableStatus(0),
	m_pPlayer(nullptr),
	m_pEnemyMgr(nullptr),
	m_pMap(nullptr),
	m_isFixSpawn(false)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
	m_collider.SetPosition(GetTransform().position);
	
	auto player = GetPlayer();

	const Vector3& playerPos = player->GetTransform().position;
	Vector3& myPos = GetTransform().position;

	float sqDistance = (playerPos - myPos).GetSqLength();

	// 固定生成なら認識範囲を適用する
	if (m_isFixSpawn)
	{
		// 認識範囲外なら終了
		if (sqDistance >= kStartRecognitionDistance * kStartRecognitionDistance) return;
	}
	// 自然生成ならデスポーン範囲を適用する
	else
	{
		if (sqDistance >= kDespawnDistance * kDespawnDistance)
		{
			m_pEnemyMgr->RemoveEnemy(this);
			return;
		}
	}

	UpdateEnemy();

	ClampInRange();

	// 当たり判定の座標更新
	m_collider.SetPosition(GetTransform().position);

	SetDrawOrder(GetTransform().position.y);
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

	m_statusParam.exp *= m_pPlayer->GetExp();

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

	SoundManager::GetInstance().PlaySe(Sound::SE::Damage2);
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

void EnemyBase::ClampInRange()
{
	Vector3& pos = GetTransform().position;

	if (pos.x < kMapRangeOffset) pos.x = kMapRangeOffset;
	else
	if (pos.x > m_pMap->GetMapBlockNumX() * 40 - kMapRangeOffset) pos.x = m_pMap->GetMapBlockNumX() * 40 - kMapRangeOffset;

	if (pos.y < kMapRangeOffset) pos.y = kMapRangeOffset;
	else
	if (pos.y > m_pMap->GetMapBlockNumY() * 40 - kMapRangeOffset) pos.y = m_pMap->GetMapBlockNumY() * 40 - kMapRangeOffset;
}
