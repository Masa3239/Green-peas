#pragma once

#include "../Scene/SceneBase.h"

class Fader
{
public:

	/// <summary>
	/// コンストラクタ
	/// メンバ変数の初期化を行う
	/// </summary>
	/// <param name="scene">属するシーンのポインタ</param>
	Fader(SceneBase* scene);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Fader() = default;

	/// <summary>
	/// フェードの更新
	/// </summary>
	/// <returns>シーン遷移を行うならtrue、行わないならfalse</returns>
	bool Update();

	/// <summary>
	/// フェードの描画
	/// </summary>
	void Draw() const;

	/// <summary>
	/// フェードアウト開始
	/// </summary>
	template <class ClassName>
	void StartFadeOut(int speed = 210, int color = 0);

	/// <summary>
	/// m_fadeColorのゲッター
	/// </summary>
	/// <returns>フェーダーの色を返す</returns>
	int GetFadeColor() const { return mFadeColor; }

	/// <summary>
	/// m_fadeColorのセッター
	/// </summary>
	/// <param name="color">フェーダーの色</param>
	void SetFadeColor(const int color) { mFadeColor = color; }

	/// <summary>
	/// フェード中かどうか
	/// </summary>
	/// <returns>フェード中ならtrue</returns>
	bool IsFading() const;

	/// <summary>
	/// フェードイン中かどうか
	/// </summary>
	/// <returns>フェードイン中ならtrue</returns>
	bool IsFadingIn() const;

	/// <summary>
	/// フェードアウト中かどうか
	/// </summary>
	/// <returns>フェードアウト中ならtrue</returns>
	bool IsFadingOut() const;

private:

	/// <summary>
	/// フェード処理
	/// </summary>
	/// <returns>フェードが完了したらtrue</returns>
	bool ProcessFade();

	/// <summary>
	/// フェードが完了したときにフェードを停止させる
	/// </summary>
	void StopFade();

	/// <summary>
	/// フェードインが完了したかどうか
	/// </summary>
	/// <returns>フェードインが完了しているならtrue</returns>
	bool IsDoneFadeIn() const;

	/// <summary>
	/// フェードアウトが完了したかどうか
	/// </summary>
	/// <returns>フェードアウトが完了しているならtrue</returns>
	bool IsDoneFadeOut() const;

	/// <summary>
	/// 自身が属するシーンのポインタ
	/// </summary>
	SceneBase* mPtrScene;

	// フェードの色
	int mFadeColor;
	// フェードの輝度
	int mFadeBright;
	// フェードのスピード
	int mFadeSpeed;
};

template<class ClassName>
inline void Fader::StartFadeOut(int speed, int color)
{
	if (IsFadingOut()) return;

	mFadeColor = color;
	mFadeSpeed = speed;

	mPtrScene->SetNextScene(new ClassName);
}
