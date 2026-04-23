#pragma once

#include<vector>
#include<memory>
#include "BossBulletBase.h"
#include "../../System/ObjectManager.h"

class Player;

class BossBulletManager
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BossBulletManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossBulletManager() = default;

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
	/// 弾の生成
	/// </summary>
	/// <param name="type"></param>
	/// <param name="position"></param>
	void Create(BossBulletBase::BulletType type, Vector3 position);

	/// <summary>
	/// 指定したインデックスの弾を削除
	/// </summary>
	/// <param name="index"></param>
	void Remove(int index);

	/// <summary>
	/// 引数の形状と弾が当たっているか調べる
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool CheckHitCollision(const Collision::Shape& other);

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
	std::vector<std::unique_ptr<BossBulletBase>> m_bullets;

	/// <summary>
	/// 弾の画像のグラフハンドル
	/// </summary>
	int m_bulletGraphHandle;

	/// <summary>
	/// オブジェクトマネージャーのポインタ
	/// </summary>
	ObjectManager* m_pObjectMgr;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	Player* m_pPlayer;

};

