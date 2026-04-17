#pragma once
#include"../Utility/Transform.h"

class Map;

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
	/// ワールドスクリーンを生成する
	/// マップのサイズによってワールドスクリーンのサイズを変える
	/// </summary>
	/// <param name="pMap"></param>
	void GenerateWorldScreen(Map* pMap);

	int GetWorldScreen()const { return m_worldScreen; }

private:

	/// <summary>
	/// カメラの追従
	/// </summary>
	/// <param name="cameraPos">カメラの位置を設定する</param>
	void UpdateFollow(Transform cameraPos);

	/// <summary>
	/// カメラのダメージ演出
	/// </summary>
	/// <param name="cameraPos"></param>
	void UpdateDamege(Transform cameraPos);

private:

	/// <summary>
	/// カメラのステータス
	/// </summary>
	enum class State {

		Follow,
		Damege,

	};

	/// <summary>
	/// カメラのステータス
	/// </summary>
	State m_state;

	/// <summary>
	/// カメラの座標に使う
	/// </summary>
	Transform m_transform;

	/// <summary>
	/// ワールドスクリーン
	/// </summary>
	int m_worldScreen;

	/// <summary>
	/// 振動の時間
	/// </summary>
	float m_shakeDuration;

};
