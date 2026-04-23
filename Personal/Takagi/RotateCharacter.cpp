#include "RotateCharacter.h"
#include "RotateCharacter.h"
#include"Player.h"
#include"../../Utility/Game.h"
#include"../../Utility/MyMath.h"
#include"RadToPos.h"
#include"../../Utility/Time.h"
#include"../../System/InputManager.h"
namespace {
	/// <summary>
	/// キャラクターの職業の最大数(キャストするのがめんどくさいため用意)
	/// </summary>
	constexpr int kCharaMaxNum = static_cast<int>(Character::Job::Max);
	/// <summary>
	/// キャラクターを配置する角度
	/// </summary>
	constexpr float kCharaRadian = 360 / kCharaMaxNum;
	/// <summary>
	/// キャラクターのファイルパス
	/// </summary>
	const char*const kGraphPath[kCharaMaxNum] = {
		"Resource\\pipo-charachip_otaku01.png" ,
		"Resource\\pipo-halloweenchara2016_01.png" ,
		"Resource\\pipo-xmaschara02.png"
	};
	constexpr float kScale = 6;
	constexpr float kPers = 400;
	constexpr float kDistance = 300;
	constexpr Vector3 kAxisPos= { Game::kScreenWidth * 0.5f,Game::kScreenHeight * 0.5f,0 };
	constexpr float kInitRadian=90*MyMath::ToRadian;
}
RotateCharacter::RotateCharacter():
	m_graphHandle(),
	m_animFrame(),
	m_transform(),
	m_axisTransform(),
	m_desireRadian(kInitRadian)
{
	// 変数の初期化
	for (int i = 0; i < kCharaMaxNum; i++) {
		for (int j = 0; j < kGraphNum; j++) {
			m_graphHandle[i][j] = -1;
			m_graphHandle[i][j] = -1;
			m_graphHandle[i][j] = -1;
		}
		m_animFrame[i] = 0;
		m_transform[i].Reset();
	}
	m_axisTransform.Reset();
	// 軸の座標を設定
	m_axisTransform.position = kAxisPos;

	// キャラそれぞれの角度の設定
	float charaRadian = 0;
	for (int i = 0; i < kCharaMaxNum; i++) {
		m_transform[i].rotation.y = charaRadian * MyMath::ToRadian;
		charaRadian += kCharaRadian;
		charaRadian = MyMath::NormalizeAngle(charaRadian);
	}
	// キャラそれぞれのアニメーションの読み込み
	int graph[kCharaMaxNum][3];
	for (int i = 0; i < kCharaMaxNum; i++) {
		LoadDivGraph(kGraphPath[i], 3, 3, 1, 32, 32, graph[i]);
		for (int j = 0; j < 3; j++) {
			m_graphHandle[i][j] = graph[i][j];
		}
	}
}

RotateCharacter::~RotateCharacter()
{
}

void RotateCharacter::Init()
{
}

void RotateCharacter::End()
{
}

void RotateCharacter::Update()
{

	float time = Time::GetInstance().GetDeltaTime();
	if (InputManager::GetInstance().IsPressed(Input::Action::Left)) {
		m_desireRadian += kCharaRadian * MyMath::ToRadian;
	}
	else if (InputManager::GetInstance().IsPressed(Input::Action::Right)) {
		m_desireRadian -= kCharaRadian * MyMath::ToRadian;
	}
	m_desireRadian = MyMath::NormalizeAngle(m_desireRadian);
	float lerp = m_desireRadian - m_axisTransform.rotation.y;
	lerp *= time * 10;
	m_axisTransform.rotation.y += lerp;
	float radian = 0;
	for (int i = 0; i < kCharaMaxNum; i++) {
		radian = m_transform[i].rotation.y + m_axisTransform.rotation.y;
		m_transform[i].position = RadToPos(radian, kDistance);
		m_transform[i].position.z = m_transform[i].position.y;
		m_transform[i].position.y = 0;
	}
	//m_axisTransform.rotation.y += 45 * MyMath::ToRadian * time;
}

void RotateCharacter::Draw()
{
	float sortPosZ[kCharaMaxNum];
	for (int i = 0; i < kCharaMaxNum; i++) {
		m_sort[i] = i;
		sortPosZ[i] = m_transform[i].position.z;
	}

	for (int i = 0; i < kCharaMaxNum; i++) {
		for (int j = 0; j < kCharaMaxNum-1; j++) {
			if (sortPosZ[j] <= sortPosZ[j + 1])continue;
			float bufPosZ = sortPosZ[j];
			sortPosZ[j] = sortPosZ[j + 1];
			sortPosZ[j + 1] = bufPosZ;

			int buf = m_sort[j];
			m_sort[j] = m_sort[j + 1];
			m_sort[j + 1] = buf;
		}
	}



	Vector3 pos;
	for (int i = 0; i < kCharaMaxNum; i++) {
		pos = m_transform[m_sort[i]].position + kAxisPos;
		float pers = (kPers + m_transform[m_sort[i]].position.z)/ kPers;
		DrawRotaGraph(pos.x, pos.y, 4*pers, 0, m_graphHandle[m_sort[i]][0], TRUE);
		printfDx("%d番目 : %d\n", i, m_sort[i]);
		printfDx("%d番目Z: %f\n", i, m_transform[i].position.z);
	}
	for (int i = 0; i < kCharaMaxNum; i++) {
		pos = m_transform[i].position + kAxisPos;

		DrawCircle(pos.x, pos.y, 10, 0xff0000);
	}
}

const Character::Job RotateCharacter::GetSelectJob() const
{
	Character::Job job=Character::Job::Warrior;
	job = static_cast<Character::Job>(m_sort[kCharaMaxNum - 1]);
	return job;
}
