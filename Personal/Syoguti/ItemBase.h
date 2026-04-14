#pragma once

/// <summary>
/// アイテムの基本クラス
/// </summary>
class ItemBase
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ItemBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ItemBase() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 終了
	/// </summary>
	virtual void End() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// グラフパスをセットするセッター関数
	/// </summary>
	/// <param name="graphHandlePath"></param>
	virtual void SetGraphHandlePath(int graphHandlePath) { m_graphHandle = graphHandlePath; }

protected:

	/// <summary>
	/// 画像の座標
	/// </summary>
	float m_posX;
	float m_posY;

	/// <summary>
	/// 画像のサイズ
	/// </summary>
	int m_sizeX;
	int m_sizeY;

	/// <summary>
	/// 画像ハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// 画像のスケール
	/// </summary>
	float m_scale;
};

