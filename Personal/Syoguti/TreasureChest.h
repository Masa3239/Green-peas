#pragma once
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include "../../Object/GameObject.h"

namespace {

	constexpr int kTreasureChestMotionNum = 21;
}

class TreasureChest : public GameObject
{

public :

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="objectMgr"></param>
	TreasureChest(ObjectManager* objectMgr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TreasureChest();

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
	/// 宝箱が開いた
	/// </summary>
	void Open();

	/// <summary>
	/// 宝箱のアニメーション
	/// </summary>
	void OpenAnimation();

	/// <summary>
	/// 宝箱が開き終わった
	/// </summary>
	void Opened();

	/// <summary>
	/// グラフィックハンドルをセットするセッター関数
	/// </summary>
	/// <param name="graphHandle"></param>
	/// <param name="index"></param>
	void SetGraphHandle(int graphHandle, int index) { m_graphHandle[index] = graphHandle; }

	/// <summary>
	/// 当たり判定を取得するゲッター関数
	/// </summary>
	/// <returns></returns>
	const Collision::Circle& GetCollision() const { return m_collision; }

	/// <summary>
	/// 宝箱を消すフラグを取得するゲッター関数
	/// </summary>
	/// <returns></returns>
	const bool& GetRemoveFlag() const { return m_isRemove; }

	const bool& GetOpenedFlag() const { return m_isOpened; }

	/// <summary>
	/// スポーンできるかどうか
	/// </summary>
	/// <returns></returns>
	bool CanSpawn() const { return m_isOpened && !m_isSpawned; }

	/// <summary>
	/// すでにスポーンしているかを決めるセッター関数
	/// </summary>
	void SetSpawned() { m_isSpawned = true; }

private:

	/// <summary>
	/// 円の当たり判定
	/// </summary>
	Collision::Circle m_collision;

	/// <summary>
	/// グラフィックハンドル
	/// </summary>
	int m_graphHandle[kTreasureChestMotionNum];

	/// <summary>
	/// モーションカウンター
	/// </summary>
	int m_motionCounter;

	/// <summary>
	/// モーションフレーム
	/// </summary>
	int m_motionFrame;

	/// <summary>
	/// 宝箱が開いたかどうか
	/// </summary>
	bool m_isOpen;

	/// <summary>
	/// 宝箱が開き終わったかどうか
	/// </summary>
	bool m_isOpened;

	/// <summary>
	/// 宝箱が開き終わってからの時間
	/// </summary>
	float m_openedTimer;

	/// <summary>
	/// 削除するかどうか
	/// </summary>
	bool m_isRemove;

	/// <summary>
	/// アイテムがスポーンしたかどうか
	/// </summary>
	bool m_isSpawned;
};

