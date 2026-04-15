#include "Sword.h"
#include"../../Object/GameObject.h"
#include"../../Utility/MyMath.h"
#include"../../Utility/Transform.h"
#include"../../Utility/Vector3.h"
#include<DxLib.h>
namespace {
	const char* const kFilePath = "Personal\\Takagi\\Resource\\Golden Sword.png";
	/// <summary>
	/// 武器の表示座標
	/// </summary>
	constexpr Vector3 kOffset = { 30.0f,0.0f,0.0f };
	constexpr float kLerpSwing = 2.0f;
	constexpr Transform kSwingUp = {
		{0,0,0},
		{0,60 * MyMath::ToRadian,0},
		{0,0,0}
	};
	constexpr float kShowRadian = -45 * MyMath::ToRadian;
}

Sword::Sword(ObjectManager* objManager):
	GameObject(objManager)
{
	// グラフィックハンドルの読み込み
	m_graphHandle = LoadGraph(kFilePath);

	// トランスフォームの初期設定
	GetTransform().Reset();
	
	// 武器を振る際のTransformを初期化
	m_swing.Reset();

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
	m_swing.rotation.y += 2*MyMath::ToRadian;
}

void Sword::Draw()
{
	bool reverseX = false;
	Vector3 drawPos = GetTransform().position;
	if (GetTransform().rotation.y>=0) {
		drawPos += kOffset;
		reverseX = false;
	}
	else {
		drawPos -= kOffset;
		reverseX = true;
	}
	float radian = GetTransform().rotation.y+m_swing.rotation.y + (kShowRadian)*MyMath::Sign(GetTransform().rotation.y);
	DrawRotaGraph(drawPos.x, drawPos.y, 1, radian, m_graphHandle, TRUE,reverseX);
	printfDx("角度 : %f\n", GetTransform().rotation.y);
	printfDx("attack : %d\n", attack);
}

void Sword::Attack()
{
	attack = !attack;
}
