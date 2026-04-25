#pragma once
#include"PlayerStatus.h"
typedef struct PlayerBuff {
public:
	PlayerBuff();
	PlayerBuff(PlayerStatus bufValue,float second,bool eternal);
	~PlayerBuff() = default;
	/// <summary>
	/// バフの更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// バフの効果が終わったかどうかを取得
	/// </summary>
	bool IsFinish();
	/// <returns></returns>
	/// <summary>
	/// バフの値を取得する関数
	/// </summary>
	/// <returns></returns>
	const PlayerStatus GetBuffValue() { return m_buffValue; }
	const float Second() { return m_second; }
	const float IsEternal() { return m_second; }
private:
	// ステータスを上昇させる量
	PlayerStatus m_buffValue;
	// 効果時間(秒)
	float m_second;
	// 効果が永続かどうか
	bool m_isEternal;
};