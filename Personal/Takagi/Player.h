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


	void Init();
	void End();
	void Update();
	/// <summary>
	/// プレイヤー移動の更新処理
	/// </summary>
	void Move();
	void Draw();

private:

	Transform m_transform;

	//// プレイヤーのグラフィックハンドル
	//int m_handle[playerFrame];

	//// プレイヤー画像のサイズ
	//int m_sizeX;
	//int m_sizeY;

	//// フレーム更新をするカウント
	//int m_animationCount;

	//// アニメーションのフレーム
	//int m_animationFrame;

	// プレイヤーが向いている方向(左右)
	int m_direction;

	// プレイヤーの移動量
	Vector3 m_moveVector;
};