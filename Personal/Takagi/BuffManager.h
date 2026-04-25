#pragma once
#include"BuffType.h"
class Player;

namespace {
	constexpr int kBuffSelectNum = 3;
}
class BuffManager
{
public:
	// バフ選択の状態
	enum class Phase {
		Start,		// バフを抽選する前
		Select,		// バフを抽選
		End,		// バフを選択
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
	/// <summary>
	/// バフを適応する
	/// </summary>
	/// <param name="buffType"></param>
	void AdaptBuff(const Buff::Type& buffType);
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
	/// 選択したバフの種類
	/// </summary>
	Buff::Type m_selected;
	/// <summary>
	/// 選択するフェーズ
	/// </summary>
	BuffManager::Phase m_phase;
	/// <summary>
	/// 選択状態を進行させる表示のグラフィックハンドル
	/// </summary>
	int m_proceedHandle[static_cast<int>(Phase::Max)];
	/// <summary>
	/// ボタン表示のグラフィックハンドル
	/// </summary>
	int m_buttonHandle;
	/// <summary>
	/// アイコン画像のグラフィックハンドル
	/// </summary>
	int m_iconHandle[kBuffMax];
	/// <summary>
	/// 説明テキスト画像のグラフィックハンドル
	/// </summary>
	int m_textHandle[kBuffMax];
	/// <summary>
	/// バフ表示背景のグラフィックハンドル
	/// </summary>
	int m_backHandle;
	/// <summary>
	/// 選択表示のグラフィックハンドル
	/// </summary>
	int m_selectHandle;
	/// <summary>
	/// 選ばれたバフたちの何個目を選んでいるか
	/// </summary>
	int m_select;
	/// <summary>
	/// バフのレベル
	/// </summary>
	Buff m_buff;
	/// <summary>
	/// フォトハンドル
	/// </summary>
	int m_fontHandle;
};

