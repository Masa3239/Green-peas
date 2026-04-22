#include "PauseManager.h"
#include <DxLib.h>
#include "../Utility/Game.h"
#include "../System/ObjectManager.h"
#include "../Object/GameObject.h"

PauseManager& PauseManager::GetInstance()
{
	static PauseManager instance;
	
	return instance;
}

void PauseManager::End()
{
	// 画面のグラフィックを解放する
	if (m_screenGraph != -1)
	{
		DeleteGraph(m_screenGraph);
	}

	m_objManager = nullptr;
	m_activeGameObjects.clear();
}

void PauseManager::Update()
{
	// オブジェクトの描画を停止しても画面に写し続けるために、
	// ポーズ前の画面を取得する
	if (m_isPause && m_screenGraph == -1)
	{
		m_screenGraph = MakeScreen(Game::kScreenWidth, Game::kScreenHeight);

		GetDrawScreenGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_screenGraph);
	}

	if (m_screenGraph != -1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);
		DrawGraph(0, 0, m_screenGraph, 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	}
}

void PauseManager::TogglePause()
{
	m_isPause = !m_isPause;

	if (m_isPause)
	{
		auto objects = m_objManager->GetAllGameObjects();

		for (const auto& obj : objects)
		{
			// アクティブなすべてのゲームオブジェクトを停止する
			if (obj->GetState() != GameObject::State::Active) continue;

			obj->SetState(GameObject::State::Deactive);
			// 元々アクティブなオブジェクトのみを配列に加える
			m_activeGameObjects.emplace_back(obj);
		}
	}
	else
	{
		DeleteGraph(m_screenGraph);
		m_screenGraph = -1;

		// 元々アクティブなゲームオブジェクトをアクティブに戻す
		for (const auto& obj : m_activeGameObjects)
		{
			obj->SetState(GameObject::State::Active);
		}
		m_activeGameObjects.clear();
	}
}
