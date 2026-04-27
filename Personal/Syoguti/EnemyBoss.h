#pragma once
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include "../../Object/GameObject.h"
#include "../Takagi/Weapon.h"

#include <array>
#include <memory>

class Player;

class BossBulletManager;

namespace {

	constexpr int kCharactorMotionNum = 32;
	constexpr int kEffectMotionNum = 32;
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
	/// ボスが封印解除されているかどうか
	/// </summary>
	/// <returns></returns>
	bool SealReleaseFlag();

	/// <summary>
	/// ボスの近距離攻撃がプレイヤーと当たっているかどうか
	/// </summary>
	/// <param name="other"></param>
	bool CheckHitCloseRangeAttackCollison(const Collision::Shape& other);

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
	/// プレイヤーのポインタをセットするセッター関数
	/// </summary>
	/// <param name="player"></param>
	/// <returns></returns>
	void const SetPlayer(Player* player) { m_pPlayer = player; }

	/// <summary>
	/// ボスの当たり判定を取得するゲッター関数
	/// </summary>
	/// <returns></returns>
	const Collision::Circle& GetCollider() const { return m_collsion; }

	/// <summary>
	/// ダメージを与える
	/// </summary>
	/// <param name="damage"></param>
	/// <returns></returns>
	bool Damage(const int damage);

	/// <summary>
	/// ダメージを与える
	/// </summary>
	/// <param name="damage"></param>
	/// <param name="wepon"></param>
	/// <param name="index"></param>
	/// <returns></returns>
	bool Damage(const int damage, int wepon, int index);

	/// <summary>
	/// ダメージフラグのリセット
	/// </summary>
	/// <param name="weapon"></param>
	/// <param name="index"></param>
	/// <returns></returns>
	bool ResetDamageFlag(int weapon, int index);

private:

	/// <summary>
	/// ボスの行動
	/// </summary>
	void Action();

	/// <summary>
	/// ボスのアニメーション
	/// </summary>
	void Status();

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
	/// ボスが倒されたかどうかチェック
	/// </summary>
	/// <returns></returns>
	bool CheckDeadFlag();

	/// <summary>
	/// ボスが倒された時の処理
	/// </summary>
	void Dead();

	/// <summary>
	/// ボスが倒された時のエフェクト
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	Vector3 DeadEffect(Vector3 position);

	/// <summary>
	/// ダメージフラグの範囲外を使おうとしたら範囲を追加する
	/// </summary>
	/// <param name="weapon"></param>
	/// <param name="index"></param>
	void CheckDamageFlagSize(int weapon, int index);

	/// <summary>
	/// ステータスを上げる関数
	/// </summary>
	void AttackUp();

private:

	/// <summary>
	/// 画像のハンドル
	/// </summary>
	int m_graphHandle[static_cast<int>(BossStatus::Max)][kCharactorMotionNum];

	/// <summary>
	/// モーション制御用のカウンタ
	/// </summary>
	int m_motionCounter;

	/// <summary>
	/// 描画するモーションのフレーム
	/// </summary>
	int m_motionFrame;

	/// <summary>
	/// 近距離攻撃のフラグ
	/// </summary>
	bool m_isCloseTheAttack;

	/// <summary>
	/// 近距離攻撃中のダメージ判定のフラグ
	/// </summary>
	bool m_isCloseTheAttackDamege;

	/// <summary>
	/// 画像の向き
	/// </summary>
	int m_direction;

	/// <summary>
	/// 弾の発射感覚
	/// </summary>
	float m_shotTimer;

	/// <summary>
	/// 座標
	/// </summary>
	// Transform m_transform;

	/// <summary>
	/// 円の当たり判定
	/// </summary>
	Collision::Circle m_collsion;

	std::array<std::vector<bool>, Weapon::Max> m_damageFlag;

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

	/// <summary>
	/// ボスの弾のポインタ
	/// </summary>
	std::unique_ptr<BossBulletManager> m_pBossBulletMgr;

	/// <summary>
	/// エフェクトを出す感覚で使うタイマー
	/// </summary>
	float m_effectTimer;

	/// <summary>
	/// エフェクトのカウント
	/// </summary>
	int m_effectCount;

	/// <summary>
	/// エフェクトのアニメーションを再生するまでの時間
	/// </summary>
	int m_effectMotionCounter;

	/// <summary>
	/// エフェクトのモーションのフレーム数
	/// </summary>
	int m_effectMotionFrame;

	/// <summary>
	/// エフェクトを描画するかどうか
	/// </summary>
	bool m_isEffect;

	/// <summary>
	/// エフェクトの座標
	/// </summary>
	Vector3 m_effectPos;

	/// <summary>
	/// エフェクトのグラフハンドル
	/// </summary>
	int m_efffectGraphHandle[kEffectMotionNum];

};

