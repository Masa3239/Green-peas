#pragma once
#include"../../Chara/Collision.h"
#include"../../Object/GameObject.h"
#include"../../Utility/Transform.h"

class BulletBase :public GameObject
{

public:

	BulletBase(ObjectManager* objManager);
	virtual ~BulletBase() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() override = 0;

	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void End() override = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() override = 0;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() override = 0;

	/// <summary>
	/// デバック描画
	/// </summary>
	virtual void DebugDraw() = 0;

	/// <summary>
	/// 弾の生成
	/// transformの位置に生成
	/// transform.rotation.zの角度に弾が進む
	/// この関数を呼ぶとm_isActiveがtrueになる
	/// </summary>
	/// <param name="transform">生成したい位置・角度</param>
	virtual void Shot(Transform transform) = 0;

	/// <summary>
	/// アクティブ状態を取得
	/// </summary>
	/// <returns>アクティブならtrue・アクティブじゃないならfalse</returns>
	virtual bool GetIsActive()const { return m_isActive; }

	/// <summary>
	/// 当たり判定の取得
	/// </summary>
	/// <returns></returns>
	virtual const Collision::Circle& GetCollision()const { return m_circle; }

	/// <summary>
	/// 画像のセット
	/// </summary>
	/// <param name="graphHandle"></param>
	virtual void SetGraphHandle(int graphHandle) { m_graphHandle = graphHandle; }

	/// <summary>
	/// 拡大率の変更
	/// </summary>
	/// <param name="scale"></param>
	virtual void SetScale(float scale) = 0;

protected:

	/// <summary>
	/// 画像のハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// トランスフォーム
	/// </summary>
	Transform m_transform;

	/// <summary>
	/// 拡大率
	/// </summary>
	float m_scale;

	/// <summary>
	/// 生成された座標
	/// </summary>
	Vector3 m_spawnPos;

	/// <summary>
	/// アクティブ状態
	/// </summary>
	bool m_isActive;

	/// <summary>
	/// サークルの当たり判定
	/// </summary>
	Collision::Circle m_circle;
	
};
