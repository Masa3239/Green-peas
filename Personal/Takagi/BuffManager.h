#pragma once
#include"BuffType.h"
class Player;
namespace {
	constexpr int kBuffSelectNum = 3;
}
class BuffManager
{
public:
	BuffManager();
	~BuffManager();
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
	/// バフ選択のスタート処理
	/// </summary>
	void BuffSelectStart();
	/// <summary>
	/// 選択するバフをランダムで調べる
	/// </summary>
	void RandomBuff();

private:
	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	Player* m_pPlayer;
	/// <summary>
	/// 選択できるバフの種類
	/// </summary>
	Buff::Type m_buffType[kBuffSelectNum];
};

