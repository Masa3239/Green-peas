#include "PauseManager.h"
#include <DxLib.h>
#include "../Utility/Game.h"
#include "../System/ObjectManager.h"
#include "../Object/GameObject.h"
#include "../Utility/Color.h"

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
	if (m_isToggled)
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

			m_screenGraph = MakeScreen(Game::kScreenWidth, Game::kScreenHeight);
			GetDrawScreenGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_screenGraph);
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

		m_isToggled = false;
	}
}

void PauseManager::Draw()
{
	// ポーズ直前の画面を描画
	if (m_screenGraph == -1) return;

	DrawGraph(0, 0, m_screenGraph, 1);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, Color::kBlack, 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
