#include "SceneTestOBB.h"
#include "../Utility/Vector3.h"
#include "../System/InputManager.h"

namespace
{
	constexpr Vector3 kCirclePos = { 400, 300, 0 };
	constexpr float kCircleRadius = 20.0f;

	constexpr Vector3 kOBBInitPos = { 200, 300, 0 };
	constexpr Vector3 kOBBSize = { 50, 80, 0 };
	//constexpr float kOBBRadian = 0;
	constexpr float kOBBRadian = 0.785398f; // 1/4 pi
}

SceneTestOBB::SceneTestOBB() :
	m_circle(Collision::Circle(kCirclePos, kCircleRadius)),
	m_obb(Collision::OBB(kOBBInitPos, kOBBSize, kOBBRadian)),
	m_obb2(Collision::OBB(kOBBInitPos, kOBBSize, 2))
{
}

SceneTestOBB::~SceneTestOBB()
{
}

void SceneTestOBB::Init()
{
}

void SceneTestOBB::End()
{
}

SceneBase* SceneTestOBB::Update()
{
	Vector2 v;
	v += InputManager::GetInstance().GetAsVector2(Input::Action::Move) * 5;

	m_obb.SetPosition(m_obb.GetPosition() + Vector3(v.x, v.y, 0.0f));

	return this;
}

void SceneTestOBB::Draw()
{
	m_circle.DebugDraw();
	m_obb.DebugDraw();
	m_obb2.DebugDraw();

	printfDx("%d\n", m_obb.CheckCollision(m_circle));
	printfDx("%d\n", m_obb.CheckCollision(m_obb2));
}

void SceneTestOBB::PreDraw()
{
}

void SceneTestOBB::PostDraw()
{
}
