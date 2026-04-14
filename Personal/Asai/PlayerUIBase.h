#pragma once
#include"../../Utility/Transform.h"

/// <summary>
/// 表示するプレイヤーのUIの情報
/// </summary>
namespace PlayerUI {

	/// <summary>
	/// 表示するプレイヤーのUIのタイプ
	/// </summary>
	struct Type {

		Transform transform;

		int hp;
		int hpMax;

		float stamina;
		float staminaMax;

		int level;

	};

	enum class DrawType {

		world,
		screen,

	};

}

class PlayerUIBase
{

protected:

	PlayerUIBase();

public:

	virtual ~PlayerUIBase() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// デバック描画
	/// </summary>
	virtual void DebugDraw() = 0;

	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void End() = 0;

	/// <summary>
	/// 描画タイプを取得する
	/// </summary>
	/// <returns></returns>
	virtual const PlayerUI::DrawType& GetDrawType()const = 0;

	virtual void SetState(const PlayerUI::Type& state) { m_state = state; }

protected:

	PlayerUI::Type m_state;

	/// <summary>
	/// 表示しているか
	/// </summary>
	bool m_isVisible;

	/// <summary>
	/// 
	/// </summary>
	float m_value;

	/// <summary>
	/// 最大値
	/// </summary>
	float m_max;

	/// <summary>
	/// 割合
	/// </summary>
	float m_rate;

};
