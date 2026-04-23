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

	int m_fontHandle;

	int m_combo;

	int m_prevDefeatedNum;

	float m_receptionTimer;

	bool m_isVisible;

	EnemyManager* m_pEnemyMgr;

};
