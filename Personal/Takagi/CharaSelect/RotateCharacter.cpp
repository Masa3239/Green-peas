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
	constexpr float kInitRadian=DX_PI_F/2;
}
RotateCharacter::RotateCharacter():
	m_graphHandle(),
	m_animFrame(),
	m_transform(),
	m_axisTransform(),
	m_desireRadian(0),
	m_sort(),
	m_radians(),
	m_radianNum(0)
{
	// 変数の初期化
	for (int i = 0; i < kCharaMaxNum; i++) {
		for (int j = 0; j < kGraphNum; j++) {
			// グラフィックハンドルの初期化
			m_graphHandle[i][j] = -1;
			m_graphHandle[i][j] = -1;
			m_graphHandle[i][j] = -1;
		}
		// フレーム数のリセット
		m_animFrame[i] = 0;
		// キャラ描画時のトランスフォームの初期化
		m_transform[i].Reset();
	}
	// 軸のトランスフォームのリセット
	m_axisTransform.Reset();
	// 軸の座標を設定
	m_axisTransform.position = kAxisPos;

	// キャラそれぞれの角度の設定
	float charaRadian = 0;
	// キャラごとの初期設定
	for (int i = 0; i < kCharaMaxNum; i++) {
		// キャラの描画位置が等間隔になるように角度の設定を行う
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
	// フレーム間の時間をキャッシュ
	float time = Time::GetInstance().GetDeltaTime();
	// 左を押したら
	if (InputManager::GetInstance().IsPressed(Input::Action::Left)) {
		// 角度を変更
		m_radianNum++;
		// サウンドを再生
		SoundManager::GetInstance().PlaySe(Sound::SE::CharactorSelect);
	}
	// 右を押したら
	else if (InputManager::GetInstance().IsPressed(Input::Action::Right)) {
		// 角度を変更
		m_radianNum--;
		// サウンドを再生
		SoundManager::GetInstance().PlaySe(Sound::SE::CharactorSelect);
	}
	// 角度が循環するように
	m_radianNum = (m_radians.size() + m_radianNum) % m_radians.size();
	// 選択しているキャラに角度が合うようにする
	m_desireRadian = m_radians[m_radianNum]+ kInitRadian;
	// 角度を補完する
	float lerp = m_desireRadian - m_axisTransform.rotation.y;
	lerp = MyMath::NormalizeRadian(lerp);
	// 補間の量が1を超えないようにする
	lerp *= MyMath::Clamp(time * 10, 0.0f, 1.0f);
	// 角度を少しずつ動かす
	m_axisTransform.rotation.y += lerp;

	// 角度に応じてキャラクター画像の描画位置を動かす
	float radian = 0;
	for (int i = 0; i < kCharaMaxNum; i++) {
		radian = m_transform[i].rotation.y + m_axisTransform.rotation.y;
		m_transform[i].position = RadToPos(radian, kDistance);
		m_transform[i].position.z = m_transform[i].position.y;
		m_transform[i].position.y = 0;
	}
}

void RotateCharacter::Draw()
{
	// キャラクターのZ座標を格納するローカル変数
	float sortPosZ[kCharaMaxNum];
	for (int i = 0; i < kCharaMaxNum; i++) {
		m_sort[i] = i;
		sortPosZ[i] = m_transform[i].position.z;
	}

	// 奥から順番に描画できるように入れ替える
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


	// キャラクターの描画座標を格納するローカル変数
	Vector3 pos = { 0.0f,0.0f,0.0f };
	// キャラクターの数だけ繰り返す
	for (int i = 0; i < kCharaMaxNum; i++) {
		// キャラクターの描画座標を格納
		pos = m_transform[m_sort[i]].position + kAxisPos;
		// 遠近に応じた拡大率を求める
		float perspective = (kPerspective + m_transform[m_sort[i]].position.z)/ kPerspective;
		// キャラクター画像の描画をする
		DrawRotaGraph(pos.x, pos.y, kScale *perspective, 0, m_graphHandle[m_sort[i]][0], TRUE);
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
