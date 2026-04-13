
#include "SceneTest.h"
#include "SceneBase.h"
#include <DxLib.h>
#include <memory>
#include "../Utility/Input.h"
#include "../Utility/Color.h"
#include "../Utility/GameSetting.h"
#include "../Utility/Vector3.h"
//#include "../Chara/CollisionSphere.h"
#include "../Chara/Collision.h"
//#include "../Object/Grass.h"
//#include "../Object/GrassManager.h"
#include "../System/SoundManager.h"
#include <math.h>

#include "../Chara/Collision.h"

namespace {

	constexpr float kLineAreaSize = 10000.0f;	// 地面を描画する線のエリアの大きさ
	constexpr int kLineNum = 50;				// 地面を描画する線の数

	// ビルボードで使用する画像のファイルパス
	const char* const kBillBoardDataPath = ".\\Resource\\image\\DxLogo.png";

	constexpr Vector3 kInitGrassPos = { 0.0f, 0.0f, -400.0f };	// 草の初期座標

	constexpr Vector3 kInitCranePos = { 0.0f, 50.0f, -400.0f };

	constexpr float kGrassCreateAreaLength = 1000.0f;			// 草を生成するエリアの長さ
}

SceneTest::SceneTest() :
	m_pBox(nullptr),
	m_isHit(false)
{
}

SceneTest::~SceneTest() {}

void SceneTest::Init() {

	//m_pSound->LoadSe();
	//m_pSound->LoadBGM();

	//m_pBox = std::make_unique<Collision::AABB>(Vector3(0, 0, 200), Vector3(150, 150, 150));

	// シングルトンのSoundManagerでの読み込み
	SoundManager::GetInstance().LoadBGM();
	SoundManager::GetInstance().LoadSe();

	// m_pSound->PlayBGM(Sound::BGM::Title);
	//SoundManager::GetInstance().PlayBGM(Sound::BGM::Menu);
}

void SceneTest::End() {


	SoundManager::GetInstance().Release();

	//m_pSound->Release();
	//delete m_pSound;
	//m_pSound = nullptr;
}

SceneBase* SceneTest::Update() {

	//// フェード処理が行われているか判定
	//if ( SceneBase::IsFading() ) {
	//
	//	m_isFadeOut = SceneBase::IsFadingOut();
	//	
	//	// フェードの更新処理
	//	SceneBase::UpdateFade();
	//
	//	// フェードが終わったら次の画面へ遷移
	//	if ( !SceneBase::IsFading() && m_isFadeOut ) {
	//
	//		// return (次のシーン)
	//	}
	//}
	//
	//// フェード処理が行われていない時
	//if ( !SceneBase::IsFading() ) {
	//
	//	// 次の画面に遷移する条件を満たしたらフェード開始
	//	
	//	// SceneBase::StartFadeOut();
	//
	//}

	return this;
}

void SceneTest::Draw() {

	//pBox->DebugDraw();

	DrawGround();

	printfDx("当たっているかどうか：%s\n", m_isHit ? "当たっている" : "当たっていない");

	//// フェードインアウトのフィルター処理
	//SceneBase::DrawFade();
}

void SceneTest::DrawGround()
{
	VECTOR pos1;
	VECTOR pos2;

	pos1 = VGet(-kLineAreaSize / 2.0f, 0.0f, -kLineAreaSize / 2.0f);
	pos2 = VGet(-kLineAreaSize / 2.0f, 0.0f, kLineAreaSize / 2.0f);

	for (int i = 0; i < kLineNum; i++)
	{
		DrawLine3D(pos1, pos2, Color::kWhite);
		pos1.x += kLineAreaSize / static_cast<float>(kLineNum);
		pos2.x += kLineAreaSize / static_cast<float>(kLineNum);
	}

	pos1 = VGet(-kLineAreaSize / 2.0f, 0.0f, -kLineAreaSize / 2.0f);
	pos2 = VGet(kLineAreaSize / 2.0f, 0.0f, -kLineAreaSize / 2.0f);

	for (int i = 0; i < kLineNum; i++)
	{
		DrawLine3D(pos1, pos2, Color::kWhite);
		pos1.z += kLineAreaSize / static_cast<float>(kLineNum);
		pos2.z += kLineAreaSize / static_cast<float>(kLineNum);
	}
}


