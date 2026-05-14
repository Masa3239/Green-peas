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
	m_statusParam(StatusParam{ 0, 0, 0, 0, 0 }),
	m_level(0),
	m_variableStatus(0),
	m_isFixSpawn(false),
	m_collider(Collision::AABB{ Vector3(), kColliderSize }),
	m_damageFlag(),
	m_pPlayer(nullptr),
	m_pEnemyMgr(nullptr),
	m_pMap(nullptr)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
	m_collider.SetPosition(GetTransform().position);
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
	ResizeDamageFlag(weapon, index);

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

	// 経験値の倍率を取得
	m_statusParam.exp *= m_pPlayer->GetExp();

	// 経験値を10個分と1個分だけで生成する
	int num10 = m_statusParam.exp / 10;
	int num1 = m_statusParam.exp % 10;
	for (int i = 0; i < num10; i++)
	{
		GenerateExp(10);
	}
	for (int i = 0; i < num1; i++)
	{
		GenerateExp(1);
	}

	SoundManager::GetInstance().PlaySe(Sound::SE::Damage2);
}

void EnemyBase::ResetDamageFlag(int weapon, int index)
{
	// 範囲外なら早期リターン
	if (index >= m_damageFlag[weapon].size()) return;

	// フラグを下ろす
	m_damageFlag[weapon][index] = false;
}

void EnemyBase::ResizeDamageFlag(int weapon, int index)
{
	// 範囲内なら変更をする必要はないため早期リターン
	if (index < m_damageFlag[weapon].size()) return;

	// 足りない分を追加
	for (int i = 0; i < index - m_damageFlag[weapon].size() + 1; i++)
	{
		m_damageFlag[weapon].emplace_back(false);
	}
}

void EnemyBase::ClampInRange()
{
	Vector3& pos = GetTransform().position;
	
	// 端の座標を定義
	const float leftEdge = kMapRangeOffset;
	const float rightEdge = m_pMap->GetMapBlockNumX() * 40 - kMapRangeOffset;
	const float topEdge = kMapRangeOffset;
	const float bottomEdge = m_pMap->GetMapBlockNumY() * 40 - kMapRangeOffset;

	if (pos.x < leftEdge) pos.x = leftEdge;
	else if (pos.x > rightEdge) pos.x = rightEdge;

	if (pos.y < topEdge) pos.y = topEdge;
	else if (pos.y > bottomEdge) pos.y = bottomEdge;
}

void EnemyBase::GenerateExp(int amount)
{
	auto exp = new ExpOrb(GetObjectManager(), amount);
	exp->Init();
	exp->SetPlayer(m_pPlayer);
	exp->GetTransform().position = GetTransform().position;
}
