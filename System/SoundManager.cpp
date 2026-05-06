#include "SoundManager.h"
#include <DxLib.h>
#include <cassert>
#include <string>
#include "../System/JsonManager.h"
#include "../Utility/MyMath.h"
#include "../Utility/Time.h"

namespace
{
	// 設定ファイルのファイルパス
	const char* const kSettingsPath = "Config\\Settings.json";
	// サウンドデータへの参照を持ったファイルパス
	const char* const kSoundDataPath = "Resource\\SoundPath.json";

	const char* const kFolderPath = "folderPath";
	const char* const kSEFilePath = "seFilePath";
	const char* const kBGMFilePath = "bgmFilePath";

	// デフォルトのBGM遷移速度
	constexpr float kDefaultFadeSpeed = 255.0f;

	// 最大音量
	constexpr float kMaxVolume = 255.0f;
	// 最小音量
	constexpr float kMinVolume = 0.0f;
}

SoundManager::SoundManager() :
	m_currentBgmHandle(-1),
	m_nextBgmHandle(-1),
	m_currentBgmVolume(kMaxVolume),
	m_nextBgmVolume(kMinVolume),
	m_bgmFadeSpeed(kDefaultFadeSpeed),
	m_isCrossFading(false)
{
	// ハンドルを初期化
	m_seHandles.fill(-1);
	m_bgmHandles.fill(-1);

	// サウンドデータを読み込む
	LoadSound(m_seHandles.data(), static_cast<int>(Sound::SE::Max), kSEFilePath);
	LoadSound(m_bgmHandles.data(), static_cast<int>(Sound::BGM::Max), kBGMFilePath);
}

SoundManager& SoundManager::GetInstance()
{
	static SoundManager instance;

	return instance;
}

void SoundManager::Update()
{
	// クロスフェード処理
	CrossFading();

	// BGMが再生されていたら音量を設定
	float volume = m_currentBgmVolume * static_cast<float>(JsonManager::GetInstance().Load(kSettingsPath)["bgmVolume"]);
	if (m_currentBgmHandle != -1) ChangeVolumeSoundMem(volume, m_currentBgmHandle);

	// 次のBGMが再生されていたら音量を設定
	volume = m_nextBgmVolume * static_cast<float>(JsonManager::GetInstance().Load(kSettingsPath)["bgmVolume"]);
	if (m_nextBgmHandle != -1) ChangeVolumeSoundMem(volume, m_nextBgmHandle);
}

void SoundManager::PlaySe(Sound::SE id)
{
	int handle = m_seHandles[static_cast<int>(id)];

	// 読み込めていないIDなら即時return
	assert(handle != -1 && "読み込みに失敗したSEを再生しようとしています");
	if (handle == -1) return;

	// SEの再生
	PlaySoundMem(handle, DX_PLAYTYPE_BACK);

	// 音量設定
	float vol = JsonManager::GetInstance().Load(kSettingsPath)["seVolume"];
	ChangeVolumeSoundMem(static_cast<int>(vol * kMaxVolume), handle);
}

void SoundManager::PlayBGM(Sound::BGM id)
{
	// すでに再生していたら停止する
	// 多重再生を防ぐ
	//StopBGM();

	int handle = m_bgmHandles[static_cast<int>(id)];

	// 現在再生中のBGMと同じBGMを再生しようとしたら処理を行わない
	if (m_currentBgmHandle == handle) return;

	// 読み込めていないIDなら即時return
	assert(handle != -1 && "読み込みに失敗したBGMを再生しようとしています");
	if (handle == -1) return;

	// 再生中のBGMハンドルの更新
	// BGMが再生されていなかったら
	if (m_currentBgmHandle == -1)
	{
		m_currentBgmHandle = handle;

		// BGMの再生
		PlaySoundMem(m_currentBgmHandle, DX_PLAYTYPE_LOOP);
	}
	// BGMが再生されていたら
	else
	{
		// クロスフェードを開始する
		m_nextBgmHandle = handle;

		m_currentBgmVolume = kMaxVolume;
		m_nextBgmVolume = kMinVolume;

		m_isCrossFading = true;

		// BGMの再生
		PlaySoundMem(m_nextBgmHandle, DX_PLAYTYPE_LOOP);
	}
}

void SoundManager::StopBGM()
{
	// BGMが再生しているか確認
	if (m_currentBgmHandle == -1) return;

	// BGMの停止
	StopSoundMem(m_currentBgmHandle);

	m_currentBgmHandle = -1;
}

void SoundManager::Release()
{
	for (auto& bgm : m_bgmHandles)
	{
		if (bgm == -1) continue;

		// SEデータの削除
		DeleteSoundMem(bgm);

		// ハンドルを初期値にしておく
		bgm = -1;
	}

	for (auto& se : m_seHandles)
	{
		if (se == -1) continue;

		// SEデータの削除
		DeleteSoundMem(se);

		// ハンドルを初期値にしておく
		se = -1;
	}
}

void SoundManager::LoadSound(int handle[], int number, const char* key)
{
	auto data = JsonManager::GetInstance().Load(kSoundDataPath);

	// フォルダーパスを取得
	std::string folderPath = data["folderPath"];

	for (int i = 0; i < number; i++)
	{
		// データパスを取得
		std::string dataPath = data[key][i];

		// ファイルパスを作成 フォルダ + データ名
		std::string filePath = folderPath + dataPath;

		// SEの読み込み
		handle[i] = LoadSoundMem(filePath.c_str());

		// 読み込みが失敗していたら警告
		assert(handle[i] != -1 && "音の読み込みに失敗しました");
		if (handle[i] == -1) continue;
	}
}

void SoundManager::CrossFading()
{
	// クロスフェード処理を行わないなら処理を停止
	if (!m_isCrossFading) return;

	float fadeSpeed = m_bgmFadeSpeed * Time::GetInstance().GetDeltaTime();

	// 現在のBGMの音量を最小に遷移する
	m_currentBgmVolume = MyMath::Approach(m_currentBgmVolume, kMinVolume, fadeSpeed);
	// 次に再生するBGMの音量を最大に遷移する
	m_nextBgmVolume = MyMath::Approach(m_nextBgmVolume, kMaxVolume, fadeSpeed);

	// 次に再生するBGMが最大音量になったら
	if (m_nextBgmVolume >= kMaxVolume)
	{
		StopBGM();

		m_currentBgmHandle = m_nextBgmHandle;
		m_nextBgmHandle = -1;

		m_currentBgmVolume = kMaxVolume;

		m_isCrossFading = false;
	}
}
