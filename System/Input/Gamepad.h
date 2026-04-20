#pragma once

#include <DxLib.h>
#include <array>

/// <summary>
/// ゲームパッドの入力管理
/// </summary>
class Gamepad
{
public:

	/// <summary>
	/// インスタンスの生成、取得を行う
	/// </summary>
	static Gamepad& GetInstance();

	// 接続できるゲームパッドの最大数
	static constexpr int kMaxSlotNum = 4;

	~Gamepad() = default;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// キーが押されているかどうかを取得する
	/// </summary>
	/// <param name="keyCode">キーコード</param>
	/// <param name="slot">ゲームパッドの識別番号</param>
	/// <returns>押下状態</returns>
	bool IsDown(int keyCode, int slot = 1);

	/// <summary>
	/// 入力状態を取得
	/// </summary>
	/// <param name="slot">ゲームパッドの識別番号</param>
	const XINPUT_STATE& GetState(int slot = 1) const { return mState[slot - 1]; }

private:

	Gamepad();
	// コピーコンストラクタ禁止
	Gamepad(const Gamepad&) = delete;
	// コピー代入禁止
	Gamepad& operator=(const Gamepad&) = delete;
	// ムーブ禁止
	Gamepad(Gamepad&&) = delete;
	// ムーブ代入禁止
	Gamepad& operator=(Gamepad&&) = delete;

	/// <summary>
	/// キーボードの押下状態
	/// </summary>
	std::array<XINPUT_STATE, 4> mState;

	/// <summary>
	/// 接続しているゲームパッドの数
	/// </summary>
	int mConnectedNum;
};

