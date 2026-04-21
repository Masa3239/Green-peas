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
	constexpr float kGraphScale = 1.0f;

	// 円の当たり判定の半径
	constexpr float kCircleRadius = 60.0f;
	constexpr float kCircleActionRadius = 100.0f;
	constexpr Vector3 kCollisionOffset = { 0.0f , 50.0f, 0.0f };
	constexpr Vector3 kCloseRangeCollisionSize = { 200.0f, 50.0f, 0.0f };

	// ボスの挙動で使うプレイヤーのオフセットの値
	constexpr float kPlayerOffsetPos = 200.0f;

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
	m_motionCounter(0),
	m_motionFrame(0),
	GameObject(objManager),
	m_collsion(GetTransform().position, kCircleRadius),
	m_actionCollsion(GetTransform().position, kCircleActionRadius),
	m_closeRangeAttackCollision(GetTransform().position, kCloseRangeCollisionSize),
	m_maxHp(kMaxHp),
	m_currentHp(kMaxHp),
	m_attackPower(kAttackPower),
	m_getKey(0),
	m_sealRelease(false),
	m_status(BossStatus::Idle),
	m_action(BossAction::Idle),
	//m_action(BossAction::Idle),
	m_getRandomTime(0.0f),
	m_targetPos(0.0f, 0.0f, 0.0f),
	m_pPlayer(nullptr)
{
	for (int i = 0; i < static_cast<int>(BossStatus::Max); i++) {

		for (int j = 0;j < kCharactorMotionNum; j++) {
			m_graphHandle[i][j] = -1;
		}
	}
	GetTransform().Reset();
}

EnemyBoss::EnemyBoss(ObjectManager* objManager, Vector3 position) :
	m_motionCounter(0),
	m_motionFrame(0),
	GameObject(objManager),
	m_collsion(GetTransform().position , kCircleRadius),
	m_actionCollsion(GetTransform().position, kCircleActionRadius),
	m_closeRangeAttackCollision(GetTransform().position, kCloseRangeCollisionSize),
	m_maxHp(kMaxHp),
	m_currentHp(kMaxHp),
	m_attackPower(kAttackPower),
	m_getKey(0),
	m_sealRelease(false),
	m_status(BossStatus::Idle),
	m_action(BossAction::Idle),
	//m_action(BossAction::Idle),
	m_getRandomTime(0.0f),
	m_targetPos(0.0f, 0.0f, 0.0f),
	m_pPlayer(nullptr)
{

	for (int i = 0; i < static_cast<int>(BossStatus::Max); i++) {

		for (int j = 0;j < kCharactorMotionNum; j++) {
			m_graphHandle[i][j] = -1;
		}
	}

	GetTransform().Reset();
	GetTransform().position = position;
}

void EnemyBoss::Init()
{
	LoadDivGraph(".\\Resource\\Dino Rex\\dino_rex_idle.png",
		5, 5, 1, 128, 128, m_graphHandle[static_cast<int>(BossStatus::Idle)]);

	LoadDivGraph(".\\Resource\\Dino Rex\\dino_rex_move.png",
		8, 8, 1, 384, 128, m_graphHandle[static_cast<int>(BossStatus::LeaveMove)]);

	LoadDivGraph(".\\Resource\\Dino Rex\\dino_rex_attack_B_2_loop.png",
		5, 5, 1, 384, 128, m_graphHandle[static_cast<int>(BossStatus::ApproachMove)]);

	LoadDivGraph(".\\Resource\\Dino Rex\\dino_rex_attack_A.png",
		21, 21, 1, 384, 128, m_graphHandle[static_cast<int>(BossStatus::CloseRangeAttack)]);

	LoadDivGraph(".\\Resource\\Dino Rex\\dino_rex_ability_black.png",
		25, 25, 1, 384, 128, m_graphHandle[static_cast<int>(BossStatus::LongRangeAttack)]);


	/*
	m_motionMaxFrame[static_cast<int>(BossStatus::Idle)] = 5;
	m_isLoop[static_cast<int>(BossStatus::Idle)] = true;

	m_motionMaxFrame[static_cast<int>(BossStatus::LeaveMove)] = 8;
	m_isLoop[static_cast<int>(BossStatus::LeaveMove)] = true;

	m_motionMaxFrame[static_cast<int>(BossStatus::ApproachMove)] = 5;
	m_isLoop[static_cast<int>(BossStatus::ApproachMove)] = true;

	m_motionMaxFrame[static_cast<int>(BossStatus::CloseRangeAttack)] = 21;
	m_isLoop[static_cast<int>(BossStatus::CloseRangeAttack)] = false;

	m_motionMaxFrame[static_cast<int>(BossStatus::LongRangeAttack)] = 25;
	m_isLoop[static_cast<int>(BossStatus::LongRangeAttack)] = false;
	*/
}

void EnemyBoss::End()
{

	for (int i = 0; i < static_cast<int>(EnemyBoss::BossStatus::Max); i++) {

		for (int j = 0; j < kCharactorMotionNum; j++) {

			// 画像の破棄
			DeleteGraph(m_graphHandle[i][j]);
		}

	}
}

