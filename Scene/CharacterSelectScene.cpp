#include "CharacterSelectScene.h"
#include"../Personal/Takagi/SceneTestTakagi.h"
#include"../Personal/Takagi/Result/ResultTestScene.h"
#include"../System/InputManager.h"
#include"../System/Input/Gamepad.h"
#include"../Personal/Takagi/RotateCharacter.h"
#include"../Personal/Takagi/BuffManager.h"
#include"SceneInGame.h"
CharacterSelectScene::CharacterSelectScene()
{
	GetCarryOver().Reset();
	m_characters = new RotateCharacter();
}

CharacterSelectScene::~CharacterSelectScene()
{
}

void CharacterSelectScene::Init()
{
}

void CharacterSelectScene::End()
{
}

SceneBase* CharacterSelectScene::Update()
{
	m_characters->Update();
	GetCarryOver().characterJob = m_characters->GetSelectJob();
	if (InputManager::GetInstance().IsPressed(Input::Action::Confirm)) {
		return new SceneInGame;
	}
	//if (Gamepad::GetInstance().IsDown(XINPUT_BUTTON_START)) {
	//	//return new ResultTestScene;
	//	return new ;
	//}
	return this;
}

void CharacterSelectScene::Draw()
{
	m_characters->Draw();
}

void CharacterSelectScene::PreDraw()
{
}

void CharacterSelectScene::PostDraw()
{
}
