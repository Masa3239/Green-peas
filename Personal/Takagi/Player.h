#include"../Chara/Collision.h"
#include"../Utility/Transform.h"
#include"../Utility/Vector3.h"

namespace {
	enum class Status {
		Stop,		// 停止状態
		Walk,		// 歩行状態
		Dash,		// ダッシュ(回避)
		Max
	};

	// プレイヤーのアニメーションの枚数
	constexpr int playerFrame = 8;
}

class Player {
public:
	/// <summary>
	/// プレイヤーのコンストラクタ
	/// メンバ変数の初期設定を行う
	/// </summary>
	Player();

	/// <summary>
	/// プレイヤーのデストラクタ
	/// </summary>
	~Player();

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
	/// プレイヤー移動の更新処理
	/// </summary>
	void Move();
	/// <summary>
	/// 移動量の計算
	/// </summary>
	void MoveAmount();
	/// <summary>
	/// 移動速度の更新処理
	/// </summary>
	void SpeedUpdate();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// プレイヤーの角度を取得する関数
	/// </summary>
	/// <returns>プレイヤーの角度</returns>
	float GetRadian() { return m_transform.rotation.y; }


private:

	/// <summary>
	/// プレイヤーのTransform
	/// </summary>
	Transform m_transform;


	// プレイヤーが向いている方向(左右)g
	int m_direction;

	// 移動速度
	float m_speed;
	// 速さの割合
	float m_accel;
	// 
	float m_deltaTime;

	// プレイヤーの移動量
	Vector3 m_moveVector;
};