#include "../Map/Map.h"
#include"../Map/MapManager.h"
#include<DxLib.h>

#include<fstream>
#include<vector>
#include<string>
#include<sstream>

namespace {

	
}

Map::Map():
m_chipScaleRate(0.0f),
m_mapBlockNumX(0),
m_mapBlockNumY(0),
m_worldid(0),
m_stageid(0)
{
	for (int i = 0; i < kMapTypeNum; i++)
	{
		m_graphHandle[i] = -1;
	}
}

Map::~Map()
{
}

void Map::Init()
{
	//マップチップの拡大率の初期化
	m_chipScaleRate = (float)kMapBlockSize / (float)kMapChipSize;

	//グラフィックハンドルの初期化
	for (int i = 0; i < kMapTypeNum; i++) {
		m_graphHandle[i] = 0;

	}

	//マップチップの読み込み
	LoadDivGraph("Image\\MapChip.png",
		55, 11, 5,
		kMapChipSize, kMapChipSize, m_graphHandle);
	
	//IDの設定
	m_worldid = 1;
	m_stageid = 2;

	////CSVデータを読み込む
	LoadCSVToMapData(m_worldid, m_stageid);
}

void Map::End()
{
	m_mapData.clear();
}

Map* Map::Update()
{
	return nullptr;
}

void Map::Draw()
{
	//二次元配列から描画する
	for (int i = 0; i < m_mapBlockNumY; i++) {

		for (int j = 0; j < m_mapBlockNumX; j++) {
			
			//0なら何もしない、１なら描画
			if (m_mapData[i][j] != MapChip::Space) {
				DrawRotaGraph(j * kMapBlockSize + (kMapBlockSize / 2),
					i * kMapBlockSize + (kMapBlockSize / 2),
					m_chipScaleRate, 0.0f,
					m_graphHandle[m_mapData[i][j]], false, false);
			}
			
		}

	}
	
}

void Map::Finalize()
{
	//グラフィックハンドルの破棄
	for (int i = 0; i < kMapTypeNum; i++) {

		DeleteGraph(m_graphHandle[i]);
	}
}

void Map::DebugShow()
{
	//二次元配列MAP_BLOCK情報から描画する
	for (int i = 0; i < m_mapBlockNumY; i++) {

		for (int j = 0; j < m_mapBlockNumX; j++) {

			//0なら何もしない、１なら描画
			if (m_mapData[i][j] != MapChip::Space) {
				DrawRotaGraph(j * kMapBlockSize + (kMapBlockSize / 2),
					i * kMapBlockSize + (kMapBlockSize / 2),
					m_chipScaleRate, 0.0f,
					m_graphHandle[41], false, false);

			}
		}

	}

}

bool Map::LoadCSVToMapData(int worldNum, int stageNum)
{
	char fileNameCSV[256];
	sprintf_s(fileNameCSV, 256, "Mapdata\\Map%d_%d.csv", worldNum, stageNum);

	if (!CheckMapSize(fileNameCSV)) return false;

	// vectorでサイズ確保
	m_mapData.resize(m_mapBlockNumY);
	for (int i = 0; i < m_mapBlockNumY; i++) {
		m_mapData[i].resize(m_mapBlockNumX);
	}

	std::ifstream ifs(fileNameCSV);

	std::string buf;
	for (int y = 0; y < m_mapBlockNumY; y++) {

		
		if (!std::getline(ifs, buf)) break;

		auto list = Split(buf, ',');

		for (int x = 0; x < list.size(); x++) {
			m_mapData[y][x] = static_cast<MapChip>(std::stoi(list[x]));
		}
	}

	ifs.close();
	return true;
}

//1行の文字列をカンマで分割する
std::vector<std::string>Map::Split(const std::string& str, char separate) {

	//最終的にカンマがある毎に分割した配列を返したいが、
	//読み込んだ１行のデータの中にカンマが何個あるのかこの時点ではわかっていない
	//今まで勉強した配列は宣言時に要素数が決まっている必要があった配列（固定長配列なので
	//要素数が何個あっても使える可変長配列というものをしようする
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

bool Map::CheckMapSize(const char* fileName)
{
	//ファイルを開く
	std::ifstream ifs(fileName);

	//マップサイズのクリア
	m_mapBlockNumX = 0;
	m_mapBlockNumY = 0;

	//マップの大きさ意を１行ずつ読み込んで調べる
	//読み込んだマップの大きさがわからないので、無限ループで調べる
	std::string buf;

	while (std::getline(ifs, buf)) {

		if (buf.empty()) continue;

		m_mapBlockNumY++;

		auto separatedList = Split(buf, ',');

		m_mapBlockNumX = separatedList.size();
	}

	//開いたファイルは必ず閉じる
	ifs.close();

	//読み込みが完了したのでtrueを返す
	return true;
}

