#include"../Chara/Collision.h"
#include"../Utility/Transform.h"
#include"../Utility/Vector3.h"
#include"../../Object/GameObject.h"
#include<memory>

class Gauge;
namespace Collision{
	class Shape;
	class Circle;
	class AABB;
}

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

class Camera;

class Player:public GameObject {
public:
	enum {
		Hp,
		Stamina,
		Anger,
		Max
	};
	/// <summary>
	/// プレイヤーのコンストラクタ
	/// メンバ変数の初期設定を行う
	/// </summary>
	Player(ObjectManager* objManager);

	/// <summary>
	/// プレイヤーのデストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init()override;
	/// <summary>
	/// 終了処理
	/// </summary>
	void End()override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update()override;
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
	void Draw()override;
	/// <summary>
	/// デバッグ処理
	/// </summary>
	void Debug();
	/// <summary>
	/// ダメージを受ける関数
	/// </summary>
	void Damage(float damage);

	void SetCamera(Camera* camera) { m_camera = camera; }
	/// <summary>
	/// プレイヤーの角度を取得する関数
	/// </summary>
	/// <returns>プレイヤーの角度</returns>
	float GetRadian() { return m_transform.rotation.y; }

	/// <summary>
	/// プレイヤーが死んでいるかどうか
	/// </summary>
	/// <returns>死んでいたらtrue</returns>
	bool IsDead();
	/// <summary>
	/// 選択したゲージの現在の量を取得する関数
	/// </summary>
	/// <param name="gauge">
	/// ゲージの種類
	/// Hp      -> HPゲージ
	/// Stamina -> スタミナゲージ
	/// Anger   -> 怒りゲージ
	/// </param>
	/// <returns></returns>
	float GetGaugeCurrentValue(int gauge);
	/// <summary>
	/// 選択したゲージの最大値を取得する関数
	/// </summary>
	/// <param name="gauge">
	/// ゲージの種類
	/// Hp      -> HPゲージ
	/// Stamina -> スタミナゲージ
	/// Anger   -> 怒りゲージ
	/// </param>
	/// <returns></returns>
	float GetGaugeMaxValue(int gauge);
	/// <summary>
	/// 選択したゲージの割合を取得する関数
	/// </summary>
	/// <param name="gauge">
	/// ゲージの種類
	/// Hp      -> HPゲージ
	/// Stamina -> スタミナゲージ
	/// Anger   -> 怒りゲージ
	/// </param>
	/// <returns></returns>
	float GetGaugeRate(int gauge);
	Collision::Circle GetCircle() { return m_circle; }
private:
	/// <summary>
	/// ダッシュ可能かどうかを調べる関数
	/// </summary>
	/// <returns>ダッシュ可能ならtrue</returns>
	bool CheckCanDash();
	/// <summary>
	/// ダッシュ中かどうかを調べる関数
	/// </summary>
	/// <returns>ダッシュ中ならtrue</returns>
	bool CheckDashNow();
private:

	/// <summary>
	/// プレイヤーのTransform
	/// </summary>
	Transform m_transform;


	// プレイヤーが向いている方向(左右)
	int m_direction;

	// 移動速度
	float m_speed;
	// 速さの割合
	float m_accel;
	// フレーム間の経過時間
	float m_deltaTime;

	// プレイヤーの移動量
	Vector3 m_moveVector;

	/// <summary>
	/// ゲージの配列(HP・スタミナ・怒り)
	/// </summary>
	std::unique_ptr<Gauge> m_gauges[Max];

	Camera* m_camera;

	/// <summary>
	/// 四角の当たり判定
	/// </summary>
	Collision::AABB m_box;
	Collision::Circle m_circle;

};