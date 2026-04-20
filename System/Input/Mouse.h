#pragma once

/// <summary>
/// マウスの入力管理
/// </summary>
class Mouse
{
public:

	/// <summary>
	/// インスタンスの生成、取得を行う
	/// </summary>
	static Mouse& GetInstance();

	~Mouse() = default;
	
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// キーが押されているかどうかを取得する
	/// </summary>
	/// <param name="keyCode">キーコード</param>
	/// <returns>押下状態</returns>
	bool IsDown(int keyCode);

private:

	Mouse() = default;
	// コピーコンストラクタ禁止
	Mouse(const Mouse&) = delete;
	// コピー代入禁止
	Mouse& operator=(const Mouse&) = delete;
	// ムーブ禁止
	Mouse(Mouse&&) = delete;
	// ムーブ代入禁止
	Mouse& operator=(Mouse&&) = delete;

	/// <summary>
	/// マウスボタンの押下状態
	/// </summary>
	int mState;
};
