#pragma once

#include <DxLib.h>

class Time
{
public:

	/// <summary>
	/// シングルトンのインスタンスを取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static Time& GetInstance();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Time() = default;

	/// <summary>
	/// デルタタイムを計算する
	/// </summary>
	/// <param name="time">前フレームの時間</param>
	void CalculateDeltaTime(LONGLONG time);

	/// <summary>
	/// デルタタイムを取得
	/// タイムスケールあり
	/// </summary>
	/// <returns>デルタタイム</returns>
	float GetDeltaTime() const { return m_deltaTime * m_timeScale; }

	/// <summary>
	/// デルタタイムを取得
	/// タイムスケールなし
	/// </summary>
	/// <returns></returns>
	float GetUnscaledDeltaTime() const { return m_deltaTime; }

	/// <summary>
	/// タイムスケールのゲッター
	/// </summary>
	/// <returns>タイムスケール</returns>
	float GetTimeScale() const { return m_timeScale; }
	/// <summary>
	/// タイムスケールのセッター
	/// </summary>
	/// <param name="timeScale">タイムスケール</param>
	void SetTimeScale(const float timeScale) { m_timeScale = timeScale; }

private:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Time();

	// コピー禁止
	Time(const Time&) = delete;
	// コピー代入禁止
	Time& operator=(const Time&) = delete;
	// ムーブ禁止		
	Time(Time&&) = delete;
	// ムーブ代入禁止
	Time& operator=(Time&&) = delete;

	/// <summary>
	/// デルタタイム
	/// </summary>
	float m_deltaTime;

	/// <summary>
	/// タイムスケール
	/// 時間の倍速度
	/// </summary>
	float m_timeScale;
};
