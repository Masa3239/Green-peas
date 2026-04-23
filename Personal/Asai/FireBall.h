#pragma once
#include"../Asai/BulletBase.h"

class FireBall :public BulletBase
{

public:

	FireBall(ObjectManager* objManager);
	~FireBall() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init()override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw()override;

	/// <summary>
	/// デバック描画
	/// </summary>
	void DebugDraw()override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void End()override;

	/// <summary>
	/// 弾の生成
	/// transformの位置に生成
	/// transform.rotation.zの角度に弾が進む
	/// この関数を呼ぶとm_isActiveがtrueになる
	/// </summary>
	/// <param name="transform">生成したい位置・角度</param>
	void Shot(Transform transform)override;

	/// <summary>
	/// 拡大率の設定
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(float scale)override;

	/// <summary>
	/// 状態を変更する関数
	/// State::Ballの状態で敵に当たった時に呼び出せば状態が変わる
	/// </summary>
	void ChangeStateField();

	/// <summary>
	/// フィールド状態でのダメージを当てれるか取得する
	/// </summary>
	/// <returns>ダメージ当てれるならtrue・当てれないならfalse</returns>
	bool CanFieldDamage();

	/// <summary>
	/// フィールド状態でのダメージ間隔タイマーをリセット
	/// </summary>
	void ResetDamageInterval() { m_fieldDamageIntervalTimer = 0; }

private:

	/// <summary>
	/// StateがBallの時の更新処理
	/// </summary>
	void UpdateBall();

	/// <summary>
	/// StateがFieldの時の更新処理
	/// </summary>
	void UpdateField();

private:

	/// <summary>
	/// 状態
	/// </summary>
	enum class State {

		Ball=0,
		Field,

	};

	/// <summary>
	/// 現在の状態
	/// </summary>
	State m_state;

	/// <summary>
	/// フィールド状態の経過時間
	/// </summary>
	float m_fieldElapsedTime;

	/// <summary>
	/// フィールド状態でのダメージ間隔のタイマー
	/// </summary>
	float m_fieldDamageIntervalTimer;

};
