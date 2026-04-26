#include "Clear.h"
#include"../../../Utility/Game.h"
#include"../../../Utility/Time.h"
#include<DxLib.h>

namespace {
	// スクリーンの中心座標
	constexpr Vector3 kScreenHalf = { Game::kScreenWidth * 0.5f,Game::kScreenHeight * 0.5f,0 };
	// 画像の大きさが1となるZ座標
	constexpr float kDefaoultPosZ = 100;
	// 描画の初期座標
	Vector3 kAcrossInitPos = { Game::kScreenWidth +1200,kScreenHalf.y,kDefaoultPosZ*2 };
	Vector3 kAcrossEndPos = {  -1200,kScreenHalf.y,200 };
	Vector3 kFallInitPos = { kScreenHalf.x,Game::kScreenWidth + 400,kDefaoultPosZ*2 };
	Vector3 kFallEndPos = { kScreenHalf.x,kScreenHalf.y -200,kDefaoultPosZ*2 };
	// 画像のファイルパス
	const char* const kGraphPath = "Resource\\Result\\Clear!!.png";
	constexpr float kMinPosZ = 20;
	constexpr float kBounce = -0.2f;
	constexpr Vector3 kPassSpeed = { -20,0,0 };
	constexpr Vector3 kScaleSpeed = { 0,-10,-5 };
}

Clear::Clear():
	m_speed({0,0,0}),
	m_phase(Across)
{
	m_graphHandle = LoadGraph(kGraphPath);
	m_transform.position = kAcrossInitPos;
}

Clear::~Clear()
{
	DeleteGraph(m_graphHandle);
}

void Clear::Init()
{
}

void Clear::End()
{
}

void Clear::Update()
{
	float time = Time::GetInstance().GetUnscaledDeltaTime();
	if (m_phase == Across) {
		m_speed += kPassSpeed * time;
		if (m_transform.position.x < kAcrossEndPos.x) {
			m_transform.position = kFallInitPos;
			m_phase = Fall;
			m_speed = { 0,0,5 };
		}
	}
	if (m_phase == Fall) {
		m_speed += kScaleSpeed * time;
		if (m_speed.z < 0 && m_transform.position.z < kMinPosZ) {
			m_speed.z *= kBounce;
			m_transform.position.z = kMinPosZ;
		}
		if (m_transform.position.y < kFallEndPos.y) {
			m_transform.position.y = kFallEndPos.y;
			m_speed.y = 0;
		}
	}
	m_transform.position += m_speed;
}

void Clear::Draw()
{

	float scale = m_transform.position.z / kDefaoultPosZ;
	scale = MyMath::Clamp(scale, 0.1f, scale);
	DrawRotaGraph(m_transform.position.x, m_transform.position.y, scale, 0, m_graphHandle, TRUE);
}
