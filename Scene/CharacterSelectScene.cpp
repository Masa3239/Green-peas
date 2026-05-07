#include "CharacterSelectScene.h"
#include"../Personal/Takagi/SceneTestTakagi.h"
#include"../Personal/Takagi/Result/ResultTestScene.h"
#include"../System/InputManager.h"
#include"../System/Input/Gamepad.h"
#include"../Personal/Takagi/CharaSelect/RotateCharacter.h"
#include"../Personal/Takagi/BuffManager.h"
#include"SceneInGame.h"
#include"../Personal/Takagi/CharaSelect/Gear.h"
CharacterSelectScene::CharacterSelectScene()
{
	GetCarryOver().Reset();
	m_characters = std::make_unique<RotateCharacter>();
	//m_gear = std::make_unique<Gear>();
}

CharacterSelectScene::~CharacterSelectScene()
{
}

void CharacterSelectScene::Init()
{
	//m_gear->Init();
}

void CharacterSelectScene::End()
{
	//m_gear->End();

}

SceneBase* CharacterSelectScene::Update()
{
	m_characters->Update();
	//m_gear->Update();
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
	//m_gear->Draw();
}

void CharacterSelectScene::PreDraw()
{
}

void CharacterSelectScene::PostDraw()
{
}
