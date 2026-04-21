#pragma once

#include "../Object/GameObject.h"
#include "../Chara/Collision.h"

class EnemyBullet : public GameObject
{
public:

	EnemyBullet(ObjectManager* objManager);
	~EnemyBullet() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void End() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 自身を有効にする
	/// </summary>
	void Create(const Vector3& position, const Vector3& rotation);

	/// <summary>
	/// 自身を無効にする
	/// </summary>
	void Remove();

private:

	/// <summary>
	/// 削除までのカウンタ
	/// </summary>
	float m_liveCounter;

	Collision::Circle m_collider;
};
