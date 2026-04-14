#pragma once
class EnemyBoss
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyBoss();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyBoss() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 終了
	/// </summary>
	void End();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:

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
	/// 画像のハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// 画像のスケール
	/// </summary>
	float m_scale;

};

