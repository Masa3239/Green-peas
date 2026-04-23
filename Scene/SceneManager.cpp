#include <cassert>
#include "SceneManager.h"
#include "../Personal/Osawa/Scene/SceneSelection.h"
#include "../Scene/SceneInGame.h"
#include "../Utility/Input.h"
#include "../System/InputPad.h"
#include "../System/ObjectManager.h"
#include "../System/PauseManager.h"
#include "CarryOver.h"

SceneManager::SceneManager() {

	m_pScene = nullptr;
}

SceneManager::~SceneManager() {}

void SceneManager::Init() {

#ifdef _DEBUG
	m_pScene = new SceneSelection();
#else
	m_pScene = new SceneInGame();
#endif

	m_pScene->Init();
	Pad::Init();
}

void SceneManager::End() {

	// 確認処理
	assert(m_pScene);
	if (!m_pScene) return;

	m_pScene->End();
	delete m_pScene;
}

void SceneManager::Update() {

	// 入力更新
	Input::Update();
	Pad::Update();

	// 確認処理
	assert(m_pScene);
	if (!m_pScene) return;

	// シーンの切り替えもしくは更新
	SceneBase* pScene = m_pScene->Update();
	m_pScene->GetObjectManager()->Update();
	CarryOver carryOver = m_pScene->GetCarryOver();
	if ( pScene != m_pScene ) {

		m_pScene->End();
		delete m_pScene;

		// ポインタを初期化
		m_pScene = pScene;
		m_pScene->GetCarryOver() = carryOver;
		m_pScene->Init();
	}

}

void SceneManager::Draw() {

	// 確認処理
	assert(m_pScene);
	if (!m_pScene) return;

	m_pScene->PreDraw();

	m_pScene->Draw();

	m_pScene->GetObjectManager()->Draw();

	m_pScene->PostDraw();

	PauseManager::GetInstance().Update();
}

