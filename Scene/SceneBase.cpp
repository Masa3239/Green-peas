#include "SceneBase.h"
#include "../Utility/Color.h"
#include "../Utility/Game.h"
#include <DxLib.h>

namespace {

	// フェード速度
	constexpr int kFadeSpeed = 5;
}

// コンストラクタ
SceneBase::SceneBase() :
	m_fadeColor(Color::kBlack),
	m_fadeBright(255),
	m_fadeSpeed(-kFadeSpeed),
	m_isFadeOut(false)
{
}

// フェードの更新
void SceneBase::UpdateFade() {

	// フェードインアウト
	m_fadeBright += m_fadeSpeed;

	if (m_fadeBright >= 255) {

		m_fadeBright = 255;

		if ( m_fadeSpeed > 0 ) {

			m_fadeSpeed = 0;
		}
	}

	if ( m_fadeBright <= 0 ) {

		m_fadeBright = 0;

		if ( m_fadeSpeed < 0 ) {

			m_fadeSpeed = 0;
		}
	}
}

// フェードの描画
void SceneBase::DrawFade() const {

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeBright);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_fadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// フェードイン中かどうかを判定
bool SceneBase::IsFadingIn() const {

	if (m_fadeSpeed < 0) return true;
	return false;
}

// フェードアウト中かどうかを判定
bool SceneBase::IsFadingOut() const {

	if (m_fadeSpeed > 0) return true;
	return false;
}

// フェード中かどうかを判定
bool SceneBase::IsFading() const {

	return IsFadingIn() || IsFadingOut();
}

/// フェードアウト開始
void SceneBase::StartFadeOut() {

	m_fadeSpeed = kFadeSpeed;
}

