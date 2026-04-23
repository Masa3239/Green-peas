#pragma once
#include"Player.h"
class Warrior:public Player
{
public:
	/// <summary>
	/// プレイヤーのコンストラクタ
	/// メンバ変数の初期設定を行う
	/// </summary>
	Warrior(ObjectManager* objManager);

	/// <summary>
	/// プレイヤーのデストラクタ
	/// </summary>
	~Warrior();
	Character::Job GetPlayerJob()override { return Character::Job::Warrior; }


	///// <summary>
	///// 初期化処理
	///// </summary>
	//void Init()override;
	///// <summary>
	///// 終了処理
	///// </summary>
	//void End()override;
	///// <summary>
	///// 更新処理
	///// </summary>
	//void Update()override;
	///// <summary>
	///// プレイヤー移動の更新処理
	///// </summary>
	//void Move();
	///// <summary>
	///// 移動量の計算
	///// </summary>
	//void MoveAmount()override;
	///// <summary>
	///// スタミナを消費するかどうか
	///// </summary>
	///// <param name="stamina"></param>
	//void Dash(bool stamina = true)override;
	///// <summary>
	///// 移動速度の更新処理
	///// </summary>
	//void SpeedUpdate()override;
	///// <summary>
	///// 描画処理
	///// </summary>
	//void Draw()override;
	///// <summary>
	///// デバッグ処理
	///// </summary>
	//void Debug();
};

