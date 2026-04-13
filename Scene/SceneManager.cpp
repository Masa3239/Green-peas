#include <cassert>
#include "SceneManager.h"
#include "SceneTest.h"
#include "../Utility/Input.h"

SceneManager::SceneManager() {

	m_pScene = nullptr;
}

SceneManager::~SceneManager() {}

void SceneManager::Init() {

	m_pScene = new SceneTest;
	m_pScene->Init();

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

	// 確認処理
	assert(m_pScene);
	if (!m_pScene) return;

	// シーンの切り替えもしくは更新
	SceneBase* pScene = m_pScene->Update();

	if ( pScene != m_pScene ) {

		m_pScene->End();
		delete m_pScene;

		// ポインタを初期化
		m_pScene = pScene;
		m_pScene->Init();
	}

}

void SceneManager::Draw() {

	// 確認処理
	assert(m_pScene);
	if (!m_pScene) return;

	m_pScene->Draw();

}

