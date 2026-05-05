#pragma once
#include"../../../Utility/Transform.h"
class Gear
{
public:
	Gear();
	~Gear();
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();
	/// <summary>
	/// 終了処理
	/// </summary>
	void End();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
private:

	/// <summary>
	/// グラフィックハンドル
	/// </summary>
	int m_graphHandle;
	/// <summary>
	///  回転速度
	/// </summary>
	float m_rotateSpeed;
	/// <summary>
	/// トランスフォーム
	/// </summary>
	Transform m_transform;
	Transform m_transformss;
};

