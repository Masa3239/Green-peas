#include "Fader.h"
#include <DxLib.h>
#include "../Utility/Color.h"
#include "../Utility/Time.h"

namespace
{
	// デフォルトフェード速度
	constexpr int kDefaultFadeSpeed = 210;
}

Fader::Fader(SceneBase* scene) :
	mPtrScene(scene),
	mFadeColor(Color::kBlack),
	mFadeBright(255),
	mFadeSpeed(-kDefaultFadeSpeed)
{
}

bool Fader::Update()
{
	// フェード処理を行う
	return ProcessFade();
}

void Fader::Draw() const
{
	// ウィンドウサイズを取得
	int width, height;
	GetWindowSize(&width, &height);

	// 透明度を設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mFadeBright);

	// フェードを描画
	DrawBox(0, 0, width, height, mFadeColor, true);

	// 透明度をリセット
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool Fader::ProcessFade()
{
	// フェード処理を行わないなら処理を停止
	if (!IsFading()) return false;

	// フェードアウトを行っているかどうか
	bool isFadeOut = IsFadingOut();

	// フェードインアウト
	mFadeBright += mFadeSpeed * Time::GetInstance().GetDeltaTime();

	// フェードが完了したらフェードを停止
	if (IsDoneFadeIn() || IsDoneFadeOut())
	{
		StopFade();
	}

	// フェードアウトが終わったら次の画面へ遷移
	if (!IsFading() && isFadeOut)
	{
		return true;
	}

	return false;
}

void Fader::StopFade()
{
	mFadeSpeed = 0;

	if (IsDoneFadeIn()) mFadeBright = 0;
	if (IsDoneFadeOut()) mFadeBright = 255;
}

bool Fader::IsFading() const
{
	return IsFadingIn() || IsFadingOut();
}

bool Fader::IsFadingIn() const
{
	return mFadeSpeed < 0;
}

bool Fader::IsFadingOut() const
{
	return mFadeSpeed > 0;
}

bool Fader::IsDoneFadeIn() const
{
	return mFadeBright <= 0;
}

bool Fader::IsDoneFadeOut() const
{
	return mFadeBright >= 255;
}
