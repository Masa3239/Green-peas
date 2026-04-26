#include "ResultTestScene.h"
#include"../SceneTestTakagi.h"
#include"../../../Scene/CharacterSelectScene.h"
#include"../System/InputManager.h"
#include"../System/Input/Gamepad.h"
#include"ResultShow.h"
ResultTestScene::ResultTestScene() :
	m_resultShow(nullptr)
{
	GetCarryOver().Reset();
	// リザルトの生成
	m_resultShow = std::make_unique<ResultShow>();
}

ResultTestScene::~ResultTestScene()
{
}

void ResultTestScene::Init()
{
	// リザルトの初期化
	m_resultShow->Init(m_carryOver);
}

void ResultTestScene::End()
{
	// リザルトの終了
	m_resultShow->End();
}

SceneBase* ResultTestScene::Update()
{
	// リザルトの更新処理
	SceneBase* nextScene =m_resultShow->Update();
	if (nextScene)return nextScene;
	return this;
}

void ResultTestScene::Draw()
{
	// リザルトの描画
	m_resultShow->Draw();
}

void ResultTestScene::PreDraw()
{
}

void ResultTestScene::PostDraw()
{
}
