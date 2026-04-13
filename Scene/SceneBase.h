#pragma once

/// <summary>
/// 各画面の基本クラス
/// 基本的にはこのクラスを継承して各画面のクラスを作成する
/// 作成したクラスをSceneManagerクラスから呼び出すことで保守しやすくする
/// </summary>
class SceneBase {

public:

	/// <summary>
	/// コンストラクタ
	/// メンバ変数の初期設定
	/// </summary>
	SceneBase();

	/// <summary>
	/// デストラクタ
	/// 派生クラスを破棄した時に備えて仮想デストラクタ化
	/// </summary>
	virtual ~SceneBase(){}

	/// <summary>
	/// 初期設定
	/// 具体的な処理は各画面毎で異なるので純粋仮想関数にして派生先で実装
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 終了処理
	/// 具体的な処理は各画面毎で異なるので純粋仮想関数にして派生先で実装
	/// </summary>
	virtual void End() = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <returns>自身のポインタを返す</returns>
	virtual SceneBase* Update() { return this; }

	/// <summary>
	/// 描画処理
	/// 具体的な処理は各画面毎で異なるので純粋仮想関数にして派生先で実装
	/// </summary>
	virtual void Draw() = 0;

	//-----------------------------------
	// フェード関連の処理
	//-----------------------------------

	/// <summary>
	/// フェードの更新
	/// </summary>
	void UpdateFade();

	/// <summary>
	/// フェードの描画
	/// </summary>
	void DrawFade() const;

	/// <summary>
	/// フェードイン中かどうかを判定
	/// </summary>
	/// <returns>フェードイン中ならtrue</returns>
	bool IsFadingIn() const;

	/// <summary>
	/// フェードアウト中かどうかを判定
	/// </summary>
	/// <returns>フェードアウト中ならtrue</returns>
	bool IsFadingOut() const;

	/// <summary>
	/// フェード中かどうかを判定
	/// </summary>
	/// <returns>フェード中ならtrue</returns>
	bool IsFading() const;

	/// <summary>
	/// フェードアウト開始
	/// </summary>
	void StartFadeOut();


protected:

	// フェード関連で必要な変数
	// フェードの色
	int m_fadeColor;
	// フェードの輝度
	int m_fadeBright;
	// フェードのスピード
	int m_fadeSpeed;
	// フェードアウトを行っているかどうか
	bool m_isFadeOut;

};
