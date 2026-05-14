#include "RotateCharacter.h"
#include "RotateCharacter.h"
#include"../Player.h"
#include"../../../Utility/Game.h"
#include"../../../Utility/MyMath.h"
#include"../RadToPos.h"
#include"../../../Utility/Time.h"
#include"../../../System/InputManager.h"
#include "../../../System/SoundManager.h"
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
	/// キャラクター画像のファイルパス
	/// </summary>
	const char*const kGraphPath[kCharaMaxNum] = {
		"Resource\\pipo-charachip_otaku01.png" ,
		"Resource\\pipo-halloweenchara2016_01.png" ,
		"Resource\\pipo-xmaschara02.png"
	};
	/// <summary>
	/// 表示する際の基本の大きさ
	/// </summary>
	constexpr float kScale = 4;
	/// <summary>
	/// 遠近によって変更する描画の大きさの基準
	/// </summary>
	constexpr float kPerspective = 400;
	/// <summary>
	/// 軸の中心からの距離
	/// </summary>
	constexpr float kDistance = 300;
	/// <summary>
	/// 軸の座標
	/// </summary>
	constexpr Vector3 kAxisPos = { Game::kScreenWidth * 0.5f,Game::kScreenHeight * 0.5f,0 };
	/// <summary>
	/// 初期の角度
	/// </summary>
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
	m_axisTransform.rotation.y = kInitRadian;

	// キャ5ラそれぞれの角度の設定
	float charaRadian = 0;
	for (int i = 0; i < kCharaMaxNum; i++) {
		m_transform[i].rotation.y = charaRadian * MyMath::ToRadian;
		charaRadian += kCharaRadian;
		charaRadian = MyMath::NormalizeAngle(charaRadian);
		m_radians.push_back(m_transform[i].rotation.y);
	}
	// キャラそれぞれのアニメーションの読み込み
	int graph[kCharaMaxNum][3];
	for (int i = 0; i < kCharaMaxNum; i++) {
		LoadDivGraph(kGraphPath[i], 3, 3, 1, 32, 32, graph[i]);
		for (int j = 0; j < 3; j++) {
			m_graphHandle[i][j] = graph[i][j];
		}
	}
	m_radianNum = 0;
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
		m_radianNum++;
		SoundManager::GetInstance().PlaySe(Sound::SE::CharactorSelect);
	}
	else if (InputManager::GetInstance().IsPressed(Input::Action::Right)) {
		m_radianNum--;
		SoundManager::GetInstance().PlaySe(Sound::SE::CharactorSelect);
	}
	m_radianNum = (m_radians.size() + m_radianNum) % m_radians.size();
	m_desireRadian = m_radians[m_radianNum]+ kInitRadian;
	float lerp = m_desireRadian - m_axisTransform.rotation.y;
	lerp = MyMath::NormalizeRadian(lerp);
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
		float perspective = (kPerspective + m_transform[m_sort[i]].position.z)/ kPerspective;
		DrawRotaGraph(pos.x, pos.y, 4*perspective, 0, m_graphHandle[m_sort[i]][0], TRUE);
		//printfDx("%d番目 : %d\n", i, m_sort[i]);
		//printfDx("%d番目Z: %f\n", i, m_transform[i].position.z);
	}
}

const Character::Job RotateCharacter::GetSelectJob() const
{
	Character::Job job=Character::Job::Warrior;
	// 一番奥にいるキャラクターから順に描画するので
	// 一番手前(描画順の最後)のキャラクターが選択キャラになる
	job = static_cast<Character::Job>(m_sort[kCharaMaxNum - 1]);
	return job;
}
