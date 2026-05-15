#include "EnemyBase.h"
//#include "../Chara/Collision.h"
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

	// プレイヤーが怒り状態で倒された場合の回復割合
	constexpr float kHealRate = 0.01f;

	// プレイヤーを認識する距離
	constexpr float kStartRecognitionDistance = 600;
	
	// デスポーンする範囲
	constexpr float kDespawnDistance = 800;

	// 一番端の座標
	constexpr float kMapRangeOffset = 60;
}

EnemyBase::EnemyBase(ObjectManager* objManager) :
	GameObject(objManager),
	m_statusParam(StatusParam{ 0, 0, 0, 0 }),
	m_level(0),
	m_variableStatus(0),
	m_isFixSpawn(false),
	m_animator(),
	m_currentAnimation(0),
	m_damageFlag(),
	m_pPlayer(nullptr),
	m_pEnemyMgr(nullptr),
	m_pMap(nullptr)
{
}

void EnemyBase::Init()
{
}

void EnemyBase::End()
{
	m_animator.End();
}

void EnemyBase::Update()
{
	if (!CheckActive()) return;

	UpdateEnemy();

	ClampInRange();

	UpdateAnimation();
	
	SetDrawOrder(GetTransform().position.y);
}

bool EnemyBase::Damage(const int damage, int weapon, int index)
{
	if (Paralyze(weapon)) return false;

	// 足りない配列を追加
	ResizeDamageFlag(weapon, index);

	// すでにその武器がダメージを与えていたら失敗
	if (m_damageFlag[weapon][index]) return false;

	// ダメージフラグを立てる
	m_damageFlag[weapon][index] = true;

	// ダメージを受ける
	m_statusParam.hp -= damage;

	return true;
}

void EnemyBase::Dead()
{
	HealPlayer();

	DropExp();

	SoundManager::GetInstance().PlaySe(Sound::SE::Damage2);
}

void EnemyBase::ResetDamageFlag(int weapon, int index)
{
	// 範囲外なら早期リターン
	if (index >= m_damageFlag[weapon].size()) return;

	// フラグを下ろす
	m_damageFlag[weapon][index] = false;
}

void EnemyBase::ChangeAnimation(int next)
{
	if (next >= m_animData.size()) return;
	if (m_currentAnimation == next) return;

	m_currentAnimation = next;
	m_animator.PlayAnimation(m_animData[next]);
}

void EnemyBase::UpdateAnimation()
{
	if (!m_animator.IsForcePlay())
	{
		BranchAnimation();
	}

	m_animator.Update();
}

bool EnemyBase::CheckActive()
{
	const Vector3& playerPos = GetPlayer()->GetTransform().position;
	const Vector3& myPos = GetTransform().position;
	float sqDistance = (playerPos - myPos).GetSqLength();

	if (ApplyRecognitionRange(sqDistance)) return false;
	if (ApplyDespawnRange(sqDistance)) return false;

	return true;
}

bool EnemyBase::ApplyRecognitionRange(float sqDistance)
{
	// 固定生成ではないなら早期リターン
	if (!m_isFixSpawn) return false;

	if (sqDistance < kStartRecognitionDistance * kStartRecognitionDistance) return false;

	return true;
}

bool EnemyBase::ApplyDespawnRange(float sqDistance)
{
	// 自然生成ではないなら早期リターン
	if (m_isFixSpawn) return false;

	if (sqDistance < kDespawnDistance * kDespawnDistance) return false;
	
	m_pEnemyMgr->RemoveEnemy(this);
	return true;
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

bool EnemyBase::Paralyze(const int weapon)
{
	// 雷攻撃を受けてないなら早期リターン
	if (weapon != Weapon::Volt) return false;
	
	// 痺れ状態ならダメージを受けない
	if (GetMyState() & kStatePalsy) return true;

	// 痺れ状態にする
	AddState(kStatePalsy);

	return false;
}

void EnemyBase::ResizeDamageFlag(int weapon, int index)
{
	// 範囲内なら変更をする必要はないため早期リターン
	if (index < m_damageFlag[weapon].size()) return;

	// 足りない分を追加
	for (int i = m_damageFlag[weapon].size() - 1; i < index; i++)
	{
		m_damageFlag[weapon].emplace_back(false);
	}
}

void EnemyBase::HealPlayer()
{
	// もしプレイヤーが怒り状態ではなかったら早期リターン
	if (!m_pPlayer->CheckAnger()) return;
	
	// HPを割合で回復
	float maxHp = m_pPlayer->GetGaugeMaxValue(Player::GaugeType::Hp);
	m_pPlayer->Heal(maxHp * kHealRate);
}

void EnemyBase::DropExp()
{
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
}

void EnemyBase::GenerateExp(int amount)
{
	auto exp = new ExpOrb(GetObjectManager(), amount);
	exp->Init();
	exp->SetPlayer(m_pPlayer);
	exp->GetTransform().position = GetTransform().position;
}
