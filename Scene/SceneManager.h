#pragma once

// 前方宣言
class SceneBase;

/// <summary>
/// ゲームシーン全体を管理するクラス
/// </summary>
class SceneManager {

public:

	/// <summary>
	/// コンストラクタ
	/// メンバの初期設定
	/// </summary>
	SceneManager();

	/// <summary>
	/// デストラクタ
	/// メンバの後処理
	/// </summary>
	virtual ~SceneManager();

	/// <summary>
	/// メンバの設定
	/// </summary>
	void Init();

	/// <summary>
	/// メンバの破棄
	/// </summary>
	void End();

	/// <summary>
	/// 毎フレームの処理
	/// </summary>
	void Update();

	/// <summary>
	/// シーンの描画
	/// </summary>
	void Draw();

private:

	// シーンのポインタ
	SceneBase* m_pScene;
};