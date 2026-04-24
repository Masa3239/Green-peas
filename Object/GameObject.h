#pragma once

#include "../Utility/Transform.h"

class ObjectManager;

/// <summary>
/// ゲームオブジェクトの基底クラス
/// </summary>
class GameObject
{
public:

	enum class State
	{
		Active,
		Deactive,
		Dead
	};

	/// <summary>
	/// コンストラクタ
	/// オブジェクトマネージャーで管理するためにマネージャーのポインタを必ず取得する
	/// </summary>
	/// <param name="manager">オブジェクトマネージャーのポインタ</param>
	GameObject(ObjectManager* manager);

	/// <summary>
	/// デストラクタ
	/// 派生クラスを破棄した時に備えて仮想デストラクタ化
	/// </summary>
	virtual ~GameObject();

	/// <summary>
	/// 初期化処理
	/// 必ず明示的に呼ぶ
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 後処理
	/// 必ず明示的に呼ぶ
	/// </summary>
	virtual void End() = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 更新の後処理
	/// </summary>
	virtual void PostUpdate() {};

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// オブジェクトマネージャーのゲッター
	/// </summary>
	/// <returns>オブジェクトマネージャーのポインタ</returns>
	ObjectManager* GetObjectManager() const { return m_pObjManager; }

	/// <summary>
	/// 状態を取得する
	/// </summary>
	/// <returns>状態</returns>
	State GetState() const { return m_state; }
	/// <summary>
	/// 状態を設定する
	/// </summary>
	/// <param name="state">状態</param>
	void SetState(const State state) { m_state = state; }

	/// <summary>
	/// トランスフォームを取得する
	/// </summary>
	Transform& GetTransform() { return m_transform; }

	int GetDrawOrder() const { return m_drawOrder; }
	void SetDrawOrder(const int order) { m_drawOrder = order; }

private:

	/// <summary>
	/// オブジェクトマネージャーのポインタ
	/// </summary>
	ObjectManager* m_pObjManager;

	/// <summary>
	/// 自身の状態
	/// </summary>
	State m_state;

	/// <summary>
	/// 座標
	/// </summary>
	Transform m_transform;

	/// <summary>
	/// 描画順
	/// </summary>
	int m_drawOrder;
};
