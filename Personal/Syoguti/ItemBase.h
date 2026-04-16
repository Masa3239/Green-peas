#pragma once
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include"../../Object/GameObject.h"
#include <memory>

class Player;

/// <summary>
/// アイテムの基本クラス
/// </summary>
class ItemBase : public GameObject
{

public:

	/// <summary>
	/// アイテムの種類
	/// </summary>
	enum class ItemType {

		Heal,
		Attack,
		Max
	};

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ItemBase(ObjectManager* objManager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ItemBase() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 終了
	/// </summary>
	virtual void End() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// アイテムの効果
	/// </summary>
	virtual void ItemAbility(Player* player) = 0;

	/// <summary>
	/// グラフハンドルをセットするセッター関数
	/// </summary>
	/// <param name="graphHandlePath"></param>
	virtual void SetGraphHandle(int graphHandle) { m_graphHandle = graphHandle; }

	/// <summary>
	/// 当たり判定の情報を取得するゲッター関数
	/// </summary>
	/// <returns></returns>
	virtual const Collision::Circle GetCollision() { return m_collision; }


protected:

	/// <summary>
	/// 画像の座標
	/// </summary>
	Transform m_transform;
	
	/// <summary>
	/// 画像ハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// 円の当たり判定
	/// </summary>
	Collision::Circle m_collision;

};

