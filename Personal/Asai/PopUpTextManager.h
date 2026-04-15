#pragma once
#include<memory>
#include<vector>

class PopUpText;

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
	/// ダメージテキストを生成
	/// </summary>
	void CreateDamageText();

private:

	std::vector<std::unique_ptr<PopUpText>>m_Texts;

};
