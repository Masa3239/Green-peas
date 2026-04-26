#include "Clear.h"
#include"../../../Utility/Game.h"
#include"../../../Utility/Time.h"
#include<DxLib.h>
#include"../../../System/InputManager.h"

namespace {
	// スクリーンの中心座標
	constexpr Vector3 kScreenHalf = { Game::kScreenWidth * 0.5f,Game::kScreenHeight * 0.5f,0 };
	// 画像の大きさが1となるZ座標
	constexpr float kDefaoultPosZ = 100;
	// 描画の初期座標
	constexpr Vector3 kAcrossInitPos = { Game::kScreenWidth +1200,kScreenHalf.y,kDefaoultPosZ*2 };
	constexpr Vector3 kAcrossEndPos = {  -1200,kScreenHalf.y,200 };
	constexpr Vector3 kNarrowInitPos = { kScreenHalf.x,Game::kScreenWidth + 400,kDefaoultPosZ*2 };
	constexpr Vector3 kNarrowEndPos = { kScreenHalf.x,kScreenHalf.y -200,kDefaoultPosZ*0.2f };
	// 画像のファイルパス
	const char* const kGraphPath = "Resource\\Result\\Clear!!.png";
	constexpr float kBounce = -0.2f;
	constexpr Vector3 kPassSpeed = { -40,0,0 };
	constexpr Vector3 kScaleSpeed = { 0,-10,-5 };
}

Clear::Clear():
	m_speed({0,0,0}),
	m_phase(Across)
{
	m_graphHandle = LoadGraph(kGraphPath);
	m_transform.position = kAcrossInitPos;
	m_isFinish = false;
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
	bool skip = InputManager::GetInstance().IsPressed(Input::Action::Confirm);
	if (skip) {
		m_phase = Narrow;
		m_transform.position = kNarrowEndPos;
		m_speed = {0,0,0};
		m_isFinish = true;
		return;
	}
	float time = Time::GetInstance().GetUnscaledDeltaTime();
	if (m_phase == Across) {
		m_speed += kPassSpeed * time;
		if (m_transform.position.x < kAcrossEndPos.x) {
			m_transform.position = kNarrowInitPos;
			m_phase = Narrow;
			m_speed = { 0,0,5 };
		}
	}
	if (m_phase == Narrow) {
		m_speed += kScaleSpeed * time;
		if (m_speed.z < 0 && m_transform.position.z < kNarrowEndPos.z) {
			m_speed.z *= kBounce;
			m_transform.position.z = kNarrowEndPos.z;
			if (m_speed.z > 0.02f)
				m_speed.z = 0;
		}
		if (m_transform.position.y < kNarrowEndPos.y) {
			m_transform.position.y = kNarrowEndPos.y;
			m_speed.y = 0;
		}
	}
	m_transform.position += m_speed;
	if (m_transform.position != kNarrowEndPos)return;
	if (m_speed.x!=0|| m_speed.y != 0|| m_speed.z != 0)return;
	m_isFinish = true;
}

void Clear::Draw()
{

	float scale = m_transform.position.z / kDefaoultPosZ;
	scale = MyMath::Clamp(scale, 0.1f, scale);
	DrawRotaGraph(m_transform.position.x, m_transform.position.y, scale, 0, m_graphHandle, TRUE);
}
