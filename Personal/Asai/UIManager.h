#pragma once

class UIManager
{

public:

	UIManager();
	~UIManager();

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
	/// デバック描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// スクリーン座標に描画
	/// </summary>
	void ScreenDraw();

	/// <summary>
	/// ワールド座標に描画
	/// </summary>
	void WorldDraw();

	/// <summary>
	/// デバック描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

private:



};
