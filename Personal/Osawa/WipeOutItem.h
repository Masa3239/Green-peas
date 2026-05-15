#pragma once

#include "../Syoguti/ItemBase.h"

class EnemyManager;

class WipeOutItem : public ItemBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	WipeOutItem(ObjectManager* objManager);

	/// <summary>
	/// 引数ありのコンストラクタ
	/// </summary>
	/// <param name="position"></param>
	WipeOutItem(ObjectManager* objManager, Vector3 position, EnemyManager* enemyMgr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~WipeOutItem() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 終了
	/// </summary>
	void End() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// アイテムの効果
	/// </summary>
	void ItemAbility(Player* player) override;

private:

	EnemyManager* m_pEnemyMgr;
};

