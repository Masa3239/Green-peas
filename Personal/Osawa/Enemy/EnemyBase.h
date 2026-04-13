#pragma once

#include "../Utility/Transform.h"

class EnemyBase
{
public:

	EnemyBase();
	virtual ~EnemyBase();

	enum class State
	{
		Alive,
		Dead
	};

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 後処理
	/// </summary>
	virtual void End() = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 敵固有の更新処理
	/// </summary>
	virtual void UpdateEnemy() = 0;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// トランスフォームを取得
	/// </summary>
	Transform& GetTransform() { return m_transform; }

	/// <summary>
	/// 状態を取得
	/// </summary>
	State GetState() const { return m_state; }

	/// <summary>
	/// HPを取得
	/// </summary>
	int GetHP() const { return m_hp; }

	/// <summary>
	/// HPを設定
	/// </summary>
	void SetHP(const int hp) { m_hp = hp; }

private:

	/// <summary>
	/// トランスフォーム
	/// </summary>
	Transform m_transform;

	/// <summary>
	/// 状態
	/// </summary>
	State m_state;

	/// <summary>
	/// 自身のHP
	/// </summary>
	int m_hp;
};
