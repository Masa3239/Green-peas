#pragma once

class Camera;

class Minimap
{

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// デバックの描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	void SetCamera(Camera* pCamera) { m_pCamera = pCamera; }

private:

	Camera* m_pCamera;

};
