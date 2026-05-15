#include "BackBoard.h"
#include"../../../Utility/Transform.h"
#include"../../../Utility/Vector3.h"
#include"../../../Utility/Game.h"
#include"../../../Utility/Time.h"
#include<math.h>
#include<DxLib.h>
#include"../../../System/InputManager.h"
#include "../../../System/SoundManager.h"

namespace {
	// スクリーンの中心の座標
	constexpr Vector3 kScreenHalf = { Game::kScreenWidth * 0.5f,Game::kScreenHeight * 0.5f,0 };
	// 2点間のX座標の距離
	constexpr float kDistance = 320;
	// 左側の座標の初期座標
	constexpr Vector3 kAcrossInitPos[BackBoard::Max] = {
		{ kScreenHalf.x - kDistance,-300,0 },
		{ kScreenHalf.x + kDistance,-300,0 },
	};
	// バウンドする量
	constexpr float kBounce = -0.3f;
	// バウンドを終了させる量
	constexpr float kFinishValue = -0.2f;
	// 落下速度
	constexpr float kFallSpeed = 10.0f;
	// 背景の画像のファイルパス
	const char* const kGraphPath = "Resource\\Result\\BackBoard.png";
	// 落下開始の時間
	constexpr float kFallStart[BackBoard::Max] = { 0.0f,0.1f };

}

BackBoard::BackBoard():
	m_backBoardHandle(-1),
	m_sidePos(),
	m_fallSpeed(),
	m_between()
{
	// グラフィックハンドルの読み込み
	m_backBoardHandle = LoadGraph(kGraphPath);
	// 角度を求めるための2点の座標,落下開始時間を初期化
	for (int i = 0; i < Max;i++) {
		m_sidePos[i] = kAcrossInitPos[i];	// 座標の初期化	
		m_fallStart[i] = kFallStart[i];		// 落下開始時の時刻
	}
	// 落下速度を初期化
	for (float& speed : m_fallSpeed) {
		speed = 0;
	}

	// 背景の描画トランスフォームの初期化
	m_between.Reset();
}

BackBoard::~BackBoard()
{
	// グラフィックハンドルの破棄
	DeleteGraph(m_backBoardHandle);
}

void BackBoard::Init()
{
	// 背景の描画座標の初期化
	m_between.position = (m_sidePos[Left] + m_sidePos[Right]) * 0.5;
}

void BackBoard::End()
{
}

void BackBoard::Update()
{
	// スキップ判定を調べる
	CheckSkip();

	// フレーム間の経過時間をキャッシュ
	float time = Time::GetInstance().GetUnscaledDeltaTime();
	// 落下開始時間の更新処理
	for (int i = 0;i < Max;i++) {
		// 落下開始までの時間をカウントダウン
		m_fallStart[i] -= time;
		// 落下開始時間の下限を0で固定
		MyMath::Clamp(m_fallStart[i], 0.0f, m_fallStart[i]);
	}
	// 両方の座標の更新処理
	for (int i = 0; i < Max; i++) {
		// 落下開始時間が0でなければ落下してはいけない
		if (m_fallStart[i])continue;
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
	// 背景の座標を2点間の中心として更新
	m_between.position = (m_sidePos[Left] + m_sidePos[Right]) * 0.5;
	Vector3 vec = m_sidePos[Right] - m_sidePos[Left];
	// 背景の描画角度を2点間の角度として更新
	m_between.rotation.z = atan2(vec.y, vec.x);
}

void BackBoard::Draw()
{
	// 背景の描画
	DrawRotaGraph(m_between.position.x, m_between.position.y, 3, m_between.rotation.z, m_backBoardHandle, TRUE);
}

bool BackBoard::IsFinish()
{
	// 左右どちらかでも落下・バウンド中なら演出が終了していない判定
	if(m_sidePos[Left].y != kScreenHalf.y)return false;
	if(m_sidePos[Right].y != kScreenHalf.y)return false;

	// どちらも落下・バウンドが終了していたら演出が終了している判定
	return true;
}

bool BackBoard::CheckSkip()
{
	// 演出のスキップができるように
	bool skip = InputManager::GetInstance().IsPressed(Input::Action::Confirm);
	// 入力が行われたら
	if (skip) {
		// 2点の座標を固定
		for (int i = 0; i < Max; i++) {
			m_sidePos[i].y = kScreenHalf.y;
			m_fallSpeed[i] = 0;
		}
	}
	// 入力がされたかどうかを返す
	return skip;
}
