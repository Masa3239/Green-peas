#pragma once
#include"../Utility/Transform.h"

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
	/// 終了処理
	/// </summary>
	void End();

private:

	/// <summary>
	/// カメラの追従
	/// </summary>
	/// <param name="cameraPos">カメラの位置を設定する</param>
	void UpdateFollow(Transform cameraPos);

private:

	enum class State {

		Follow,
		Damege,

	};

	State m_state;

	Transform m_transform;

	int m_worldScreen;

};

