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

	//プレイヤーのアイコンの画像
	const char* const kPlayerGraphPath = ".\\Personal\\Asai\\Graph\\pointer_c.png";
	//プレイヤーのアイコンの拡大率
	constexpr float kPlayerIconScale = 0.3f;
	//プレイヤーのアイコンと角度のずれを直す
	constexpr float kOffSetRadian = MyMath::DegToRad(25);

	int worldScrren;

}

Minimap::Minimap():
	m_playerUIGrahpHandle(-1),
	m_pMap(nullptr),
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

	//画像の読み込み
	m_playerUIGrahpHandle = LoadGraph(kPlayerGraphPath);

}

void Minimap::Update()
{
}

void Minimap::Draw()
{
	//ミニマップの描画
	DrawExtendGraph(kLeftPos, kTopPos, kRightPos, kBottomPos, worldScrren, FALSE);

	//プレイヤーの位置を取得
	Vector3 playerPos = ToMinimapPos(m_pPlayer->GetTransform().position);
	//プレイヤーの描画
	DrawRotaGraph(playerPos.x, playerPos.y, kPlayerIconScale, m_pPlayer->GetTransform().rotation.z + kOffSetRadian, m_playerUIGrahpHandle, TRUE);

	for (int i = 0;i < m_pItemMgr->GetArraySize();i++) {
		//アイテムの座標を取得　ミニマップの座標に変換
		Vector3 itemPos = ToMinimapPos(m_pItemMgr->GetItemPos(i));
		//アイテムを描画
		DrawCircle(itemPos.x, itemPos.y, 2, 0xffff00, TRUE);

	}

}

void Minimap::DebugDraw()
{
}

void Minimap::End()
{

	//画像の破棄
	DeleteGraph(m_playerUIGrahpHandle);

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
