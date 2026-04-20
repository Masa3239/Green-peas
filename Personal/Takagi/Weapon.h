#pragma once
#include"../../Object/GameObject.h"
#include"../../Utility/Transform.h"
#include"../../Utility/Vector3.h"
#include"../../Chara/Collision.h"
#include"PlayerStatus.h"
class EnemyManager;
class PlayerStatus;

class Weapon:public GameObject
{
public:
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
	virtual void Attack()=0;
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
	void SetScale(float scale) { m_scale = scale; }
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
};

