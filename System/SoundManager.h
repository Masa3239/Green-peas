#pragma once

#include <array>

namespace Sound
{
	enum class BGM
	{
		Pause,
		BGM1,
		BGM2,
		BGM3,
		BGM4,
		Clear,
		Max
	};

	enum class SE
	{
		Temp,
		Bomerang,
		Boss1,
		Boss2,
		BossBullet,
		Bow,
		Bullet,
		Button,
		Chest,
		Confirm1,
		Confirm2,
		Critical,
		CursorMove,
		Damage1,
		Damage2,
		Dash,
		Explosion,
		Fire1,
		Fire2,
		Heal,
		ItemGet1,
		ItemGet2,
		LevelUp,
		Pause,
		Damage3,
		Damage4,
		PowerUp,
		Button2,
		Damage5,
		Sword1,
		Sword2,
		Sword3,
		Thunder,
		BuffDecision,
		CharactorButton,
		CharactorSelect,
		FailedRotation,
		Katana,
		Buff,
		Rotation1,
		Rotation2,
		Max
	};
}

class SoundManager
{
public:

	static SoundManager& GetInstance();

	~SoundManager() = default;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// SEの再生
	/// </summary>
	/// <param name="id">再生したいSEのID</param>
	void PlaySe(Sound::SE id);

	/// <summary>
	/// BGMの再生
	/// </summary>
	/// <param name="id"></param>
	void PlayBGM(Sound::BGM id);

	/// <summary>
	/// 再生中のBGMの停止
	/// </summary>
	void StopBGM();

	/// <summary>
	/// 読み込んだデータの解放
	/// </summary>
	void Release();

private:

	/// <summary>
	/// コンストラクタ
	/// シングルトンパターンのクラスならprivateにして生成できないようにする
	/// </summary>
	SoundManager();

	// シングルトンパターンのクラスでは、コピーできないように「禁止」する
	// コピー禁止 Class a = b; / Class a(b);
	SoundManager(const SoundManager&) = delete;
	// コピー代入禁止	a = b;
	SoundManager& operator=(const SoundManager&) = delete;
	// ムーブ禁止		
	SoundManager(SoundManager&&) = delete;
	// ムーブ代入禁止
	SoundManager& operator=(SoundManager&&) = delete;

	/// <summary>
	/// 音の読み込み
	/// </summary>
	/// <param name="handle">読み込んだ音を格納するハンドルの配列</param>
	/// <param name="number">読み込む音の数</param>
	/// <param name="key">jsonファイルの読み込みたいキーの名前</param>
	void LoadSound(int handle[], int number, const char* key);

	/// <summary>
	/// BGMのクロスフェード処理
	/// </summary>
	void CrossFading();

	/// <summary>
	/// SEのハンドル
	/// </summary>
	std::array<int, static_cast<size_t>(Sound::SE::Max)> m_seHandles;

	/// <summary>
	/// BGMのハンドル
	/// </summary>
	std::array<int, static_cast<size_t>(Sound::BGM::Max)> m_bgmHandles;

	/// <summary>
	/// 再生中のBGMハンドル
	/// </summary>
	int m_currentBgmHandle;

	/// <summary>
	/// 次に再生するBGMハンドル
	/// </summary>
	int m_nextBgmHandle;

	/// <summary>
	/// 再生中のBGMの音量
	/// </summary>
	float m_currentBgmVolume;

	/// <summary>
	/// 次に再生するBGMの音量
	/// </summary>
	float m_nextBgmVolume;

	/// <summary>
	/// BGMの遷移速度
	/// </summary>
	float m_bgmFadeSpeed;

	/// <summary>
	/// クロスフェード処理を行うかどうか
	/// </summary>
	bool m_isCrossFading;
};
