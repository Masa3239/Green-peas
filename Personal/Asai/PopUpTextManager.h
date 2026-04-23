#pragma once
#include<memory>
#include<vector>
#include"../Asai/PopUpText.h"

#include"../../Utility/Vector3.h"

class PopUpTextManager
{

public:

	PopUpTextManager();
	~PopUpTextManager();

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
	/// テキストを生成
	/// </summary>
	void CreateText(Vector3 position, int amount, PopUpUI::TextType type);

private:

	std::vector<std::unique_ptr<PopUpText>>m_pTexts;

	std::vector<int>m_textFonts;

};
