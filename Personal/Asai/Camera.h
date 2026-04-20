#pragma once
#include"../Utility/Transform.h"

class Map;

namespace CameraState {

	enum class Type {

		Follow,
		Damage,
		Anger,

	};

}

class Camera
{

public:

	Camera();
	~Camera();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="cameraPos">カメラの位置を設定する</param>
	void Update(Transform cameraPos);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// デバックの描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	/// <summary>
	/// カメラのダメージ挙動開始
	/// </summary>
	/// <param name="shakeDuration">振動時間　デフォルトは1秒</param>
	void StartDamage(float shakeDuration = 1.0f);

	/// <summary>
	/// 追従状態に変更
	/// </summary>
	void ChangeFollow() { m_state = CameraState::Type::Follow; }

	/// <summary>
	/// 怒り状態のカメラに変更
	/// </summary>
	void ChangeAnger() { m_state = CameraState::Type::Anger; }

	/// <summary>
	/// ワールドスクリーンを生成する
	void GenerateWorldScreen();

	/// <summary>
	/// ワールドスクリーンを取得する
	/// </summary>
	/// <returns></returns>
	int GetWorldScreen()const { return m_worldScreen; }

	/// <summary>
	/// マップのポインターをセットする
	/// </summary>
	/// <param name="pMap"></param>
	void SetMap(Map* pMap) { m_pMap = pMap; }

private:

	/// <summary>
	/// 線形補間
	/// </summary>
	/// <param name="cameraPos"></param>
	void Lerp(Transform cameraPos);

	/// <summary>
	/// カメラの追従
	/// </summary>
	/// <param name="cameraPos">カメラの位置を設定する</param>
	void UpdateFollow(Transform cameraPos);

	/// <summary>
	/// カメラのダメージ演出
	/// </summary>
	/// <param name="cameraPos">カメラの位置を設定する</param>
	void UpdateDamage(Transform cameraPos);

	/// <summary>
	/// 怒り状態のカメラの更新処理
	/// </summary>
	/// <param name="cameraPos">カメラの位置を設定する</param>
	void UpdateAnger(Transform cameraPos);

	/// <summary>
	/// ワールドスクリーンの外を描画しないようにする
	/// </summary>
	void KeepInWorldScreen();

private:

	/// <summary>
	/// カメラのステータス
	/// </summary>
	CameraState::Type m_state;

	/// <summary>
	/// カメラの座標に使う
	/// </summary>
	Transform m_transform;

	/// <summary>
	/// ワールドスクリーン
	/// </summary>
	int m_worldScreen;

	/// <summary>
	/// マップのポインター
	/// </summary>
	Map* m_pMap;

	/// <summary>
	/// 振動の時間
	/// </summary>
	float m_shakeDuration;

	/// <summary>
	/// ワールドスクリーンの左端
	/// </summary>
	float m_worldScreenLeft;

	/// <summary>
	/// ワールドスクリーンの右端
	/// </summary>
	float m_worldScreenRight;

	/// <summary>
	/// ワールドスクリーンの上端
	/// </summary>
	float m_worldScreenTop;

	/// <summary>
	/// ワールドスクリーンの下端
	/// </summary>
	float m_worldScreenBottom;

};
