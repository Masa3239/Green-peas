#include "EnemyBoss.h"
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include "DxLib.h"
#include "../../Utility/MyRandom.h"
#include "../../Utility/Time.h"
#include "../Takagi/Player.h"

namespace {

	// 画像のファイルパス
	const char* const kSealBossGraphHandlePath = ".\\Resource\\EnemyBossTest1.png";
	const char* const kBossGraphHandlePath = ".\\Resource\\EnemyBossTest2.png";

	// 画像のサイズ
	constexpr float kGraphScale = 0.1f;

	// 円の当たり判定の半径
	constexpr float kCircleRadius = 50.0f;
	constexpr float kCircleActionRadius = 100.0f;
	constexpr Vector3 kCloseRangeCollisionSize = { 200.0f, 50.0f, 0.0f };
	// ボスの最大体力
	constexpr int kMaxHp = 100;

	// ボスの攻撃力
	constexpr int kAttackPower = 10;

	// ランダムに行動を決める時のインターバル
	constexpr float kRandomInterval = 3.0f;

	/// <summary>
	/// ボスの速さ
	/// </summary>
	constexpr float kSpeed = 100.0f;

}

EnemyBoss::EnemyBoss(ObjectManager* objManager) :
	GameObject(objManager),
	m_graphHandle(-1),
	m_transform(),
	m_collsion(m_transform.position, kCircleRadius),
	m_actionCollsion(m_transform.position, kCircleActionRadius),
	m_closeRangeAttackCollision(m_transform.position, kCloseRangeCollisionSize),
	m_maxHp(kMaxHp),
	m_currentHp(kMaxHp),
	m_attackPower(kAttackPower),
	m_getKey(0),
	m_sealRelease(false),
	m_status(BossStatus::Idle),
	m_getRandomTime(0.0f),
	m_pPlayer(nullptr)
{
	m_transform.Reset();
}

EnemyBoss::EnemyBoss(ObjectManager* objManager, Vector3 position) :
	GameObject(objManager),
	m_graphHandle(-1),
	m_transform(),
	m_collsion(m_transform.position, kCircleRadius),
	m_actionCollsion(m_transform.position, kCircleActionRadius),
	m_closeRangeAttackCollision(m_transform.position, kCloseRangeCollisionSize),
	m_maxHp(kMaxHp),
	m_currentHp(kMaxHp),
	m_attackPower(kAttackPower),
	m_getKey(0),
	m_sealRelease(false),
	m_status(BossStatus::Idle),
	m_getRandomTime(0.0f),
	m_pPlayer(nullptr)
{
	m_transform.Reset();
	m_transform.position = position;
}

void EnemyBoss::Init()
{

	m_graphHandle = LoadGraph(kSealBossGraphHandlePath);
}

void EnemyBoss::End()
{
	// 画像の破棄
	DeleteGraph(m_graphHandle);
}

void EnemyBoss::Update()
{

	// 当たり判定の更新
	m_collsion.SetPosition(m_transform.position);
	m_actionCollsion.SetPosition(m_transform.position);
	m_closeRangeAttackCollision.SetPosition(m_transform.position);

	// 時間を計測
	m_getRandomTime += Time::GetInstance().GetDeltaTime();

	if (m_getRandomTime >= kRandomInterval) {

		GetRandomStatus();
		m_getRandomTime = 0.0f;
	}

	switch (m_status)
	{
	case EnemyBoss::BossStatus::Idle:
		printfDx("アイドル\n");
		break;
	case EnemyBoss::BossStatus::CloseRangeAttack:
		ChangeTheAttack(m_pPlayer->GetCircle());
		printfDx("近距離攻撃\n");
		break;
	case EnemyBoss::BossStatus::LongRangeAttack:
		ChangeTheAttack(m_pPlayer->GetCircle());
		printfDx("遠距離攻撃攻撃\n");
		break;
	case EnemyBoss::BossStatus::ApproachMove:
		ApproachPlayer(m_pPlayer->GetTransform().position);
		printfDx("近づく\n");
		break;
	case EnemyBoss::BossStatus::LeaveMove:
		LeavePlayer(m_pPlayer->GetTransform().position);
		printfDx("離れる\n");
		break;
	default:
		printfDx("エラー\n");
		break;
	}
}

void EnemyBoss::Draw()
{

	// 画像の描画
	DrawRotaGraph(m_transform.position.x, m_transform.position.y, kGraphScale, 0.0f, m_graphHandle, TRUE);

	// 円の当たり判定の描画
	m_collsion.DebugDraw();
	m_actionCollsion.DebugDraw();

	
}

bool EnemyBoss::SealReleaseFlag(int maxKey)
{

	// 封印解除されたらtrueを返す
	if (m_sealRelease) return true;

	// 鍵がとられる度に加算
	m_getKey++;

	// 指定された値より大きくなったら
	if (m_getKey >= maxKey) {

		// 封印解除されている(true)
		m_sealRelease = true;
	}

	// 結果を返す
	return m_sealRelease;
}

void EnemyBoss::GetRandomStatus()
{

	// 次に選ぶ行動をランダムで取得
	BossStatus nextStatus = static_cast<BossStatus>(MyRandom::Int(0, static_cast<int>(BossStatus::Max) - 1));

	// 現在のステータスに入れる
	m_status = nextStatus;
}

void EnemyBoss::ApproachPlayer(const Vector3& playerPos)
{

	// 方向ベクトル
	Vector3 direction = playerPos - m_transform.position;

	// 距離チェック
	if (direction.GetSqLength() <= 3000.0f) return;

	// 正規化
	direction = direction.GetNormalize();

	// スピード
	float speed = kSpeed;

	// 移動
	m_transform.position += direction * speed * Time::GetInstance().GetDeltaTime();
}

void EnemyBoss::LeavePlayer(const Vector3& playerPos)
{
	// 方向ベクトル
	Vector3 direction = playerPos - m_transform.position;

	// 距離チェック
	if (direction.GetSqLength() <= 0.0001f) return;

	// 正規化
	direction = direction.GetNormalize();

	// スピード
	float speed = -kSpeed;

	// 移動
	m_transform.position += direction * speed * Time::GetInstance().GetDeltaTime();
}

void EnemyBoss::CloseRangeAttack()
{
	// 近距離攻撃の当たり判定の描画
	m_closeRangeAttackCollision.DebugDraw();
}

void EnemyBoss::LongRangeAttack()
{
	printfDx("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n");
}

void EnemyBoss::ChangeTheAttack(const Collision::Shape& other)
{

	// 引数(プレイヤーの当たり判定と当たっていたら)
	if (m_actionCollsion.CheckCollision(other)) {
		CloseRangeAttack();
	}
	else {
		LongRangeAttack();
	}
}

