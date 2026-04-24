#include "../EnemyMap/EnemyMap.h"
#include<DxLib.h>

#include<fstream>
#include<vector>
#include<string>
#include<sstream>

namespace {

	// CSVファイルパス（worldid / stageIidで変化）
	const char* const kEnemyMapCsv = "Resource\\EnemyMap%d_%d.csv";

	// 1マスのサイズ
	constexpr int kCellSize = 40;

}

EnemyMap::EnemyMap() :
	m_worldid(0),
	m_stageid(0)
{
	
}

EnemyMap::~EnemyMap()
{
}

void EnemyMap::Init()
{

	//IDの設定
	m_worldid = 1;
	m_stageid = 1;

	////CSVデータを読み込む
	LoadCSVToMapData(m_worldid, m_stageid);
}

void EnemyMap::End()
{
}

EnemyMap* EnemyMap::Update()
{
	return nullptr;
}

void EnemyMap::Draw()
{
}

void EnemyMap::Finalize()
{
}

bool EnemyMap::LoadCSVToMapData(int worldNum, int stageNum)
{
	char fileNameCSV[256];
	// CSVファイル名生成（ワールド・ステージ指定）
	sprintf_s(fileNameCSV, 256, kEnemyMapCsv, worldNum, stageNum);
	
	std::ifstream ifs(fileNameCSV);
	std::string buf;
	// 既存データをクリア
	m_spawnList.clear();
	// y座標
	int y = 0;
	// 1行ずつ読み込み
	while (std::getline(ifs, buf))
	{
		// カンマで分割
		auto list = Split(buf, ',');

		for (int x = 0; x < list.size(); x++)
		{
			int typeNum = std::stoi(list[x]);

			if (typeNum == 0) continue; // 0は空マス

			EnemySpawnData data;
			// 数字 → 敵タイプ変換
			switch (typeNum)
			{
			case 1: data.type = EnemyManager::EnemyType::Melee; break;  // 近接敵
			case 2: data.type = EnemyManager::EnemyType::Shooter; break;// 遠距離敵
			case 3: data.type = EnemyManager::EnemyType::Miniboss; break; // 中ボス
			default:
				continue; // 未定義は無視
			}
			// グリッド座標 → 実際のワールド座標に変換
			data.pos.x = x * kCellSize;
			data.pos.y = y * kCellSize;
			data.pos.z = 0.0f;

			m_spawnList.push_back(data);
		}
		// 次の行へ
		y++;
	}

	return true;
}

//1行の文字列をカンマで分割する
std::vector<std::string>EnemyMap::Split(const std::string& str, char separate) {

	std::vector<std::string>separatedList;

	//引数で渡された文字列を分割しやすくする<sstream>
	std::stringstream ss(str);

	//分割したデータの一時保存をする変数を宣言
	std::string buf;

	//引数の文字列strを１文字ずつチェック
	//分割する記号(separate)が見つかったら分割する
	//最後の文字まで繰り返す
	while (std::getline(ss, buf, separate)) {
		//分割する記号(separate)が見つかったら可変長配列に入れていく
		separatedList.push_back(buf);
	}
	//分割した配列をかえす
	return separatedList;
}
