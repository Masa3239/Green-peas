#pragma once
class Gauge
{
public:
	/// <summary>
	/// ゲージ関連のクラス
	/// これを継承してHP・スタミナ・怒りゲージ等の処理を作る
	/// </summary>
	Gauge();
	~Gauge();

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
	/// <summary>
	/// 上昇
	/// </summary>
	void Increase();
	/// <summary>
	/// 減少
	/// </summary>
	void Decrease();

public:// ゲッター・セッター =======================
	/// <summary>
	/// 現在の値を取得
	/// </summary>
	/// <returns></returns>
	float GetCurrentValue() { return m_currentValue; }
	/// <summary>
	/// 最大値を設定
	/// </summary>
	/// <param name="Max"></param>
	void SetMaxValue(float Max) { m_maxValue = Max; }
	/// <summary>
	/// 最大値を取得する関数
	/// </summary>
	/// <returns></returns>
	float GetMaxValue() { return m_maxValue; }
	/// <summary>
	/// 最小値を設定
	/// </summary>
	/// <param name="Min"></param>
	void SetMinValue(float Min) { m_minValue = Min; }
	/// <summary>
	/// 最小値を取得する関数
	/// </summary>
	/// <returns></returns>
	float GetMinValue() { return m_minValue; }

	/// <summary>
	/// 割合を取得する関数
	/// </summary>
	/// <returns>現在の値を最大の値で割った割合</returns>
	float GetRate() { return m_currentValue / m_maxValue; }

private:
	/// <summary>
	/// 最大値
	/// </summary>
	float m_maxValue;
	/// <summary>
	/// 現在の値
	/// </summary>
	float m_currentValue;
	/// <summary>
	/// 最小値
	/// </summary>
	float m_minValue;

};

