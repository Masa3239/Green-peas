#pragma once
#include"../Asai/BulletBase.h"

class Arrow :public BulletBase
{

public:

	Arrow(ObjectManager* objManager);
	~Arrow() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init()override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw()override;

	/// <summary>
	/// デバック描画
	/// </summary>
	void DebugDraw()override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void End()override;

	/// <summary>
	/// 弾の生成
	/// transformの位置に生成
	/// transform.rotation.zの角度に弾が進む
	/// この関数を呼ぶとm_isActiveがtrueになる
	/// </summary>
	/// <param name="transform">生成したい位置・角度</param>
	void Shot(Transform transform)override;

	/// <summary>
	/// 拡大率の設定
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(float scale)override;

	/// <summary>
	/// 画像のセット
	/// </summary>
	/// <param name="graphHandle"></param>
	void SetGraphHandle(int graphHandle) { m_graphHandle = graphHandle; }

private:

	/// <summary>
	/// 画像
	/// </summary>
	static int m_graphHandle;

};
