#pragma once

#include <nlohmann/json.hpp>

using nlohmann::json;

class JsonManager
{
public:

	/// <summary>
	/// インスタンスの生成、取得を行う
	/// </summary>
	static JsonManager& GetInstance();

	~JsonManager() = default;

	/// <summary>
	/// jsonファイルを読み込んで取得する
	/// すでに読み込んでいる場合は取得のみ
	/// </summary>
	json& Load(std::string path);

	/// <summary>
	/// jsonファイルを指定したパスに保存する
	/// </summary>
	void Save(std::string path);

private:

	JsonManager() = default;
	// コピーコンストラクタ禁止
	JsonManager(const JsonManager&) = delete;
	// コピー代入禁止
	JsonManager& operator=(const JsonManager&) = delete;
	// ムーブ禁止
	JsonManager(JsonManager&&) = delete;
	// ムーブ代入禁止
	JsonManager& operator=(JsonManager&&) = delete;

	std::unordered_map<std::string, json> m_jsons;
};
