#pragma once
#include"../Chara/Collision.h"
#include"../Utility/Transform.h"
#include"../Utility/Vector3.h"
#include"../../Object/GameObject.h"
//#include"../../System/InputPad.h"
#include"PlayerStatus.h"
#include"PlayerBuff.h"
#include<memory>
#include<vector>

namespace {
	//enum class Status {
	//	Stop,		// 停止状態
	//	Walk,		// 歩行状態
	//	Dash,		// ダッシュ(回避)
	//	Max
	//};
	
	// プレイヤーのアニメーションの枚数
	constexpr int kPlayerFrame = 4;
	// プレイヤーのアニメーションで何枚目のフレームを使うか
	constexpr int kFrame[kPlayerFrame] = { 0,1,2,1 };
	constexpr int kWeaponMaxNum = 2;
}

class Gauge;
class Camera;
class Weapon;
class EnemyManager;
class ItemManager;
//class PlayerBuff;
namespace Character {
	enum class Job {
		Warrior,	// 戦士
		Hunter,		// 狩人
		Wizard,		// 魔法使い
		Max
	};
}

class Player:public GameObject {
public:
	enum class GaugeType {
		Hp,
		Stamina,
		Anger,
		Exp,
		Max
	};

	/// <summary>
	/// プレイヤーのコンストラクタ
	/// メンバ変数の初期設定を行う
	/// </summary>
	Player(ObjectManager* objManager);

	/// <summary>
	/// プレイヤーのデストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init()override;
	/// <summary>
	/// 終了処理
	/// </summary>
	void End()override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update()override;
	/// <summary>
	/// プレイヤー移動の更新処理
	/// </summary>
	void Move();
	/// <summary>
	/// 移動量の計算
	/// </summary>
	void MoveAmount();
	/// <summary>
	/// スタミナを消費するかどうか
	/// </summary>
	/// <param name="stamina"></param>
	void Dash(bool stamina=true);
	/// <summary>
	/// 移動速度の更新処理
	/// </summary>
	void SpeedUpdate();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw()override;
	/// <summary>
	/// デバッグ処理
	/// </summary>
	void Debug();
	/// <summary>
	/// ダメージを受ける関数
	/// </summary>
	/// <param name="value">ダメージ量</param>
	void Damage(float value);
	/// <summary>
	/// 回復をする関数
	/// </summary>
	/// <param name="value">回復量</param>
	void Heal(float value);
	/// <summary>
	/// プレイヤーにバフを追加
	/// </summary>
	/// <param name="playerBuf"></param>
	/// <returns></returns>
	void AddBuff(PlayerBuff& playerBuff);
public: // ゲッター・セッター=======================
	virtual Character::Job GetPlayerJob() { return Character::Job::Warrior; };
	void SetCamera(Camera* camera) { m_camera = camera; }
	/// <summary>
	/// プレイヤーの角度を取得する関数
	/// </summary>
	/// <returns>プレイヤーの角度</returns>
	float GetRadian() { return GetTransform().rotation.y; }

	/// <summary>
	/// プレイヤーが死んでいるかどうか
	/// </summary>
	/// <returns>死んでいたらtrue</returns>
	bool IsDead();
	/// <summary>
	/// 選択したゲージの現在の量を取得する関数
	/// </summary>
	/// <param name="gauge">
	/// ゲージの種類
	/// Hp      -> HPゲージ
	/// Stamina -> スタミナゲージ
	/// Anger   -> 怒りゲージ
	/// Exp     -> 経験値ゲージ
	/// </param>
	/// <returns></returns>
	float GetGaugeCurrentValue(GaugeType gauge);
	/// <summary>
	/// 選択したゲージの最大値を取得する関数
	/// </summary>
	/// <param name="gauge">
	/// ゲージの種類
	/// Hp      -> HPゲージ
	/// Stamina -> スタミナゲージ
	/// Anger   -> 怒りゲージ
	/// Exp     -> 経験値ゲージ
	/// </param>
	/// <returns></returns>
	float GetGaugeMaxValue(GaugeType gauge);
	/// <summary>
	/// 選択したゲージの割合を取得する関数
	/// </summary>
	/// <param name="gauge">
	/// ゲージの種類
	/// Hp      -> HPゲージ
	/// Stamina -> スタミナゲージ
	/// Anger   -> 怒りゲージ
	/// Exp     -> 経験値ゲージ
	/// </param>
	/// <returns></returns>
	float GetGaugeRate(GaugeType gauge);
	Collision::Circle GetCircle() { return m_circle; }
	