void EnemyBoss::Update()
{

	// 当たり判定の更新
	m_collsion.SetPosition(GetTransform().position);
	m_actionCollsion.SetPosition(GetTransform().position);
	m_closeRangeAttackCollision.SetPosition(GetTransform().position);

	if (m_status == BossStatus::Idle) {

		// 時間を計測
		m_getRandomTime += Time::GetInstance().GetDeltaTime();
	}

	if (m_getRandomTime >= kRandomInterval) {

		GetRandomStatus();
		m_getRandomTime = 0.0f;
	}

	
	switch (m_action)
	{
	case EnemyBoss::BossAction::Idle:
		break;
	case EnemyBoss::BossAction::CloseRangeAttack:
		if (ApproachPlayer(m_pPlayer->GetTransform().position)) {
			CloseRangeAttack();
		}
		break;
	case EnemyBoss::BossAction::LongRangeAttack:
		if (LeavePlayer(m_targetPos)) {
			LongRangeAttack();
		}
		break;
	default:
		break;
	}
	
	
	switch (m_status)
	{
	case EnemyBoss::BossStatus::Idle:
		// GetRandomStatus();
		printfDx("アイドル\n");
		break;
	case EnemyBoss::BossStatus::CloseRangeAttack:
		
		break;
	case EnemyBoss::BossStatus::LongRangeAttack:
		
		break;
	case EnemyBoss::BossStatus::ApproachMove:
		printfDx("近づく\n");
		break;
	case EnemyBoss::BossStatus::LeaveMove:
		printfDx("離れる\n");
		break;
	default:
		printfDx("エラー\n");
		break;
	}
	
	
}

void EnemyBoss::Draw()
{

	m_motionCounter++;
	if (m_motionCounter % 5 == 0) {

		m_motionFrame++;

		if (m_graphHandle[static_cast<int>(m_status)][m_motionFrame] == -1) {

			switch (m_status)
			{
			case EnemyBoss::BossStatus::Idle:
			case EnemyBoss::BossStatus::ApproachMove:
			case EnemyBoss::BossStatus::LeaveMove:
				break;
			case EnemyBoss::BossStatus::CloseRangeAttack:
			case EnemyBoss::BossStatus::LongRangeAttack:
				m_status = BossStatus::Idle;
				m_action = BossAction::Idle;
				break;
			default:
				break;
			}
				m_motionFrame = 0;
			// 現在のステータスがループアニメーションなら
			if (m_isLoop[static_cast<int>(m_status)]) {
			}
			else {
			}
		}

		m_motionCounter = 0;
	}

	printfDx("ボスaaaaa%d\n",static_cast<int>(m_status));

	// 画像の描画
	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y, kGraphScale, 0.0f, 
		m_graphHandle[static_cast<int>(m_status)][m_motionFrame], TRUE);

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

	/*
	// 次に選ぶ行動をランダムで取得
	BossStatus nextStatus = static_cast<BossStatus>(MyRandom::Int(0, static_cast<int>(BossStatus::Max) - 1));

	// 現在のステータスに入れる
	m_status = nextStatus;

	if (m_status == BossStatus::LeaveMove) {

		m_targetPos = TargetPos(m_pPlayer->GetTransform().position);
	}
	*/
	

	// 次に選ぶ行動をランダムで取得
	BossAction nextAction = static_cast<BossAction>(MyRandom::Int(0, static_cast<int>(BossAction::Max) - 1));

	// 現在のステータスに入れる
	m_action = nextAction;
}

bool EnemyBoss::ApproachPlayer(const Vector3& playerPos)
{

	// 方向ベクトル
	Vector3 direction = playerPos - GetTransform().position;

	// 距離チェック
	if (direction.GetSqLength() <= 3000.0f) return true;

	m_status = BossStatus::ApproachMove;

	// 正規化
	direction = direction.GetNormalize();

	// スピード
	float speed = kSpeed;

	// 移動
	GetTransform().position += direction * speed * Time::GetInstance().GetDeltaTime();
	return false;
}

bool EnemyBoss::LeavePlayer(const Vector3& playerPos)
{
	// 方向ベクトル
	Vector3 direction = playerPos - GetTransform().position;

	// 距離チェック
	if (direction.GetSqLength() <= 10000.0f) return true;

	m_status = BossStatus::LeaveMove;

	// 正規化
	direction = direction.GetNormalize();

	// スピード
	float speed = -kSpeed;

	// 移動
	GetTransform().position += direction * speed * Time::GetInstance().GetDeltaTime();
	return false;
}

Vector3 EnemyBoss::TargetPos(const Vector3& playerPos)
{

	// プレイヤーから離した距離を用意
	float offsetX = kPlayerOffsetPos;
	float offsetY = kPlayerOffsetPos;

	// ランダムで+か-の値を決める
	int randomX = MyRandom::Int(0, 1) == 0 ? 1 : -1;
	int randomY = MyRandom::Int(0, 1) == 0 ? 1 : -1;

	Vector3 targetPos;

	// XとYの座標を計算する
	targetPos.x = playerPos.x + offsetX * randomX;
	targetPos.y = playerPos.y + offsetY * randomY;
	targetPos.z = playerPos.z;

	// 計算結果を返す
	return targetPos;
}

void EnemyBoss::CloseRangeAttack()
{
	m_status = BossStatus::CloseRangeAttack;
	// 近距離攻撃の当たり判定の描画
	m_closeRangeAttackCollision.DebugDraw();
	printfDx("近距離攻撃\n");
}

void EnemyBoss::LongRangeAttack()
{
	
	m_status = BossStatus::LongRangeAttack;
	printfDx("遠距離攻撃攻撃\n");
}


