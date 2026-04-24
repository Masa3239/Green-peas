#pragma once
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include "../../Object/GameObject.h"

namespace {

	constexpr int kTreasureChestMotionNum = 32;
}

class TreasureChest : public GameObject
{

public :

	TreasureChest(ObjectManager* objectMgr);

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

	void SetGraphHandle(int graphHandle, int index) { m_graphHandle[index] = graphHandle; }

	void SetFrame(int frame) { m_frame = frame; }

private:

	/// <summary>
	/// 円の当たり判定
	/// </summary>
	Collision::Circle m_collision;

	int m_graphHandle[32];

	int m_frame;
};

