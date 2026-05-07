#pragma once
#include"../Asai/PlayerUIBase.h"
#include"../Takagi/Player.h"

class PlayerWeaponUI :public PlayerUIBase
{

public:

	PlayerWeaponUI();
	~PlayerWeaponUI() = default;

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
	/// 枠を描画
	/// </summary>
	void DrawFrame();

	/// <summary>
	/// 武器を描画
	/// </summary>
	void DrawWepon();

private:

	int m_weaponGraph[kWeaponMaxNum];

	float m_weaponScale[kWeaponMaxNum];

};
