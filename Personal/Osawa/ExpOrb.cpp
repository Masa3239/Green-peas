#include "ExpOrb.h"
#include <DxLib.h>
#include "../Personal/Takagi/Player.h"
#include "../Utility/Time.h"
#include "../Utility/MyRandom.h"

namespace
{
	// 初速の最大値
	constexpr float kMaxInitSpeed = 50.0f;

	// 加速度
	constexpr float kAccel = 3.0f;

	constexpr float kColliderSize = 3;
}

ExpOrb::ExpOrb(ObjectManager* objManager, int exp) :
	GameObject(objManager),
	m_speed(),
	m_expAmount(exp),
	m_collider(Collision::Circle{ Vector3::zero, m_expAmount * kColliderSize} ),
	m_pPlayer(nullptr)
{
}

ExpOrb::~ExpOrb()
{
}

void ExpOrb::Init()
{
	m_speed = Vector3(MyRandom::Float(-kMaxInitSpeed, kMaxInitSpeed), MyRandom::Float(-kMaxInitSpeed, kMaxInitSpeed), 0.0f);
}

void ExpOrb::End()
{
}

void ExpOrb::Update()
{
	Vector3& myPos = GetTransform().position;
	Vector3& playerPos = m_pPlayer->GetTransform().position;

	// ベクトル取得
	Vector3 vec = playerPos - myPos;

	// プレイヤーに向かって加速する
	m_speed += vec.GetNormalize() * kAccel;
	// 移動
	myPos += m_speed * Time::GetInstance().GetDeltaTime();

	m_collider.SetPosition(myPos);

	// プレイヤーに当たったら
	if (m_collider.CheckCollision(m_pPlayer->GetCircle()))
	{
		// 経験値をプレイヤーに与える
		m_pPlayer->ExpUp(m_expAmount);

		// 自身を削除する
		SetState(State::Dead);
	}
}

void ExpOrb::Draw()
{
	Vector3 pos = GetTransform().position;

	DrawCircle(pos.x, pos.y, m_expAmount, 0x00ff00);
}
