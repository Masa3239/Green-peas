#pragma once

#include "../Object/GameObject.h"
#include "../Utility/Transform.h"

class EnemyBase : public GameObject
{
public:

	EnemyBase(ObjectManager* objManager);
	virtual ~EnemyBase();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 敵固有の更新処理
	/// </summary>
	virtual void UpdateEnemy() = 0;

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
	/// 自身のHP
	/// </summary>
	int m_hp;
};
