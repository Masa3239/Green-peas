#include "SceneBase.h"
#include <DxLib.h>
#include "../Utility/Color.h"
#include "../Utility/Game.h"
#include "../System/ObjectManager.h"
#include "../System/PauseManager.h"
#include "../Scene/Fader.h"

SceneBase::SceneBase() :
	m_objManager(nullptr),
	m_fader(nullptr)
{
	m_objManager = std::make_unique<ObjectManager>();
	m_objManager->Init();

	m_fader = std::make_unique<Fader>(this);
}

SceneBase::~SceneBase()
{
	m_objManager->End();

	PauseManager::GetInstance().End();
}

SceneBase* SceneBase::UpdateBase()
{
	if (m_fader->Update())
	{
		PauseManager::GetInstance().SetPauseState(false);
		return m_nextScene;
	}

	return Update();
}

void SceneBase::DrawBase()
{
	PreDraw();
	Draw();
	GetObjectManager()->Draw();
	PostDraw();

	m_fader->Draw();
}
