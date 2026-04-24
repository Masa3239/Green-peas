#pragma once
#include"Player.h"
#include"../../Utility/Transform.h"
namespace {
	constexpr int kGraphNum = 8;
}

/// <summary>
/// キャラクターを軸に合わせて回転運動させる
/// </summary>
class RotateCharacter
{
public:
	RotateCharacter();
	~RotateCharacter();
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();
	/// <summary>
	/// 終了処理
	/// </summary>
	void End();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 選択中のキャラクターを調べる関数
	/// </summary>
	const Character::Job GetSelectJob()const;
private:
	/// <summary>
	/// キャラクターのグラフィックハンドル
	/// </summary>
	int m_graphHandle[static_cast<int>(Character::Job::Max)][kGraphNum];
	/// <summary>
	/// アニメーションのフレーム
	/// </summary>
	float m_animFrame[static_cast<int>(Character::Job::Max)];
	/// <summary>
	/// キャラクターそれぞれのトランスフォーム
	/// </summary>
	Transform m_transform[static_cast<int>(Character::Job::Max)];
	/// <summary>
	/// 中心軸のトランスフォーム
	/// </summary>
	Transform m_axisTransform;
	/// <summary>
	/// 補間するためのラジアン角
	/// </summary>
	float m_desireRadian;
	/// <summary>
	/// 並べ替えの順番
	/// </summary>
	int m_sort[static_cast<int>(Character::Job::Max)];
};

