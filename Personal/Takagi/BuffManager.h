#pragma once
#include"BuffType.h"
class Player;

namespace {
	constexpr int kBuffSelectNum = 3;
}
class BuffManager
{
public:
	enum class Phase {
		Start,
		Select,
		End,
		Max
	};
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
	/// バフを選択する
	/// </summary>
	Buff::Type BuffSelect();
	/// <summary>
	/// 選択するバフをランダムで調べる
	/// </summary>
	void RandomBuff();
	/// <summary>
	/// プレイヤーを設定する関数
	/// </summary>
	/// <param name="player"></param>
	void SetPlayer(Player* player) { m_pPlayer = player; }
	/// <summary>
	/// バフ選択画面かどうかを調べる
	/// </summary>
	/// <returns></returns>
	bool IsSelect();
private:
	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	Player* m_pPlayer;
	/// <summary>
	/// 選択できるバフの種類
	/// </summary>
	Buff::Type m_buffType[kBuffSelectNum];
	/// <summary>
	/// 選択するフェーズ
	/// </summary>
	BuffManager::Phase m_phase;
	int m_iconHandle[kBuffMax];
	int m_Handle[kBuffMax];
	int m_selectHandle;
	int m_select;
	Buff::Type m_selected;
	Buff m_buff;
	int m_fontHandle;
};

