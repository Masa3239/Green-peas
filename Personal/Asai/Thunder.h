#pragma once
#include"../Asai/BulletBase.h"
#include<vector>

class EnemyManager;
class EnemyBase;

class Thunder :public BulletBase
{

public:

	Thunder(ObjectManager* objManager);
	~Thunder() = default;

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
	/// State::Ballの状態で呼び出せば状態が変わる
	/// </summary>
	void ChangeStateInfection();

	void SetEnemyManager(EnemyManager* pEnemyMgr) { m_pEnemyMgr = pEnemyMgr; }

	void SetIndex(int index) { m_index = index; }

private:

	/// <summary>
	/// StateがBallの時の更新処理
	/// </summary>
	void UpdateBall();

	/// <summary>
	/// 伝染状態のアップデート
	/// </summary>
	void UpdateInfection();

private:

	int m_index;

	enum class State {

		Ball = 0,
		Infection,
	};

	/// <summary>
	/// 雷の状態
	/// </summary>
	State m_state;

	/// <summary>
	/// 経過時間
	/// </summary>
	float m_fieldElapsedTime;

	/// <summary>
	/// 伝染のカウント
	/// </summary>
	int m_infectionCount;

	float m_infectionTimer;

	/// <summary>
	/// 敵の座標を取得する為に使う
	/// </summary>
	EnemyManager* m_pEnemyMgr;

	/// <summary>
	/// 雷が当たった敵を調べる
	/// </summary>
	std::vector<EnemyBase*>m_pEnemies;

	/// <summary>
	/// 
	/// </summary>
	std::vector<int>m_graphHandle;

	float m_graphFrame;

	float m_graphCounter;

};
