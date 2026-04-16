#pragma once
#include"../../Chara/Collision.h"
#include"../../Object/GameObject.h"
#include"../../Utility/Transform.h"

class BulletBase :public GameObject
{

public:

	BulletBase(ObjectManager* objManager);
	virtual ~BulletBase() = default;

	virtual void Init() override = 0;

	virtual void End() override = 0;

	virtual void Update() override = 0;

	virtual void Draw() override = 0;

	virtual void DebugDraw() = 0;

	virtual void Shot(Transform transform) = 0;

	virtual bool GetIsActive()const { return m_isActive; }

	virtual const Collision::Circle& GetCollision()const { return m_circle; }

	virtual void SetGraphHandle(int graphHandle) { m_graphHandle = graphHandle; }

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
