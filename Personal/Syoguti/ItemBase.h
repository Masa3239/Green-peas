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
	virtual void Init(int graphHandle) = 0;

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
	/// 生成
	/// </summary>
	virtual void Regist() = 0;

protected:

	float m_posX;
	float m_posY;

	int m_sizeX;
	int m_sizeY;

	int m_graphHandle;
	float m_scale;
};

