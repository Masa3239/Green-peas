#include "CharacterSelectScene.h"
#include"../Personal/Takagi/SceneTestTakagi.h"
#include"../Personal/Takagi/Result/ResultTestScene.h"
#include"../System/InputManager.h"
#include"../System/Input/Gamepad.h"
#include"../Personal/Takagi/CharaSelect/RotateCharacter.h"
#include"../Personal/Takagi/BuffManager.h"
#include"SceneInGame.h"
#include"../Personal/Takagi/CharaSelect/Gear.h"
#include "../System/SoundManager.h"
CharacterSelectScene::CharacterSelectScene()
{
	GetCarryOver().Reset();
	m_characters = std::make_unique<RotateCharacter>();
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
		SoundManager::GetInstance().PlaySe(Sound::SE::CharactorButton);
		return new SceneInGame;
	}

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
