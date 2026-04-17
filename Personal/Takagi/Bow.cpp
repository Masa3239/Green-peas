#include "Bow.h"
#include "Weapon.h"
#include"../../Object/GameObject.h"
#include"../Asai/Arrow.h"
#include"../../System/InputPad.h"

namespace {
	constexpr float kShowRadian = -45 * MyMath::ToRadian;
	const char* const kHandlePath = "Image\\Bow.png";
}

Bow::Bow(ObjectManager* objManager) :
	Weapon(objManager)
{
	for (auto& arrows : m_pArrows) {
		arrows = nullptr;
		arrows = new Arrow(objManager);
	}
	m_graphHandle = LoadGraph(kHandlePath);
}

Bow::~Bow()
{
	DeleteGraph(m_graphHandle);
}

void Bow::Init()
{
}

void Bow::End()
{
}

void Bow::Update()
{
}

void Bow::Draw()
{
	float radian = GetTransform().rotation.y+m_swing.rotation.y /*+ (kShowRadian)*MyMath::Sign(GetTransform().rotation.y)*/;
	DrawRotaGraph(GetTransform().position.x, GetTransform().position.y, 1, radian, m_graphHandle, TRUE);
}

void Bow::Attack()
{
	if (!Pad::IsReleased(Pad::Button::X))return;
	m_pArrows[0]->Shot(GetTransform());
}

bool Bow::CheckAttack()
{
    return false;
}

Collision::Circle Bow::GetCollision()
{
	return Collision::Circle();
}

void Bow::CheckCollision()
{
}
