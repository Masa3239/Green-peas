#pragma once
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include "../../Object/GameObject.h"
#include <vector>

class Player;

namespace {

	constexpr int kCharactorMotionNum = 25;
	//constexpr int kCharactorStatusNum = static_cast<int>(EnemyBoss::BossStatus::Max);
}

class EnemyBoss : public GameObject
{

public:

	// ボスの状態(アニメーション)
	enum class BossStatus {

		Idle,
		CloseRangeAttack,
		LongRangeAttack,
		ApproachMove,
		LeaveMove,
		Max
	};

	// ボスの行動
	enum class BossAction {

		Idle,
		CloseRangeAttack,
		LongRangeAttack,
		Max
	};

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyBoss(ObjectManager* objManager);

	/// <summary>
	/// 引数ありのコンストラクタ
	/// </summary>
	EnemyBoss(ObjectManager* objManager, Vector3 position);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyBoss() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 終了
	/// </summary>
	void End() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// ボスの最大HPを取得するゲッター関数
	/// </summary>
	/// <returns></returns>
	int GetBossMaxHp() { return m_maxHp; }

	/// <summary>
	/// ボスの現在のHPを取得するゲッター関数
	/// </summary>
	/// <returns></returns>
	int GetBossCurrentHp() { return m_currentHp; }

	/// <summary>
	/// ボスが封印解除されているかどうか
	/// </summary>
	/// <param name="maxKey"></param>
	/// <returns></returns>
	bool SealReleaseFlag(int maxKey);

	/// <summary>
	/// ボスの行動をランダムに決める
	/// </summary>
	void GetRandomAction();

	/// <summary>
	/// プレイヤーに近づく処理
	/// </summary>
	bool ApproachPlayer(const Vector3& playerPos);

	/// <summary>
	/// 目的地に近づく処理(プレイヤーから離れる処理)
	/// </summary>
	bool LeavePlayer(const Vector3& playerPos);

	/// <summary>
	/// 目的地を決める処理
	/// </summary>
	Vector3 TargetPos(const Vector3& playerPos);

	/// <summary>
	/// 近距離攻撃
	/// </summary>
	void CloseRangeAttack();

	/// <summary>
	/// 遠距離攻撃
	/// </summary>
	void LongRangeAttack();

	/// <summary>
	/// プレイヤーのポインタをセットするセッター関数
	/// </summary>
	/// <param name="player"></param>
	/// <returns></returns>
	void const SetPlayer(Player* player) {m_pPlayer = player; }

private:

	/// <summary>
	/// 画像のハンドル
	/// </summary>
	int m_graphHandle[static_cast<int>(BossStatus::Max)][kCharactorMotionNum];

	// モーション制御用のカウンタ
	int m_motionCounter;

	// 描画するモーションのフレーム
	int m_motionFrame;

	/// <summary>
	/// 座標
	/// </summary>
	// Transform m_transform;

	/// <summary>
	/// 円の当たり判定
	/// </summary>
	Collision::Circle m_collsion;

	/// <summary>
	/// 行動する時に使う円の判定
	/// </summary>
	Collision::Circle m_actionCollsion;

	/// <summary>
	/// 近距離攻撃の当たり判定
	/// </summary>
	Collision::AABB m_closeRangeAttackCollision;

	/// <summary>
	/// ボスの最大体力
	/// </summary>
	int m_maxHp;

	/// <summary>
	/// ボスの現在の体力
	/// </summary>
	int m_currentHp;

	/// <summary>
	/// ボスの攻撃力
	/// </summary>
	int m_attackPower;

	/// <summary>
	/// 鍵の数
	/// </summary>
	int m_getKey;

	/// <summary>
	/// 封印解除解除されたかどうか
	/// </summary>
	bool m_sealRelease;

	/// <summary>
	/// ボスのステータス
	/// </summary>
	BossStatus m_status;

	/// <summary>
	/// ボスの行動
	/// </summary>
	BossAction m_action;

	/// <summary>
	/// ランダムに行動を決めるまでの時間
	/// </summary>
	float m_getRandomTime;

	/// <summary>
	/// 目標の座標
	/// </summary>
	Vector3 m_targetPos;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	Player* m_pPlayer;

};

