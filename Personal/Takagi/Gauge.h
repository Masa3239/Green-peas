#pragma once

namespace {
	/// <summary>
	/// リセットの種類
	/// </summary>
	/*enum class GaugeValue {
		Max,
		Current,
		Min,
	};*/
	/// <summary>
	/// 値の初期値
	/// </summary>
	constexpr float kInitialValue = 100.0f;
}

class Gauge
{
public:
	enum class Value{
		Max,
		Current,
		Min,
	};
	/// <summary>
	/// ゲージ関連のクラス
	/// これを継承してHP・スタミナ・怒りゲージ等の処理を作る
	/// </summary>
	Gauge();
	~Gauge();

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init();
	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void End();
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();
	/// <summary>
	/// 上昇
	/// </summary>
	/// <param name="value">上昇量</param>
	virtual void Increase(float value);
	/// <summary>
	/// 減少
	/// </summary>
	/// <param name="value">減少量</param>
	virtual void Decrease(float value);
	virtual void Clamp();
	/// <summary>
	/// ゲージをリセットする関数
	/// </summary>
	/// <param name="set">
	/// リセットの種類
	/// Max -> 最大値でリセット
	/// Min -> 最小値でリセット
	/// </param>
	virtual void Reset(Value set = Value::Max);
	/// <summary>
	/// 指定した値以上かどうかを調べる
	/// </summary>
	/// <param name="value">値の量</param>
	/// <param name="check">
	/// 調べる値の種類
	/// Max     -> 最大値を調べる
	/// Current -> 現在の値を調べる
	/// Min     -> 最小値を調べる
	/// </param>
	/// <returns></returns>
	bool CheckValue(float value, Value check = Value::Current);

	virtual void Debug();
public:// ゲッター・セッター =======================
	/// <summary>
	/// 最大・最小・現在の値を設定する関数
	/// </summary>
	/// <param name="velue">設定する値</param>
	/// <param name="get">
	/// 設定する値の種類
	/// Max     -> 最大値を設定
	/// Current -> 現在の値を設定
	/// Min     -> 最小値を設定
	/// </param>
	void SetValue(float value,Value set = Value::Current);
	/// <summary>
	/// 最大・最小・現在の値を取得する関数
	/// </summary>
	/// <param name="get">
	/// 取得する値の種類
	/// Max     -> 最大値を取得
	/// Current -> 現在の値を取得
	/// Min     -> 最小値を取得
	/// </param>
	/// <returns></returns>
	float GetValue(Value get = Value::Current);

	/// <summary>
	/// 割合を取得する関数
	/// </summary>
	/// <returns>現在の値を最大の値で割った割合</returns>
	virtual float GetRate() { return (m_currentValue / m_maxValue); }
	/// <summary>
	/// 最大かどうか
	/// </summary>
	/// <returns>最大以上ならtrue</returns>
	virtual bool CheckMax() { return (m_currentValue >= m_maxValue); }
	/// <summary>
	/// 最小かどうか
	/// </summary>
	/// <returns>最小以下ならtrue</returns>
	virtual bool CheckMin() { return (m_currentValue <= m_minValue); }
protected:
	/// <summary>
	/// 最大値
	/// </summary>
	float m_maxValue;
	/// <summary>
	/// 最小値
	/// </summary>
	float m_minValue;
	/// <summary>
	/// 現在の値
	/// </summary>
	float m_currentValue;

};

