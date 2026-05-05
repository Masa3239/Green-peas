#include "Gear.h"
#include"../../../Utility/Game.h"
#include"../../../Utility/Vector3.h"
#include"../../../Utility/Time.h"
#include"../../../Utility/MyMath.h"
#include"../../../Chara/Collision.h"
#include"../RadToPos.h"
#include<DxLib.h>

namespace {
	Vector3 kStartPos = { Game::kScreenWidth * 0.3f,Game::kScreenHeight * 0.5f,0 };
	Vector3 kEndPos = { kStartPos.x + Game::kScreenWidth * 0.5f ,kStartPos.y,0 };
	const char* const kPath = "Resource\\CharaSelectUI\\icon_gear.png";
	float kSpeedUp=2;
	float kScale = 1;
	float kRadius = 110 * kScale;

	float kCircum = (kRadius * 2) * DX_PI_F;
	float kInitRad = 90 * MyMath::ToRadian;
}

Gear::Gear():
	m_graphHandle(-1),
	m_rotateSpeed(0),
	m_transform()
{
	m_transform.Reset();
	m_graphHandle = LoadGraph(kPath);
	m_transformss.Reset();
	m_transformss.position = kEndPos;
	m_transformss.rotation.z = -kInitRad;
}

Gear::~Gear()
{
	DeleteGraph(m_graphHandle);
}

void Gear::Init()
{
}

void Gear::End()
{
}

void Gear::Update()
{
	float time = Time::GetInstance().GetDeltaTime();
	float moveRad = m_rotateSpeed * time;
	m_transform.rotation.z -= moveRad;
	m_rotateSpeed += time * kSpeedUp;
	m_rotateSpeed = 2;
	m_transform.rotation.z = MyMath::NormalizeRadian(m_transform.rotation.z);



	float move = kCircum * (moveRad / (DX_PI_F * 2));
	int dir = -1;
	if (MyMath::Abs(m_transformss.rotation.z) < kInitRad) {
		dir *= -1;
	}
	m_transformss.position.x += move * dir;
	m_transformss.position.x = MyMath::Clamp(m_transformss.position.x, kStartPos.x, kEndPos.x);

	if (m_transformss.position.x == kStartPos.x||
		m_transformss.position.x == kEndPos.x) {
		m_transformss.rotation.z -= moveRad;
	}
	m_transformss.rotation.z = MyMath::NormalizeRadian(m_transformss.rotation.z);
}

void Gear::Draw()
{
	DrawRotaGraph(kStartPos.x, kStartPos.y, kScale, m_transform.rotation.z, m_graphHandle, TRUE);
	DrawRotaGraph(kEndPos.x, kEndPos.y, kScale, m_transform.rotation.z, m_graphHandle, TRUE);
	Collision::Circle circle;
	circle.SetPosition(kStartPos);
	circle.SetRadius(kRadius);
	circle.DebugDraw();
	circle.SetPosition(kEndPos);
	circle.DebugDraw();
	printfDx("角度 : %f\n", m_transform.rotation.z);
	float abs = MyMath::Abs(m_transformss.rotation.z);
	printfDx("角度ss : %f\n", abs);

	DrawCircle(m_transformss.position.x, m_transformss.position.y, 10, 0x00ff00);
	Vector3 drawPos = RadToPos(m_transformss.rotation.z, kRadius, m_transformss.position);
	DrawCircle(drawPos.x, drawPos.y, 10, 0xff0000);


}
