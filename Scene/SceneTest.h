#pragma once
#include "SceneBase.h"
#include <DxLib.h>

// スマートポインタを使用するためにインクルード
#include <memory>

// スマートポインタについて
// 今までのポインタ（生ポインタ）は手動でnew、deleteを行っていた
// スマートポインタはメモリ管理を安全に楽にしてくれるもの 置き換えられるものは置き換え推奨
// スマートポインタは3種類存在する
//	unique_ptr	ユニークポインタ
//	shared_ptr	シェアードポインタ
//	weak_ptr	ウィークポインタ
// ここではユニークポインタを扱っていく
// unique_ptrは、所有権を一つしか持たず、自動で破棄してくれるポインタのことをいう

// 前方宣言
class GameSetting;
//class GrassManager;

namespace Collision
{
	class AABB;
}

/// <summary>
/// 授業で作成して確認用のクラス
/// なにか機能の確認を行うときにこのクラスで検証をする
/// </summary>
class SceneTest : public SceneBase
{
public:

	/// <summary>
	/// SceneTest画面のコンストラクタ
	/// メンバの初期設定を行う
	/// </summary>
	SceneTest();

	/// <summary>
	/// SceneTest画面のデストラクタ
	/// メンバの後処理を行う
	/// </summary>
	virtual ~SceneTest();

	/// <summary>
	/// 画面の初期設定を行う
	/// </summary>
	void Init();

	/// <summary>
	/// 画面の後処理を行う
	/// </summary>
	void End();

	/// <summary>
	/// SceneTest画面の処理を行う
	/// </summary>
	/// <returns>SceneBase型のポインタ 次に処理をする画面</returns>
	SceneBase* Update();

	/// <summary>
	/// SceneTest画面の描画を行う
	/// </summary>
	void Draw();

private:

	/// <summary>
	/// 位置関係が分かるように地面を線で描画する
	/// </summary>
	void DrawGround();

private:

	/*
	/// <summary>
	/// Playerクラスのポインタ
	/// </summary>
	Player* m_pPlayer;

	/// <summary>
	/// Cameraクラスのポインタ
	/// </summary>
	Camera* m_pCamera;

	/// <summary>
	/// Grassクラスのポインタ
	/// </summary>
	GrassManagerV* m_pGrassMgr;
	*/

	// スマートポインタのunique_ptrの宣言方法
	// std::unique_ptr<クラス名> スマートポインタ名;

	std::unique_ptr<Collision::AABB> m_pBox;

	/// <summary>
	/// 当たっているかどうか
	/// </summary>
	bool m_isHit;

};
