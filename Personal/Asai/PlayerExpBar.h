#pragma once
#include"../Asai/PlayerUIBase.h"

class PlayerExpBar :public PlayerUIBase
{

public:

	PlayerExpBar();
	~PlayerExpBar() = default;

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

	int m_fontHandle;

};
