#pragma once

class EnemyManager;

class Combo
{

public:

	Combo();
	~Combo() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// デバックの描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	void SetEnemyManager(EnemyManager* pEnemyMgr) { m_pEnemyMgr = pEnemyMgr; }

private:

	/// <summary>
	/// コンボのフォント
	/// </summary>
	int m_fontHandle;

	/// <summary>
	/// コンボ数
	/// </summary>
	int m_combo;

	/// <summary>
	/// 1F前の倒した敵の数
	/// </summary>
	int m_prevDefeatedNum;

	/// <summary>
	/// コンボ受付タイマー
	/// </summary>
	float m_receptionTimer;

	/// <summary>
	/// 表示状態
	/// </summary>
	bool m_isVisible;

	EnemyManager* m_pEnemyMgr;

};
