#pragma once
namespace {
	// バフを管理する量
	constexpr int kBuf = 30;
}
struct PlayerStatus {
public:

	//	Level,				// レベル
	//	HP,					// HP
	//	Attack,				// 攻撃力
	//	Defence,			// 防御力
	//	Speed,				// 移動速度
	//	Stamina,			// スタミナ
	//	CriticalRate,		// クリティカル率
	//	CriticalDamage,		// クリティカル割合
	//	Max,
	int Level;
	float HP, Attack, Defence, Speed, Stamina, CriticalRate, CriticalDamage;
	/// <summary>
	/// デフォルトコンストラクタ
	/// 要素のすべてを0で初期化する
	/// 定数宣言で使えるようにするために、
	/// constexprをつけてヘッダーに記載
	/// </summary>
	constexpr PlayerStatus() : Level(0), HP(0.0f), Attack(0.0f),Defence(0.0f), Speed(0.0f), Stamina(0.0f), CriticalRate(0.0f), CriticalDamage(0.0f) {}

	/// <summary>
	/// 引数ありのコンストラクタ
	/// </summary>
	/// <param name="level"></param>
	/// <param name="hp"></param>
	/// <param name="attack"></param>
	/// <param name="defence"></param>
	/// <param name="speed"></param>
	/// <param name="stamina"></param>
	/// <param name="criticalRate"></param>
	/// <param name="criticalDamage"></param>
	constexpr PlayerStatus(int level, float hp, float attack, float defence, float speed, float stamina, float criticalRate, float criticalDamage) : Level(level), HP(hp), Attack(attack), Defence(defence), Speed(speed), Stamina(stamina), CriticalRate(criticalRate), CriticalDamage(criticalDamage) {}

	/// <summary>
	/// マイナスのステータスを返す
	/// </summary>
	/// <returns></returns>
	PlayerStatus operator-() const;

	/// <summary>
	/// ステータスの加算
	/// </summary>
	/// <param name="vec">足されるステータス</param>
	/// <returns></returns>
	PlayerStatus operator+(const PlayerStatus& status) const;

	/// <summary>
	/// ステータスの減算
	/// </summary>
	/// <param name="vec">引かれるステータス</param>
	/// <returns></returns>
	PlayerStatus operator-(const PlayerStatus& status) const;

	/// <summary>
	/// ステータス同士の乗算
	/// </summary>
	/// <param name="scale">乗算する量</param>
	/// <returns></returns>
	PlayerStatus operator*(const PlayerStatus& status) const;
	/// <summary>
	/// ステータス同士の乗算
	/// </summary>
	/// <param name="scale">乗算する量</param>
	/// <returns></returns>
	PlayerStatus operator/(const PlayerStatus& status) const;
	/// <summary>
	/// ステータスの乗算
	/// </summary>
	/// <param name="scale">乗算する量</param>
	/// <returns></returns>
	PlayerStatus operator*(float scale) const;

	/// <summary>
	/// ステータスの除算
	/// </summary>
	/// <param name="scale">除算する量</param>
	/// <returns></returns>
	PlayerStatus operator/(float scale) const;

	/// <summary>
	/// ステータスとステータスの加算代入
	/// 自身を変更するので参照を返す
	/// </summary>
	/// <param name="status"></param>
	/// <returns></returns>
	PlayerStatus& operator+=(const PlayerStatus& status);

	/// <summary>
	/// ステータスとステータスの減算代入演算子
	/// 自身を変更するので参照を返す
	/// </summary>
	/// <param name="status"></param>
	/// <returns></returns>
	PlayerStatus& operator-=(const PlayerStatus& status);

	/// <summary>
	/// ステータスの乗算代入演算子
	/// 自身を変更するので参照を返す
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	PlayerStatus& operator*=(const PlayerStatus& status);

	/// <summary>
	/// ステータスの除算代入演算子
	/// 自身を変更するので参照を返す
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	PlayerStatus& operator/=(const PlayerStatus& status);
	/// <summary>
	/// ステータスの乗算代入演算子
	/// 自身を変更するので参照を返す
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	PlayerStatus& operator*=(float scale);

	/// <summary>
	/// ステータスの除算代入演算子
	/// 自身を変更するので参照を返す
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	PlayerStatus& operator/=(float scale);

	/// <summary>
	/// ステータスの比較 等しいかどうか
	/// </summary>
	/// <param name="status"></param>
	/// <returns>等しいならtrue</returns>
	bool operator==(const PlayerStatus& status) const;

	/// <summary>
	/// ステータスの比較 等しくないかどうか
	/// </summary>
	/// <param name="status"></param>
	/// <returns>等しくなければtrue</returns>
	bool operator!=(const PlayerStatus& status) const;

	/// <summary>
	/// 初期設定
	/// </summary>
	void Reset();

};