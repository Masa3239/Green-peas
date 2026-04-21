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
	m_circle = Collision::Circle(GetTransform().position, kCollisionSize);
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
	GetTransform().position.x += sinf(GetTransform().rotation.z) * kSpeed * deltaTime;
	GetTransform().position.y += -cosf(GetTransform().rotation.z) * kSpeed * deltaTime;

	//当たり判定の更新
	m_circle.SetPosition(GetTransform().position);

	//移動距離を取得
	float distance = (m_spawnPos - GetTransform().position).GetSqLength();
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
	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y, 1.0f, GetTransform().rotation.z, m_graphHandle, TRUE);

	DrawCircle(GetTransform().position.x, GetTransform().position.y, kCollisionSize * m_scale, TRUE, 0xffff00);

}

void Arrow::DebugDraw()
{

	//非アクティブならスルー
	if (!m_isActive)return;

	printfDx(m_isActive ? "Arrow Active\n" : "Arrow !Active\n");
	printfDx("Arrow Scale %f\n", m_scale);

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
	GetTransform() = transform;
	//アクティブにする
	m_isActive = true;
	//スポーン位置を設定
	m_spawnPos = transform.position;

}

void Arrow::SetScale(float scale)
{
	//m_scaleの変更
	m_scale = scale;
	//当たり判定のサイズを変更
	m_circle = Collision::Circle(GetTransform().position, kCollisionSize * scale);

}
