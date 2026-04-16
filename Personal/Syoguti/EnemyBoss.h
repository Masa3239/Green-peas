#pragma once
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"

class EnemyBoss
{

public:

	enum class BossStatus {

	
	};

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyBoss();

	/// <summary>
	/// 引数ありのコンストラクタ
	/// </summary>
	EnemyBoss(Vector3 position);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyBoss() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 終了
	/// </summary>
	void End();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

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
	/// ボスの体力
	/// </summary>
	int m_bossHp;

	/// <summary>
	/// ボスの攻撃力
	/// </summary>
	int m_attackPower;
};

