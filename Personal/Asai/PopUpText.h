#pragma once
#include"../../Utility/Transform.h"

namespace PopUpUI {

	enum class TextType {

		Damage = 0,
		Critical,
		Heal,
		Max,

	};

}

class PopUpText
{

public:

	PopUpText();
	~PopUpText();

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

	/// <summary>
	/// isDeadを取得する変数
	/// </summary>
	/// <returns></returns>
	bool GetIsActive()const { return m_isActive; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">設定する座標</param>
	void SetPos(Vector3 pos) { m_transform.position = pos; }

	/// <summary>
	/// 設定
	/// </summary>
	/// <param name="amount">設定する値</param>
	/// <param name="fontHandle">設定する画像</param>
	/// <param name="type">設定するタイプ</param>
	void SetData(int amount, int fontHandle, PopUpUI::TextType type);

private:

	Transform m_transform;

	/// <summary>
	/// 表示する数字の値
	/// </summary>
	int m_amount;

	/// <summary>
	/// フォント
	/// </summary>
	int m_fontHandle;

	/// <summary>
	/// 色
	/// </summary>
	int m_color;

	/// <summary>
	/// タイマー
	/// </summary>
	float m_timer;

	/// <summary>
	/// 寿命がきたか
	/// </summary>
	bool m_isActive;

};
