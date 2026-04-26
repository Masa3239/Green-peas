#pragma once
#include<memory>
class BackBoard;
class ResultHead;

class ResultShow
{
public:
	enum {
		Back,
		Head,
		Max
	};
	ResultShow();
	~ResultShow();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();
	/// <summary>
	/// 終了処理
	/// </summary>
	void End();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private:

	/// <summary>
	/// 数値の表示をするフォントハンドル
	/// </summary>
	int m_fontHandle;
	/// <summary>
	/// 背景のポインタ
	/// </summary>
	std::unique_ptr<BackBoard> m_backBoard;
	/// <summary>
	/// クリアしたかどうかの表示をするポインタ
	/// </summary>
	std::unique_ptr<ResultHead> m_resultHead;
	/// <summary>
	/// リザルト演出の状態
	/// </summary>
	int m_phase;
	float m_interval;

};

