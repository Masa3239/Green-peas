#pragma once

/// <summary>
/// 入力情報の取得・更新をする
/// </summary>
namespace Input {

	/// <summary>
	/// 入力情報の取得・更新
	/// ゲームループで呼ぶ
	/// </summary>
	void Update();

	/// <summary>
	/// キーが押されているかどうか調べる
	/// </summary>
	/// <param name="key">入力されたキー</param>
	/// <returns>入力結果 押されていたらtrue</returns>
	bool IsDown(int key);

	/// <summary>
	/// キーが押された瞬間かどうか調べる
	/// </summary>
	/// <param name="key">入力されたキー</param>
	/// <returns>入力結果 押された瞬間だったらtrue</returns>
	bool IsPressed(int key);

	/// <summary>
	/// キーが離された瞬間かどうか調べる
	/// </summary>
	/// <param name="key">入力されたキー</param>
	/// <returns>入力結果 離された瞬間だったらtrue</returns>
	bool IsReleased(int key);

}

