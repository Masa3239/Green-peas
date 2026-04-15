#pragma once
#include"../../Object/GameObject.h"
#include"../../Utility/Transform.h"
#include"../../Utility/Vector3.h"
class Weapon
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Weapon() :m_graphHandle(-1), m_swing(Transform()) {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Weapon() = default;
	//virtual void Init() = 0;
	//virtual void End()= 0;
	//virtual void Update()= 0;
	//virtual void Draw()= 0;
	//virtual void Attack();

protected:
	/// <summary>
	/// 武器のグラフィックハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// 武器を振った際のTransform
	/// </summary>
	Transform m_swing;
};

