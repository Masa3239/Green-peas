#pragma once

#include <vector>

class GameObject;

/// <summary>
/// ゲームオブジェクトを管理するクラス
/// </summary>
class ObjectManager
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ObjectManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ObjectManager() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 後処理
	/// </summary>
	void End();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// ゲームオブジェクトを追加する
	/// </summary>
	/// <param name="gameObject">ゲームオブジェクトのポインタ</param>
	void AddGameObject(GameObject* gameObject);

	/// <summary>
	/// ゲームオブジェクトを削除する
	/// </summary>
	/// <param name="gameObject">ゲームオブジェクトのポインタ</param>
	void RemoveGameObject(GameObject* gameObject);

	void ActiveAllGameObject();

	void DeactiveAllGameObject();

private:

	/// <summary>
	/// ゲームオブジェクトを更新する
	/// </summary>
	void UpdateGameObjects();

	/// <summary>
	/// 状態がEDeadのゲームオブジェクトを削除する
	/// </summary>
	void RemoveDeadGameObjects();

	/// <summary>
	/// ゲームオブジェクトの衝突を判定する
	/// </summary>
	void CheckCollision();

	/// <summary>
	/// ゲームオブジェクトの配列
	/// </summary>
	std::vector<GameObject*> m_gameObjects;

	/// <summary>
	/// 待機中のゲームオブジェクトの配列
	/// 配列のforループ中に配列のサイズが変わることで、
	/// アドレスが変わり初期化されていない値を指してしまうため使用する
	/// </summary>
	std::vector<GameObject*> m_pendingGameObjects;

	/// <summary>
	/// ゲームオブジェクトを更新中かどうか
	/// </summary>
	bool m_isUpdatingGameObject;
};
