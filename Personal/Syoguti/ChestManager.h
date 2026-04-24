#pragma once

#include<vector>
#include<memory>
#include "TreasureChest.h"
#include "../../System/ObjectManager.h"

class TreasureChest;


class ChestManager
{

public:

	ChestManager();

	~ChestManager();

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
	/// 生成
	/// </summary>
	/// <param name="position"></param>
	void Create(Vector3 position);

	/// <summary>
	/// 削除
	/// </summary>
	/// <param name="index"></param>
	void Remove(int index);

	/// <summary>
	/// 当たり判定のチェック
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool CheckHitCollision(const Collision::Shape& other);

	/// <summary>
	/// オブジェクトマネージャーのポインタをセットするセッター関数
	/// </summary>
	/// <param name="objectManager"></param>
	void SetObjectManager(ObjectManager* objectManager) { m_pObjectMgr = objectManager; }

private:

	/// <summary>
	/// 可変長配列
	/// </summary>
	std::vector<std::unique_ptr<TreasureChest>> m_chests;

	/// <summary>
	/// グラフィックハンドル
	/// </summary>
	int m_graphHandle[kTreasureChestMotionNum];

	/// <summary>
	/// オブジェクトマネージャーのポインタ
	/// </summary>
	ObjectManager* m_pObjectMgr;

};

