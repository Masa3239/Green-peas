#pragma once
#include "BossBulletBase.h"
#include "../../Utility/Transform.h"

class BossBullet : public BossBulletBase
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="objManager"></param>
	BossBullet(ObjectManager* objManager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossBullet();

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


private:

	/// <summary>
	///  アニメーション
	/// </summary>
	int m_animIndex;

	/// <summary>
	/// アニメーションのタイマー
	/// </summary>
	int m_animTimer;

};

