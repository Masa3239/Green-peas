#pragma once

#include "Buff.h"
#include <vector>

class BuffRandom
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BuffRandom();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BuffRandom();

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

	std::vector<Buff::BuffType> GetRandomBuffs(int count);

private:

	std::vector<Buff::BuffType> m_buffs;
	
};

