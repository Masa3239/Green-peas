#include "JsonManager.h"
#include <fstream>

JsonManager& JsonManager::GetInstance()
{
	static JsonManager instance;
	
	return instance;
}

json& JsonManager::Load(std::string path)
{
	auto iter = m_jsons.find(path);
	// すでに読み込んでいたらマップから取得
	if (iter != m_jsons.end())
	{
		return iter->second;
	}

	// まだ読み込んでいなかったら読み込む
	std::ifstream fIn(path.c_str());
	assert(fIn && "jsonファイルを開けませんでした");

	json j;
	fIn >> j;

	// マップに追加してデータを返す
	return m_jsons.emplace(path, j).first->second;
}

void JsonManager::Save(std::string path)
{
	auto iter = m_jsons.find(path);
	// 読み込んでいないjsonファイルを保存しようとしたら
	if (iter == m_jsons.end())
	{
		assert(false && "読み込まれていないjsonファイルは保存できません");
		return;
	}

	std::ofstream fOut(path);

	fOut << std::setw(4) << iter->second;
}
