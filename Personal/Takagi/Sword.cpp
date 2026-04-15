#include "Sword.h"
#include"../../Object/GameObject.h"
#include"../../Utility/MyMath.h"
#include"../../Utility/Transform.h"
#include"../../Utility/Vector3.h"
#include"../../Utility/Time.h"
#include<DxLib.h>
#include<math.h>
namespace {
	const char* const kFilePath = "Personal\\Takagi\\Resource\\Golden Sword.png";
	/// <summary>
	/// 武器の表示座標
	/// </summary>
	constexpr Vector3 kOffset = { -13.0f,10.0f,0.0f };
	constexpr float kLerpSwing = 12.0f;
	constexpr Transform kSwingUp = {
		{0,0,0},
		{0,60 * MyMath::ToRadian,0},
		{0,0,0}
	};
	constexpr float kShowRadian = -45 * MyMath::ToRadian;
	constexpr float kSwingRadian = 60 * MyMath::ToRadian;
	constexpr float kColRadius = 10;
}

Sword::Sword(ObjectManager* objManager) :
	Weapon(objManager),
	attack(false)
{
	// グラフィックハンドルの読み込み
	m_graphHandle = LoadGraph(kFilePath);

	// トランスフォームの初期設定
	GetTransform().Reset();
	
	// 武器を振る際のTransformを初期化
	m_swing.Reset();
	m_desireRadian = 0;
	m_swingState = Swing::Normal;
	m_circle = Collision::Circle(Vector3(), kColRadius);
}

Sword::~Sword()
{
	DeleteGraph(m_graphHandle);
}

void Sword::Init()
{
}

void Sword::End()
{
}

void Sword::Update()
{
	float time = Time::GetInstance().GetDeltaTime();
	float differ = m_desireRadian - m_swing.rotation.y;
	differ = MyMath::NormalizeAngle(differ * MyMath::ToDegree) * MyMath::ToRadian;
	m_swing.rotation.y += differ*kLerpSwing * time;
	if (differ * differ < 0.1f * 0.1f) {
		if (m_swingState == Swing::Up) {
			m_desireRadian = m_attackRadian - kSwingRadian;
			m_swingState = Swing::Down;
		}
		else if (m_swingState == Swing::Down) {
			m_desireRadian = m_attackRadian;
			attack = false;
			m_swingState = Swing::Normal;
		}
	}

	Vector3 drawPos = GetTransform().position;
	if (GetTransform().rotation.y >= 0) {
		drawPos.x += kOffset.x;
		drawPos.y += kOffset.y;
	}
	else {
		drawPos.x -= kOffset.x;
		drawPos.y += kOffset.y;
	}

	if (attack) {
	drawPos.x = sinf(m_swing.rotation.y);
	drawPos.y = -cosf(m_swing.rotation.y);
	drawPos = drawPos.GetNormalize();
	//if (attack) {
		drawPos *= 60;
	/*}
	else
	{
		drawPos *= 30;
	}*/
	drawPos += GetTransform().position;
	}
	else {
		if (GetTransform().rotation.y >= 0) {
		m_desireRadian = -150*MyMath::ToRadian;
		}
		else {
		m_desireRadian = 150*MyMath::ToRadian;
		}
		m_attackRadian= GetTransform().rotation.y;
	}
	m_swing.position += (drawPos - m_swing.position) * 50 * time;
	m_circle.SetPosition(drawPos);
}

void Sword::Draw()
{
	bool reverseX = false;
	if (GetTransform().rotation.y >= 0) {
		reverseX = false;
	}
	else {
		reverseX = true;
	}
	float radian = /*GetTransform().rotation.y+*/m_swing.rotation.y + (kShowRadian)*MyMath::Sign(GetTransform().rotation.y);

	//if (attack) {
	//}
	//else {
	//	radian = 0;
	//}

	DrawRotaGraph(m_swing.position.x, m_swing.position.y, 1, radian, m_graphHandle, TRUE, reverseX);
	printfDx("角度 : %f\n", GetTransform().rotation.y);
	printfDx("attack : %d\n", attack);
	m_circle.DebugDraw();
}

void Sword::Attack()
{
	if (m_swingState != Swing::Normal)return;
	m_desireRadian = m_attackRadian + kSwingRadian;
	m_swing.rotation.y = m_desireRadian;
	attack = true;
	m_swingState = Swing::Up;
}
