#pragma once
#include"Gauge.h"
class ExpGauge:public Gauge
{
public:
	ExpGauge();
	~ExpGauge();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init()override;
	/// <summary>
	/// 終了処理
	/// </summary>
	void End()override;
	void Update()override;
	/// <summary>
	/// 上昇
	/// </summary>
	/// <param name="value">上昇量</param>
	void Increase(float value)override;
	/// <summary>
	/// 減少
	/// </summary>
	/// <param name="value">減少量</param>
	void Decrease(float value)override;
	void Clamp()override;
	void Debug()override;
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
	/// 割合を取得する関数
	/// </summary>
	/// <returns>現在の値を最大の値で割った割合</returns>
	//virtual float GetRate();
	/// <summary>
	/// 最大かどうか
	/// </summary>
	/// <returns>最大以上ならtrue</returns>
	virtual bool CheckMax()override;
	/// <summary>
	/// レベルを上昇させる関数
	/// </summary>
	void LevelUp();
	/// <summary>
	/// 最大値・最小値を計算する
	/// </summary>
	void CheckLimit();
	void CheckCurrent();
private:
	/// <summary>
	/// 現在のレベル
	/// </summary>
	unsigned int m_level;
	/// <summary>
	/// 今までのトータルのレベル
	/// </summary>
	float m_totalExp;
	/// <summary>
	/// 現在のレベル時の最大経験値
	/// </summary>
	float m_maxExp;
	/// <summary>
	/// 現在のレベル時の最小経験値
	/// </summary>
	float m_minExp;

};

