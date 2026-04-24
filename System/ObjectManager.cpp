#include "ObjectManager.h"
#include "../Object/GameObject.h"

ObjectManager::ObjectManager() :
	m_isUpdatingGameObject(false)
{
}

void ObjectManager::Init()
{
}

void ObjectManager::End()
{
	// ゲームオブジェクトをすべて削除する
	// forループ中に配列のサイズが変わるとバグるため、
	// whileループを使用する
	while (!m_gameObjects.empty())
	{
		// ゲームオブジェクトを削除
		delete m_gameObjects.back();
	}
}

void ObjectManager::Update()
{
	UpdateGameObjects();

	RemoveDeadGameObjects();

	CheckCollision();
}

void ObjectManager::Draw()
{
	std::vector<GameObject*> objects = m_gameObjects;

	std::sort(objects.begin(), objects.end(), [](GameObject* a, GameObject* b)
		{
			return a->GetDrawOrder() < b->GetDrawOrder();
		});

	// ゲームオブジェクトを描画する
	for (const auto& obj : objects)
	{
		if (obj->GetState() != GameObject::State::Active) continue;
		obj->Draw();
	}
}

void ObjectManager::AddGameObject(GameObject* gameObject)
{
	// ゲームオブジェクトの更新中なら待機用の配列に追加する
	if (m_isUpdatingGameObject)
	{
		m_pendingGameObjects.emplace_back(gameObject);
	}
	// でなければそのまま配列に追加する
	else
	{
		m_gameObjects.emplace_back(gameObject);
	}
}

void ObjectManager::RemoveGameObject(GameObject* gameObject)
{
	auto iter = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
	if (iter != m_gameObjects.end())
	{
		m_gameObjects.erase(iter);
	}

	iter = std::find(m_pendingGameObjects.begin(), m_pendingGameObjects.end(), gameObject);
	if (iter != m_pendingGameObjects.end())
	{
		m_pendingGameObjects.erase(iter);
	}
}

void ObjectManager::ActiveAllGameObject()
{
	for (const auto& obj : m_gameObjects)
	{
		if (obj->GetState() == GameObject::State::Dead) continue;

		obj->SetState(GameObject::State::Active);
	}
}

void ObjectManager::DeactiveAllGameObject()
{
	for (const auto& obj : m_gameObjects)
	{
		if (obj->GetState() == GameObject::State::Dead) continue;

		obj->SetState(GameObject::State::Deactive);
	}
}

void ObjectManager::UpdateGameObjects()
{
	// ゲームオブジェクトを更新する
	m_isUpdatingGameObject = true;
	for (const auto& obj : m_gameObjects)
	{
		if (obj->GetState() != GameObject::State::Active) continue;
		obj->Update();
	}
	for (const auto& obj : m_gameObjects)
	{
		if (obj->GetState() != GameObject::State::Active) continue;
		obj->PostUpdate();
	}
	m_isUpdatingGameObject = false;

	// ゲームオブジェクトの更新中に生成されたゲームオブジェクトを配列に移動させる
	for (const auto& obj : m_pendingGameObjects)
	{
		m_gameObjects.emplace_back(obj);
	}
	m_pendingGameObjects.clear();
}

void ObjectManager::RemoveDeadGameObjects()
{
	// forループ中に配列のサイズが変わるとバグるため
	// ローカル変数にコピーしてから削除する
	std::vector<GameObject*> deadGameObject;

	for (const auto& obj : m_gameObjects)
	{
		if (obj->GetState() != GameObject::State::Dead) continue;

		deadGameObject.emplace_back(obj);
	}
	// ゲームオブジェクトを削除する
	for (auto& obj : deadGameObject)
	{
		obj->End();
		delete obj;
	}
}

void ObjectManager::CheckCollision()
{
	// 衝突を判定するゲームオブジェクトのリスト
	// 要素を消す処理を行うため、コピーしたものを使用する
	auto checkObjects = m_gameObjects;

	while (!checkObjects.empty())
	{
		// 状態がアクティブなら衝突をチェック
		if (checkObjects.front()->GetState() == GameObject::State::Active)
		{
			// 他のオブジェクトとの衝突を判定
			for (const auto& obj : checkObjects)
			{
				// 自分自身ならスキップ
				if (checkObjects.front() == obj) continue;

				// 状態がアクティブではないならスキップ
				if (obj->GetState() != GameObject::State::Active) continue;

				//// 衝突していなかったらスキップ
				//if (!Collision::CheckHitSphereCollision(checkObjects.front()->GetCollision(), obj->GetCollision())) continue;

				//// 衝突していたらお互いの衝突処理を呼ぶ
				//checkObjects.front()->CollideOtherObject(obj);
				//obj->CollideOtherObject(checkObjects.front());
			}
		}

		// 判定リストから削除
		checkObjects.erase(checkObjects.begin());
	}
}
