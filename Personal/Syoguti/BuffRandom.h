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
	/// <param name="buffs"></param>
	void Draw(const std::vector<Buff::BuffType>& buffs);

	/// <summary>
	/// バフをランダムに決める
	/// </summary>
	/// <param name="count"></param>
	/// <returns></returns>
	std::vector<Buff::BuffType> GetRandomBuffs(int count);

	/// <summary>
	/// バフのテキストを取得する
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	const char* GetBuffText(Buff::BuffType type);

private:

	/// <summary>
	/// BuffTypeの可変長配列
	/// </summary>
	std::vector<Buff::BuffType> m_buffs;
	
	// int m_level[static_cast<int>(Buff::BuffType::Max)];

};

