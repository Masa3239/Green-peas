#pragma once
#include"../../Object/GameObject.h"
#include"../../Utility/Transform.h"
#include"../../Utility/Vector3.h"
#include"../../Chara/Collision.h"
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
	Weapon(ObjectManager* objManager) :GameObject(objManager), m_graphHandle(-1), m_swing(Transform()) {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Weapon() = default;
	//virtual void Init() = 0;
	//virtual void End()= 0;
	//virtual void Update()= 0;
	//virtual void Draw()= 0;
	virtual void Attack()=0;
	virtual Collision::Circle GetCollision()=0;

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
};

