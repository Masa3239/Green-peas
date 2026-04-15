#pragma once

#include "../Object/GameObject.h"
#include "../Utility/Transform.h"

class Player;

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

	Player* GetPlayer() const { return m_player; }
	void SetPlayer(Player* player) { m_player = player; }

private:

	/// <summary>
	/// 自身のHP
	/// </summary>
	int m_hp;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	Player* m_player;
};
