#include "Minimap.h"

#include<DxLib.h>

#include"../../Utility/Game.h"
#include"../Asai/Camera.h"

#include"../Takagi/Player.h"
#include"../Syoguti/ItemManager.h"

namespace {
	//ミニマップのサイズ
	constexpr int kSizeX = 100;
	constexpr int kSizeY = 100;
	//画面端からずらす大きさ
	constexpr int kOffSet = 15;

	//ミニマップの位置
	constexpr int kLeftPos = Game::kScreenWidth - kSizeX - kOffSet;
	constexpr int kRightPos = Game::kScreenWidth - kOffSet;
	constexpr int kTopPos = 0 + kOffSet;
	constexpr int kBottomPos = 0 + kSizeY + kOffSet;

	const char* const kPlayerGraphPath = ".\\Personal\\Asai\\Graph\\pointer_c.png";

	constexpr float kOffSetRadian = MyMath::DegToRad(25);

	int worldScrren;

}

Minimap::Minimap():
	m_playerUIGrahpHandle(-1),
	m_pPlayer(nullptr),
	m_pCamera(nullptr),
	m_pEnemyMgr(nullptr),
	m_pItemMgr(nullptr)
{
}

Minimap::~Minimap()
{
}

void Minimap::Init()
{
	worldScrren = m_pCamera->GetWorldScreen();

	m_playerUIGrahpHandle = LoadGraph(kPlayerGraphPath);

}

void Minimap::Update()
{
}

void Minimap::Draw()
{
	//ミニマップの描画
	DrawExtendGraph(kLeftPos, kTopPos, kRightPos, kBottomPos, worldScrren, FALSE);

	Vector3 playerPos = ToMinimapPos(m_pPlayer->GetTransform().position);
	//DrawCircle(playerPos.x, playerPos.y, 5.0f, 0xffffff, TRUE);

	DrawRotaGraph(playerPos.x, playerPos.y, 0.3f, m_pPlayer->GetTransform().rotation.z+kOffSetRadian, m_playerUIGrahpHandle, TRUE);

	for (int i = 0;i < m_pItemMgr->GetArraySize();i++) {

		Vector3 itemPos = ToMinimapPos(m_pItemMgr->GetItemPos(i));

		DrawCircle(itemPos.x, itemPos.y, 5, 0xffff00, TRUE);

		printfDx("%f\n", m_pItemMgr->GetItemPos(i).x);
		printfDx("%d\n", i);
	}

	printfDx("%d\n", m_pItemMgr->GetArraySize());

}

void Minimap::DebugDraw()
{
}

void Minimap::End()
{
}

Vector3 Minimap::ToMinimapPos(const Vector3 pos)
{

	Vector3 vector;

	float rateX = MyMath::Rate(pos.x, 10000);
	float rateY = MyMath::Rate(pos.y, 10000);

	vector.x = kLeftPos + (kSizeX * rateX);
	vector.y = kTopPos + (kSizeY * rateY);

	return vector;

}
