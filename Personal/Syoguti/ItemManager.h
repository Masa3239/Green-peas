#pragma once

#include<vector>
#include<memory>
#include "ItemBase.h"
#include "../../System/ObjectManager.h"

class Player;

class ItemManager
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ItemManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ItemManager() = default;

	/// <summary>
	///  初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 終了
	/// </summary>
	void End();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// アイテムの生成
	/// </summary>
	/// <param name="type">アイテムの種類</param>
	/// <param name="position">座標</param>
	void Create(ItemBase::ItemType type, Vector3 position);

	/// <summary>
	/// 指定したインデックスのアイテムを削除
	/// </summary>
	/// <param name="index"></param>
	void Remove(int index);

	/// <summary>
	/// 引数の形状とアイテムが当たっているか調べる
	/// </summary>
	/// <param name="other"></param>
	void CheckHitCollision(const Collision::Shape& other);

	/// <summary>
	/// オブジェクトマネージャーのポインタをセットするセッター関数
	/// </summary>
	/// <param name="objectManager"></param>
	void SetObjectManager(ObjectManager* objectManager) { m_pObjectMgr = objectManager; }

	/// <summary>
	/// プレイヤーのポインタをセットするセッター関数
	/// </summary>
	/// <param name="player"></param>
	void SetPlayer(Player* player) { m_pPlayer = player; }

private:

	/// <summary>
	/// 可変長配列
	/// </summary>
	std::vector<std::unique_ptr<ItemBase>> m_items;

	/// <summary>
	/// Hp回復アイテムの画像のグラフハンドル
	/// </summary>
	int m_hpHealItemGraphHandle;

	/// <summary>
	/// 攻撃力アップアイテムの画像のグラフハンドル
	/// </summary>
	int m_attackUpItemGraphHandle;

	/// <summary>
	/// オブジェクトマネージャーのポインタ
	/// </summary>
	ObjectManager* m_pObjectMgr;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	Player* m_pPlayer;
};

