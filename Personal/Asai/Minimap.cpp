#include "Minimap.h"

#include<DxLib.h>

#include"../../Utility/Game.h"
#include"../../Utility/Color.h"
#include"../Asai/Camera.h"

#include"../Kimura/Map/Map.h"
#include"../Kimura/Map/MapManager.h"
#include"../Osawa/Enemy/EnemyManager.h"
#include"../Syoguti/ItemManager.h"
#include"../Takagi/Player.h"

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
	constexpr float kOffSetRadian = MyMath::DegToRad(115);

}

Minimap::Minimap():
	m_playerUIGrahpHandle(-1),
	m_worldScrren(-1),
	m_mapSizeX(0),
	m_mapSizeY(0),
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

	//画像の読み込み
	m_playerUIGrahpHandle = LoadGraph(kPlayerGraphPath);

	if (!m_pCamera)return;
	m_worldScrren = m_pCamera->GetWorldScreen();

}

void Minimap::Update()
{
}

void Minimap::Draw()
{
	//ミニマップ描画
	DrawMiniMap();
	//プレイヤー描画
	DrawPlayer();
	//アイテム描画
	DrawItem();
	//敵を描画
	DrawEnemy();

}

void Minimap::DebugDraw()
{
}

void Minimap::End()
{

	//画像の破棄
	DeleteGraph(m_playerUIGrahpHandle);

}

void Minimap::GenerateMinimap(Camera* pCamera, Map* pMap)
{

	m_pCamera = pCamera;
	m_pMap = pMap;

	m_worldScrren = m_pCamera->GetWorldScreen();

	m_mapSizeX = m_pMap->GetMapBlockNumX() * kMapBlockSize;
	m_mapSizeY = m_pMap->GetMapBlockNumY() * kMapBlockSize;

}

void Minimap::DrawMiniMap()
{

	//ミニマップの描画
	DrawExtendGraph(kLeftPos, kTopPos, kRightPos, kBottomPos, m_worldScrren, FALSE);

}

void Minimap::DrawPlayer()
{

	if (!m_pPlayer)return;

	//プレイヤーの位置を取得
	Vector3 playerPos = ToMinimapPos(m_pPlayer->GetTransform().position);
	//プレイヤーの描画
	DrawRotaGraph(playerPos.x, playerPos.y, kPlayerIconScale, m_pPlayer->GetTransform().rotation.z + kOffSetRadian, m_playerUIGrahpHandle, TRUE);

}

void Minimap::DrawItem()
{

	if (!m_pItemMgr)return;

	//全てのアイテムを描画
	for (int i = 0;i < m_pItemMgr->GetArraySize();i++) {
		//アイテムの座標を取得　ミニマップの座標に変換
		Vector3 itemPos = ToMinimapPos(m_pItemMgr->GetItemPos(i));
		//アイテムを描画
		DrawCircle(itemPos.x, itemPos.y, 1.5f, Color::kYellow, TRUE);

	}

}

void Minimap::DrawEnemy()
{

	if (!m_pEnemyMgr)return;

	//全ての中ボスを描画
	for (auto miniBoss : m_pEnemyMgr->GetMiniBossPositions()) {
		//中ボスの座標をミニマップ座標に変換
		miniBoss = ToMinimapPos(miniBoss);
		//中ボスを描画
		DrawCircle(miniBoss.x, miniBoss.y, 2, Color::kRed, TRUE);

	}

}

Vector3 Minimap::ToMinimapPos(const Vector3 pos)
{

	Vector3 vector;

	float rateX = MyMath::Rate(pos.x, m_mapSizeX);
	float rateY = MyMath::Rate(pos.y, m_mapSizeY);

	vector.x = kLeftPos + (kSizeX * rateX);
	vector.y = kTopPos + (kSizeY * rateY);

	return vector;

}
