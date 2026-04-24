#include "BossBulletManager.h"
#include "BossBullet.h"

#include <DxLib.h>

namespace {

	// 画像のファイルパス
	const char* const kBulletGraphHandlePath = ".\\Resource\\ItemTest1.png";
}

BossBulletManager::BossBulletManager() :
	m_bulletGraphHandle(-1),
	m_pObjectMgr(nullptr),
	m_pPlayer(nullptr)
{
}

void BossBulletManager::Init()
{

	for (int i = 0;i < static_cast<int>(BossBulletBase::BulletType::Max); i++) {

		for (int j = 0; j < kMotionNum; j++) {

			m_bulletGraphHandle[i][j];
		}
	}

	// 画像の読み込み
	// m_bulletGraphHandle = LoadGraph(kBulletGraphHandlePath);
}

void BossBulletManager::End()
{
	for (auto& e : m_bullets) {
		e->End();
	}

	// 可変長配列を綺麗にする
	m_bullets.clear();

	DeleteGraph(m_bulletGraphHandle);
}

void BossBulletManager::Update()
{
	for (auto& e : m_bullets) {
		e->Update();
	}
}

void BossBulletManager::Draw()
{
	for (auto& e : m_bullets) {
		e->Draw();
	}
}

void BossBulletManager::Create(BossBulletBase::BulletType type, Vector3 position)
{
	std::unique_ptr<BossBulletBase> bullets;
	int graphHandle = -1;

	switch (type)
	{
	case BossBulletBase::BulletType::Normal:
		bullets = std::make_unique<BossBullet>(m_pObjectMgr);
		graphHandle = m_bulletGraphHandle;
		break;
	default:
		break;
	}

	if (!bullets || graphHandle == -1) return;

	// プレイヤーのポインタをセット
	bullets->SetPlayer(m_pPlayer);
	// 座標を引数の値にする
	bullets->GetTransform().position = position;
	bullets->Init();
	bullets->SetGraphHandle(m_bulletGraphHandle);

	m_bullets.push_back(std::move(bullets));

}

void BossBulletManager::Remove(int index)
{

	// インデックスの値が配列の範囲内かチェック
	if (index < 0 || index >= m_bullets.size()) {

		return;
	}

	// 指定した弾を削除
	m_bullets[index]->End();

	m_bullets.erase(m_bullets.begin() + index);
}

bool BossBulletManager::CheckHitCollision(const Collision::Shape& other)
{

	// 空きがあれば前詰めする前提の処理
	for (int i = m_bullets.size() - 1; i >= 0; i--) {

		// 弾のi番目と引数が当たっているかどうか調べる
		if (!m_bullets[i]->GetCollision().CheckCollision(other)) continue;

		Remove(i);

		// 当たっていたらtrueを返す
		return true;
	}
	// 当たっていなければfalseを返す
	return false;
}
