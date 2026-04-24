#pragma once
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include"../../Object/GameObject.h"
#include <memory>

class Player;

namespace {

	constexpr int kAnimationNum = 32;
}

class BossBulletBase : public GameObject
{

public:

	enum class BulletType {

		Normal,
		Max
	};

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="objManager"></param>
	BossBulletBase(ObjectManager* objManager);

	virtual ~BossBulletBase() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 終了
	/// </summary>
	virtual void End() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// グラフハンドルをセットするセッター関数
	/// </summary>
	/// <param name="graphHandlePath"></param>
	virtual void SetGraphHandle(int graphHandle,int index) { m_graphHandle[index] = graphHandle; }

	/// <summary>
	/// プレイヤーのポインタをセットするセッター関数
	/// </summary>
	/// <param name="player"></param>
	virtual void SetPlayer(Player* player) { m_pPlayer = player; }

	/// <summary>
	/// 当たり判定の情報を取得するゲッター関数
	/// </summary>
	/// <returns></returns>
	virtual const Collision::Circle GetCollision() { return m_collision; }

protected:

	/// <summary>
	/// 画像ハンドル
	/// </summary>
	int m_graphHandle[kAnimationNum];

	/// <summary>
	/// 角度
	/// </summary>
	Vector3 m_velocity;

	/// <summary>
	/// 円の当たり判定
	/// </summary>
	Collision::Circle m_collision;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	Player* m_pPlayer;

};

