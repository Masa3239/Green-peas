#pragma once
#include"../../Utility/Transform.h"

class PopUpText
{

public:

	enum class Type {

		Damage = 0,
		Heal,
		Max,

	};

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

private:

	Transform m_transform;

	int m_amount;

	int m_fontHandle;

	int m_color;

	float m_timer;

	bool m_isDead;

};

