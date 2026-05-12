#pragma once
#include<string>

class EnemyManager;

class BossHpBar
{

public:

	BossHpBar();
	~BossHpBar() = default;

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

	void SetEnemyManager(EnemyManager* pEnemyManager);

private:

	EnemyManager* m_pEnemyMgr;

	int m_currentHp;

	int m_maxHp;

	float m_rate;

	int m_hpFont;

	std::string m_maxHpFont;

};
