#pragma once
#include"../../Object/GameObject.h"
#include"../../Utility/Transform.h"
#include"../../Utility/Vector3.h"
#include"../../Chara/Collision.h"
#include"PlayerStatus.h"
class EnemyManager;
class PlayerStatus;
namespace {
	// 斬撃エフェクト画像のフレーム数
	constexpr int kEffectFrame = 16;
	// 取得する際の半径
	constexpr float kCatchRadius = 20;
	// チャージ判定にする時間
	constexpr float kChargeTime = 0.5f;
	constexpr int kBulletNum = 100;
}
class Weapon:public GameObject
{
public:
	/// <summary>
	/// 武器の種類
	/// </summary>
	enum {
		Sword,		// 剣
		Katana,		// 刀
		Boomerang,	// ブーメラン
		Bow,		// 弓
		Volt,	// 雷
		Flame,		// 炎
		Max
	};
	enum class Swing {
		Normal,
		Up,
		Down,
		Max
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Weapon(ObjectManager* objManager);
		
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Weapon() = default;
	//virtual void Init() = 0;
	//virtual void End()= 0;
	//virtual void Update()= 0;
	//virtual void Draw()= 0;

	/// <summary>
	/// 攻撃処理
	/// </summary>
	/// <returns>攻撃したか</returns>
	virtual bool Attack()=0;
	/// <summary>
	/// 当たり判定の取得
	/// </summary>
	/// <returns></returns>
	//virtual Collision::Circle GetCollision()=0;
	/// <summary>
	/// 攻撃中かどうかチェック
	/// </summary>
	/// <returns></returns>
	virtual bool CheckAttack() = 0;

	virtual void CheckCollision() = 0;
	/// <summary>
	/// 敵マネージャーの設定をする関数
	/// </summary>
	/// <param name="enemyMgr"></param>
	void SetEnemyManager(EnemyManager* enemyMgr) {
		m_pEnemyMgr = enemyMgr; 
	}
	void SetPlayerStatus(const PlayerStatus& status) { m_playerStatus = status; }
	void SetActive(bool active) { m_active = active; }
	virtual void SetScale(float scale) { m_scale = scale; }
	void UpdateCatchCol() { m_catchCol.SetPosition(GetTransform().position);m_catchCol.SetRadius(kCatchRadius); }
	Collision::Circle GetCatchCol() { return m_catchCol; }
	void SetPos(const Vector3 position);
	virtual int GetWeaponType()=0;
	void SetChatch(bool catchFlag) { m_catch = catchFlag; }
	bool GetChatch() { return m_catch; }
	bool GetChargeFlag() { return m_chargeFlag; }
	bool CheckCameraUpdate() { return m_camUpdate; }
protected:
	/// <summary>
	/// 武器のグラフィックハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// 武器を振った際のTransform
	/// </summary>
	Transform m_swing;
	/// <summary>
	/// 武器を振る際の状態
	/// </summary>
	Swing m_swingState;
	float m_attackRadian;
	/// <summary>
	/// 敵マネージャーのポインタ
	/// </summary>
	EnemyManager* m_pEnemyMgr;

	PlayerStatus m_playerStatus;
	PlayerStatus m_weaponStatus;
	bool m_active;
	float m_scale;
	/// <summary>
	/// 取得する際の当たり判定
	/// </summary>
	Collision::Circle m_catchCol;
	bool m_catch;
	bool m_chargeFlag;
	bool m_camUpdate;
};