	/// <summary>
	/// 自身のレベルを取得する関数
	/// </summary>
	/// <returns></returns>
	int GetLevel() { return m_status.Level; }
	void SetEnemyManager(EnemyManager* enemyManager);
	void SetItemManager(ItemManager* itemManager) { m_pItemMgr = itemManager; }
	void SetWeapon(Weapon* weapon);
	void ExpUp(float value);
	bool CheckAnger() { return m_anger; }
private:
	/// <summary>
	/// ダッシュ可能かどうかを調べる関数
	/// </summary>
	/// <returns>ダッシュ可能ならtrue</returns>
	bool CheckCanDash();
	/// <summary>
	/// ダッシュ中かどうかを調べる関数
	/// </summary>
	/// <returns>ダッシュ中ならtrue</returns>
	bool CheckDashNow();
	void CheckHit();
	void LevelUp();
	void BufUpdate();
	bool CheckAngerButton();
	void UpdateAngerButton();
	const PlayerStatus CheckBuffValue();
protected:

	/// <summary>
	/// プレイヤーのTransform
	/// </summary>
	//Transform m_transform;

	/// <summary>
	/// プレイヤーのグラフィックハンドル
	/// </summary>
	int m_graphHandle[static_cast<int>(MyMath::FourDirection::Max)][kPlayerFrame];

	// プレイヤーが向いている方向(左右)
	int m_directionX;
	// プレイヤーの移動量
	float m_moveAmount;
	// 移動速度
	//float m_speed;
	// 速さの割合
	float m_accel;
	// フレーム間の経過時間
	float m_deltaTime;

	// プレイヤーの移動量
	Vector3 m_moveVector;
	// 4方向で向いている向き
	MyMath::FourDirection m_direction;
	// アニメーションのフレーム
	float m_animFrame;

	/// <summary>
	/// ゲージの配列(HP・スタミナ・怒り)
	/// </summary>
	std::unique_ptr<Gauge> m_gauges[static_cast<int>(GaugeType::Max)];
	Weapon* m_weapons[kWeaponMaxNum];

	Camera* m_camera;
	Transform m_cameraTransform;

	/// <summary>
	/// 四角の当たり判定
	/// </summary>
	//Collision::AABB m_box;
	Collision::Circle m_circle;
	/// <summary>
	/// バフの配列
	/// </summary>
	//std::vector< std::unique_ptr<PlayerBuf>> m_buffs;
	std::vector<std::unique_ptr<PlayerBuff>> m_buffs;
	/// <summary>
	/// プレイヤーのパラメータ
	/// </summary>
	PlayerStatus m_status;
	/// <summary>
	/// 敵マネージャのポインタ
	/// </summary>
	EnemyManager* m_pEnemyMgr;
	/// <summary>
	/// アイテムマネージャーのポインタ
	/// </summary>
	ItemManager* m_pItemMgr;
	/// <summary>
	/// 怒りボタンを押したかどうかを取得するための変数
	/// </summary>
	bool m_angerButton[2];
	/// <summary>
	/// 怒り状態かどうか
	/// </summary>
	bool m_anger;
	/// <summary>
	/// カメラを揺らし続ける時間
	/// </summary>
	float m_cameraShakeCount;
	Character::Job m_playerType;
};