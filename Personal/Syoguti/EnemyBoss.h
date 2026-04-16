#pragma once
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include "../../Object/GameObject.h"

class EnemyBoss : public GameObject
{

public:

	enum class BossStatus {

	
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


private:

	/// <summary>
	/// 画像のハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// 座標
	/// </summary>
	Transform m_transform;

	/// <summary>
	/// 円の当たり判定
	/// </summary>
	Collision::Circle m_collsion;

	/// <summary>
	/// 封印状態かどうか
	/// </summary>
	bool m_sealFlag;

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
};

