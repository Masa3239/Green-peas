#pragma once
#include<string>

class EnemyManager;

/// <summary>
/// ボスのHPを表示するクラス
/// </summary>
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

	/// <summary>
	/// ボスの体力を取得するために用意
	/// </summary>
	EnemyManager* m_pEnemyMgr;

	/// <summary>
	/// 現在のHP
	/// </summary>
	int m_currentHp;

	/// <summary>
	///	最大のHP
	/// </summary>
	int m_maxHp;

	/// <summary>
	/// 最大HPと現在HPの割合
	/// </summary>
	float m_rate;

	/// <summary>
	/// HPのフォント
	/// </summary>
	int m_hpFont;

	/// <summary>
	/// 最大HPの文字を保存する
	/// </summary>
	std::string m_maxHpFont;

};
