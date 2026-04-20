#include "Arrow.h"
#include"../Asai/BulletBase.h"
#include"../../Chara/Collision.h"
#include"../../Object/GameObject.h"
#include"../../Utility/Transform.h"

#include<DxLib.h>
#include<math.h>
#include"../../Utility/Time.h"

namespace {
	//当たり判定のサイズ
	constexpr float kCollisionSize = 20.0f;
	//スピード
	constexpr float kSpeed = 300.0f;
	//最大移動距離
	constexpr float kMaxMoveDistance = 500.0f;

}

Arrow::Arrow(ObjectManager* objManager):
	BulletBase(objManager)
{
	m_circle = Collision::Circle(m_transform.position, kCollisionSize);
}

void Arrow::Init()
{

	m_isActive = false;

}

void Arrow::Update()
{
	//非アクティブならスルー
	if (!m_isActive)return;

	//デルタタイムを取得
	float deltaTime = Time::GetInstance().GetDeltaTime();

	//移動
	m_transform.position.x += cosf(m_transform.rotation.z) * kSpeed * deltaTime;
	m_transform.position.y += sinf(m_transform.rotation.z) * kSpeed * deltaTime;

	//当たり判定の更新
	m_circle.SetPosition(m_transform.position);

	//移動距離を取得
	float distance = (m_spawnPos - m_transform.position).GetSqLength();
	//移動距離の最大値じゃないならスルー
	if (distance <= kMaxMoveDistance* kMaxMoveDistance)return;

	//非アクティブにする
	m_isActive = false;

}

void Arrow::Draw()
{

	//非アクティブならスルー
	if (!m_isActive)return;

	//画像の描画
	DrawRotaGraph(m_transform.position.x, m_transform.position.y, 1.0f, m_transform.rotation.z, m_graphHandle, TRUE);

	DrawCircle(m_transform.position.x, m_transform.position.y, kCollisionSize, TRUE, 0xffff00);

}

void Arrow::DebugDraw()
{

	//非アクティブならスルー
	if (!m_isActive)return;

	printfDx(m_isActive ? "Arrow Active\n" : "Arrow !Active\n");

	//当たり判定の描画
	m_circle.DebugDraw();

}

void Arrow::End()
{

	DeleteGraph(m_graphHandle);

}

void Arrow::Shot(Transform transform)
{

	//アクティブならスルー
	if (m_isActive)return;

	//セット
	m_transform = transform;
	//アクティブにする
	m_isActive = true;
	//スポーン位置を設定
	m_spawnPos = transform.position;

}
