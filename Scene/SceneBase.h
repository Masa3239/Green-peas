#pragma once

#include <memory>
#include "CarryOver.h"

class ObjectManager;
class Fader;

/// <summary>
/// 各画面の基本クラス
/// 基本的にはこのクラスを継承して各画面のクラスを作成する
/// 作成したクラスをSceneManagerクラスから呼び出すことで保守しやすくする
/// </summary>
class SceneBase {

public:

	/// <summary>
	/// コンストラクタ
	/// メンバ変数の初期設定
	/// </summary>
	SceneBase();

	/// <summary>
	/// デストラクタ
	/// 派生クラスを破棄した時に備えて仮想デストラクタ化
	/// </summary>
	virtual ~SceneBase();

	/// <summary>
	/// 初期設定
	/// 具体的な処理は各画面毎で異なるので純粋仮想関数にして派生先で実装
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 終了処理
	/// 具体的な処理は各画面毎で異なるので純粋仮想関数にして派生先で実装
	/// </summary>
	virtual void End() = 0;

	/// <summary>
	/// シーンベースの更新処理
	/// </summary>
	SceneBase* UpdateBase();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <returns>自身のポインタを返す</returns>
	virtual SceneBase* Update() { return this; }

	/// <summary>
	/// シーンベースの描画処理
	/// </summary>
	void DrawBase();

	/// <summary>
	/// 描画処理
	/// 具体的な処理は各画面毎で異なるので純粋仮想関数にして派生先で実装
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// 描画前の処理
	/// </summary>
	virtual void PreDraw() {};
	/// <summary>
	/// 描画後の処理
	/// </summary>
	virtual void PostDraw() {};
	
	/// <summary>
	/// 持ち越しする変数を取得する関数
	/// </summary>
	CarryOver& GetCarryOver() { return m_carryOver; }

	/// <summary>
	/// オブジェクトマネージャーのポインタを取得する
	/// </summary>
	ObjectManager* GetObjectManager() const { return m_objManager.get(); }

	/// <summary>
	/// フェーダーのゲッター
	/// </summary>
	/// <returns>フェーダーのポインタ</returns>
	Fader* GetFader() const { return m_fader.get(); }

	/// <summary>
	/// 次のシーンのセッター
	/// </summary>
	/// <param name="next">次のシーンのポインタ</param>
	void SetNextScene(SceneBase* next) { m_nextScene = next; }

protected:

	CarryOver m_carryOver;

private:

	std::unique_ptr<ObjectManager> m_objManager;

	std::unique_ptr<Fader> m_fader;

	SceneBase* m_nextScene;
};
