#include "BackBoard.h"
#include"../../../Utility/Transform.h"
#include"../../../Utility/Vector3.h"
#include"../../../Utility/Game.h"
#include"../../../Utility/Time.h"
#include<math.h>
#include<DxLib.h>
namespace {
	constexpr Vector3 kScreenHalf = { Game::kScreenWidth * 0.5f,Game::kScreenHeight * 0.5f,0 };
	// 2点間のX座標の距離
	constexpr float kDistance = 200;
	// 左側の座標の初期座標
	constexpr Vector3 kAcrossInitPos[BackBoard::Max] = {
		{ kScreenHalf.x - kDistance,-300,0 },
		{ kScreenHalf.x + kDistance,-350,0 },
	};
	// バウンドする量
	constexpr float kBounce = -0.3f;
	// バウンドを終了させる量
	constexpr float kFinishValue = -0.2f;
	// 落下速度
	constexpr float kFallSpeed = 10.0f;
	const char* const kGraphPath = "Resource\\BuffSelect\\START.png";
}

BackBoard::BackBoard():
	m_backBoardHandle(-1),
	m_sidePos(),
	m_fallSpeed(),
	m_between()
{
	// グラフィックハンドルの読み込み
	m_backBoardHandle = LoadGraph(kGraphPath);
	for (int i = 0; i < Max;i++) {
		m_sidePos[i] = kAcrossInitPos[i];
	}
	for (float& speed : m_fallSpeed) {
		speed = 0;
	}
	m_between.Reset();
}

BackBoard::~BackBoard()
{
	DeleteGraph(m_backBoardHandle);
}

void BackBoard::Init()
{
	for (int i = 0; i < Max; i++) {
		m_sidePos[i] = kAcrossInitPos[i];
	}
	for (float& speed : m_fallSpeed) {
		speed = 0;
	}
	m_between.Reset();
	m_between.position = (m_sidePos[Left] + m_sidePos[Right]) * 0.5;
}

void BackBoard::End()
{
}

void BackBoard::Update()
{
	// フレーム間の経過時間をキャッシュ
	float time = Time::GetInstance().GetUnscaledDeltaTime();
	// 両方の座標の更新処理
	for (int i = 0; i < Max; i++) {
		// 落下速度を更新
		m_fallSpeed[i] += kFallSpeed * time;
		// 座標に落下速度を加算
		m_sidePos[i].y += m_fallSpeed[i];
		
		
		if (m_fallSpeed[i] <= 0 || m_sidePos[i].y <= kScreenHalf.y)continue;
		// 落下速度が下方向かつ座標が一定を下回ったらバウンドさせる
		m_fallSpeed[i] *= kBounce;
		
		
		if (m_fallSpeed[i] < kFinishValue)continue;
		// バウンドした瞬間 上方向の力の量が一定より小さいとき
		// 落下速度をなくす
		m_fallSpeed[i] = 0;
		// 座標を固定する
		m_sidePos[i].y = kScreenHalf.y;
	}
	m_between.position = (m_sidePos[Left] + m_sidePos[Right]) * 0.5;
	Vector3 vec = m_sidePos[Right] - m_sidePos[Left];
	m_between.rotation.z = atan2(vec.y, vec.x);
}

void BackBoard::Draw()
{
	DrawRotaGraph(m_between.position.x, m_between.position.y, 1, m_between.rotation.z, m_backBoardHandle, TRUE);
	for (int i = 0; i < Max; i++) {
		DrawCircle(m_sidePos[i].x, m_sidePos[i].y, 10, 0x00ff00);
	}
	DrawCircle(m_between.position.x, m_between.position.y, 10, 0x0000ff);
}

bool BackBoard::IsEnd()
{
	if(m_sidePos[Left].y != kScreenHalf.y)return false;
	if(m_sidePos[Right].y != kScreenHalf.y)return false;

	return true;
}
