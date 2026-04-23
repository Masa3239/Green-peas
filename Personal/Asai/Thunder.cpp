#include "Thunder.h"
#include"../Asai/BulletBase.h"
#include"../Osawa/Enemy/EnemyBase.h"
#include"../Osawa/Enemy/EnemyManager.h"

#include<DxLib.h>
#include<math.h>
#include"../../Utility/Time.h"
#include"../Takagi/Weapon.h"

namespace {
	//当たり判定のサイズ
	constexpr float kCollisionBallSize = 20.0f;
	constexpr float kCollisionFieldSize = 70.0f;
	constexpr float kCollisionInfectionSize = 80.0f;

	//移動速度
	constexpr float kSpeed = 120.0f;
	//移動の最大距離
	constexpr float kMaxMoveDistance = 500;

	//フィールドに残る時間
	constexpr float kFieldLifetime = 0.3f;

	//伝染回数
	constexpr int kMaxInfection = 5;
	//伝染感覚
	constexpr float kInterval = 1.0f;

}


Thunder::Thunder(ObjectManager* objManager):
	BulletBase(objManager),
	m_state(State::Ball),
	m_fieldElapsedTime(0),
	m_infectionCount(0),
	m_infectionTimer(0),
	m_pEnemyMgr(nullptr),
	m_pEnemies()
{
	m_pEnemies.clear();
}

void Thunder::Init()
{
}

void Thunder::Update()
{

	//非アクティブならリターン
	if (!m_isActive)return;

	switch (m_state)
	{
	case Thunder::State::Ball:
		//State::Ballの更新処理
		UpdateBall();
		break;

	case Thunder::State::Field:
		//State::Fieldの更新処理
		UpdateField();
		break;

	case Thunder::State::Infection:
		UpdateInfection();
		break;

	default:
		break;
	}

}

void Thunder::Draw()
{
	//非アクティブならリターン
	if (!m_isActive)return;

	m_circle.DebugDraw();

	//for (auto enemy : m_pEnemies) {

	//	DrawCircle(enemy->GetTransform().position.x, enemy->GetTransform().position.y, kCollisionInfectionSize * m_scale, 0xffffff, FALSE);

	//}

	float collisionSize = 0;

	switch (m_state)
	{
	case Thunder::State::Ball:
		collisionSize = kCollisionBallSize;
		break;
	case Thunder::State::Infection:
		collisionSize = kCollisionInfectionSize;
		break;
	default:
		break;
	}

	//丸を描画
	DrawCircle(GetTransform().position.x, GetTransform().position.y, collisionSize * m_scale, TRUE, 0xffff00);

}

void Thunder::DebugDraw()
{
	//非アクティブならリターン
	if (!m_isActive)return;

	printfDx("m_pEnemies.size() %d\n", m_pEnemies.size());
	printfDx("m_infectionCount %d\n", m_infectionCount);
	printfDx("m_infectionTimer %f\n", m_infectionTimer);
	printfDx("state%d\n", static_cast<int>(m_state));

}

void Thunder::End()
{
}

void Thunder::Shot(Transform transform)
{
	//セット
	GetTransform() = transform;
	//アクティブにする
	m_isActive = true;
	//スポーン位置を設定
	m_spawnPos = transform.position;
	//玉の状態にする
	m_state = State::Ball;
	//当たり判定を変更する
	m_circle = Collision::Circle(GetTransform().position, kCollisionBallSize * m_scale);

}

void Thunder::SetScale(float scale)
{
	//m_scaleの変更
	m_scale = scale;
	//当たり判定のサイズを変更
	m_circle = Collision::Circle(GetTransform().position, kCollisionBallSize * scale);

}

void Thunder::UpdateBall()
{
	//デルタタイムを取得
	float deltaTime = Time::GetInstance().GetDeltaTime();

	//移動
	GetTransform().position.x += cosf(GetTransform().rotation.z) * kSpeed * deltaTime;
	GetTransform().position.y += sinf(GetTransform().rotation.z) * kSpeed * deltaTime;

	//当たり判定を更新
	m_circle.SetPosition(GetTransform().position);
	//当たった敵を取得
	m_pEnemies = (m_pEnemyMgr->GetHitEnemies(m_circle, 1));

	//移動距離を取得
	float distance = (m_spawnPos - GetTransform().position).GetSqLength();
	//移動距離の最大値じゃないならスルー
	if (distance <= kMaxMoveDistance * kMaxMoveDistance)return;

	//移動距離の最大になったら状態を変更
	m_state = State::Infection;
	m_circle = Collision::Circle(GetTransform().position, kCollisionInfectionSize * m_scale);

	//当たり前を更新
	m_circle.SetPosition(GetTransform().position);
	//当たった敵を取得
	m_pEnemies = (m_pEnemyMgr->GetHitEnemies(m_circle, 1));

}

void Thunder::UpdateField()
{
	//タイマーを加算
	m_fieldElapsedTime += Time::GetInstance().GetDeltaTime();
	

	//消える時間じゃないならスルー
	if (m_fieldElapsedTime < kFieldLifetime)return;

	//非アクティブにする
	//m_isActive = false;

	//伝染
	m_state = State::Infection;
	//当たり前を更新
	m_circle.SetPosition(GetTransform().position);
	//当たった敵を取得
	m_pEnemies = (m_pEnemyMgr->GetHitEnemies(m_circle, 1));

}

void Thunder::UpdateInfection()
{
	//タイマーを加算
	m_infectionTimer += Time::GetInstance().GetDeltaTime();

	//時間じゃないならスルー
	if (m_infectionTimer <= kInterval)return;
	//タイマーをリセット
	m_infectionTimer = 0;
	//伝染回数を加算する
	m_infectionCount++;

	std::vector<EnemyBase*>enemies;
	enemies.clear();

	//m_pEnemies.clear();
	m_pEnemies.insert(m_pEnemies.end(), enemies.begin(), enemies.end());

	//雷の当たった敵を調べる
	for (auto& enemy : m_pEnemies) {
		//当たり判定を作る
		auto circle = Collision::Circle(enemy->GetTransform().position, kCollisionInfectionSize * m_scale);
		//当たっていなければスルー
		m_pEnemyMgr->CheckHitEnemies(circle, 3, 1, 1, Weapon::Sword, 1);

	}

	for (auto& enemy : m_pEnemies)
	{
		auto circle = Collision::Circle(enemy->GetTransform().position, kCollisionInfectionSize * m_scale);

		auto check = (m_pEnemyMgr->GetHitEnemies(circle, EnemyBase::kStatePalsy));

		enemies.insert(enemies.end(), check.begin(), check.end());

	}

	m_pEnemyMgr->ResetEnemyDamageFlag(Weapon::Sword, 1);

	if (m_infectionCount > kMaxInfection) {
		m_isActive = false;
		m_infectionCount = 0;
		m_infectionTimer = 0;
	}

}
