#pragma once

#include <unordered_map>
#include "../System/Input/Literal/KeyCodes.h"

struct Vector2;

/// <summary>
/// キーコードから入力状態を検知するクラス
/// </summary>
class InputFormatBase
{
public:

	InputFormatBase() = default;
	virtual ~InputFormatBase() = default;

	using LinkToKeyCode = std::unordered_map<KeyCode::Button, unsigned int>;

	/// <summary>
	/// ここで自作キーコードを登録する
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// ボタンの押下状態を取得する
	/// </summary>
	/// <param name="myKeyCode">自作キーコード</param>
	/// <returns>押されていたらtrue</returns>
	virtual bool CheckButtonState(const KeyCode::Button keyCode) = 0;

	/// <summary>
	/// 自作キーコードを登録する
	/// </summary>
	/// <param name="myKeyCode">自作キーコード</param>
	/// <param name="keyCode">元のキーコード</param>
	void RegisterKeyCode(const KeyCode::Button myKeyCode, const unsigned int keyCode);

	/// <summary>
	/// キーコードの紐づけを取得する
	/// </summary>
	/// <returns>自作キーコードを元のキーコードに紐づけるマップ</returns>
	const LinkToKeyCode& GetLinkToKeyCode() const { return mLinkToKeyCode; };

	virtual Vector2 GetValue(const KeyCode::Button keyCode) = 0;

private:

	/// <summary>
	/// 自作キーコードを元のキーコードに紐づけるマップ
	/// </summary>
	LinkToKeyCode mLinkToKeyCode;
};
