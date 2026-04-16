#pragma once
namespace {
	// バフを管理する量
	constexpr int kBuf = 30;
}
//// バフ
//class Buf {
//	// ステータス上昇の種類
//	PlayerStatus::Status bufType;
//	// 上昇量(倍率)
//	float m_amount;
//	// 時間(秒)
//	float m_second;
//};
class PlayerStatus {	// プレイヤーのステータスをまとめたもの(随時追加)
public:
	enum Status {
		Level,				// レベル
		HP,					// HP
		ATTACK,				// 攻撃力
		Defence,			// 防御力
		Speed,				// 移動速度
		Stamina,			// スタミナ
		CriticalRate,		// クリティカル率
		CriticalDamage,		// クリティカル割合
		Max,
	};

	// ステータスの実数値
	float m_Status[static_cast<int>(Status::Max)];
	// バフの量
	//Buf m_buf[static_cast<int>(Status::Max)][kBuf];
};
