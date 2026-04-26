#pragma once
#include"ResultHead.h"
class Clear:public ResultHead
{
public:
	enum {
		Across,
		Fall
	};
	Clear();
	~Clear();
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;
	/// <summary>
	/// 終了処理
	/// </summary>
	void End() override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
private:
	Vector3 m_speed;
	int m_phase;
};

