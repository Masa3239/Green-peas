#pragma once

#include "../Object/GameObject.h"

/// <summary>
/// ゲームオブジェクトの見本
/// </summary>
class ExampleObject : public GameObject
{
public:

	// コンストラクタには必ずObjectManagerクラスのポインタを渡すようにする
	// 関数定義でGameObjectクラスのコンストラクタにも渡すようにする
	ExampleObject(ObjectManager* objManager);

	~ExampleObject();

	/// <summary>
	/// 自動で呼ばれないため、明示的に呼ぶ必要がある
	/// </summary>
	void Init() override;

	/// <summary>
	/// 自動で呼ばれないため、明示的に呼ぶ必要がある
	/// </summary>
	void End() override;

	/// <summary>
	/// 自動で呼ばれるため、呼ばなくて良い
	/// </summary>
	void Update() override;

	/// <summary>
	/// 自動で呼ばれるため、呼ばなくて良い
	/// </summary>
	void Draw() override;
};
