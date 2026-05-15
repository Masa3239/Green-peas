#pragma once
#include"../Asai/PlayerUIBase.h"
#include"../../Utility/Vector3.h"

class PlayerStaminaBar :public PlayerUIBase
{

public:

	PlayerStaminaBar();
	~PlayerStaminaBar();

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

	PlayerUI::DrawType GetDrawType()const override;

	void SetPlayer(Player* pPlayer)override;

private:

	/// <summary>
	/// スタミナゲージを表示する位置
	/// </summary>
	Vector3 m_pos;

	/// <summary>
	/// 1F前の値
	/// </summary>
	float m_prevValue;

	/// <summary>
	/// 1F前と比べて変わったか
	/// </summary>
	bool m_isChanged;

};
