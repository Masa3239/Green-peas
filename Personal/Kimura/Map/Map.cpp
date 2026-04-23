#include "../Map/Map.h"
#include"../Map/MapManager.h"
#include"../Chara/Collision.h"
#include<DxLib.h>

#include<fstream>
#include<vector>
#include<string>
#include<sstream>

namespace {

	// マップチップ画像
	const char* const kMapChip = "Resource\\MapChip.png";
	// CSVファイルパス（worldid / stageIidで変化）
	const char* const kMapCsv = "Resource\\Map%d_%d.csv";

}

Map::Map():
m_chipScaleRate(0.0f),
m_mapBlockNumX(0),
m_mapBlockNumY(0),
m_worldid(0),
m_stageid(0)
{
	// グラフィックハンドル初期化
	for (int i = 0; i < kMapTypeNum; i++)
	{
		m_graphHandle[i] = 0;
	}
}

Map::~Map()
{
}

void Map::Init()
{
	//マップチップの拡大率の初期化
	m_chipScaleRate = (float)kMapBlockSize / (float)kMapChipSize;

	//マップチップの読み込み
	LoadDivGraph(kMapChip,
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
			
			// 空マスは描画しない
			if (m_mapData[i][j] != MapChip::Space) {
				DrawRotaGraph(j * kMapBlockSize + (kMapBlockSize / 2),
					i * kMapBlockSize + (kMapBlockSize / 2),
					m_chipScaleRate, 0.0f,
					m_graphHandle[m_mapData[i][j]], false, false);
			}
			
		}

	}
	//for (int y = 0; y < m_mapBlockNumY; y++)
	//{
	//	for (int x = 0; x < m_mapBlockNumX; x++)
	//	{
	//		if (IsWall(x, y))
	//		{
	//			DrawBox(
	//				x * kMapBlockSize,
	//				y * kMapBlockSize,
	//				(x + 1) * kMapBlockSize,
	//				(y + 1) * kMapBlockSize,
	//				GetColor(255, 0, 0), // 赤
	//				FALSE
	//			);
	//		}
	//	}
	//}
}

void Map::Finalize()
{
	//グラフィックハンドル解放
	for (int i = 0; i < kMapTypeNum; i++) {

		DeleteGraph(m_graphHandle[i]);
	}
}

bool Map::LoadCSVToMapData(int worldNum, int stageNum)
{
	char fileNameCSV[256];
	// CSVファイル名生成（ワールド・ステージ指定）
	sprintf_s(fileNameCSV, 256, kMapCsv, worldNum, stageNum);
	// マップサイズ取得（失敗したら読み込み終了）
	if (!CheckMapSize(fileNameCSV)) return false;

	//2次元配列サイズ確保
	m_mapData.resize(m_mapBlockNumY);
	for (int i = 0; i < m_mapBlockNumY; i++) 
	{
		m_mapData[i].resize(m_mapBlockNumX);
	}

	std::ifstream ifs(fileNameCSV);
	std::string buf;
	// 1行ずつ読み込み
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

bool Map::IsWall(int mapX, int mapY) {

 // 範囲外はすべて壁扱い
 if (mapX < 0 || mapX >= m_mapBlockNumX || mapY < 0 || mapY >= m_mapBlockNumY)
 { 
	 return true;
 }

 // マップデータからチップ情報を取得
 MapChip chip = m_mapData[mapY][mapX];

 // チップの種類によって判定を分ける
 switch (chip) { 
	// 壁タイル
   case MapChip::Wall:

   return true; 
   // それ以外はすべて壁扱い
   default:
	 return false; 
 }
}

bool Map::IsWallByWorld(float worldX, float worldY) { 
	// ワールド座標 → マップ座標へ変換
	int mapX = static_cast<int>(worldX) / kMapBlockSize; 
	int mapY = static_cast<int>(worldY) / kMapBlockSize;
	// 変換後のマスが壁かどうかを判定
	return IsWall(mapX, mapY); 

}

bool Map::IsWallCircle(const Collision::Circle& circle)
{
    Vector3 pos = circle.GetPosition();
    float r = circle.GetRadius();

    int left   = (pos.x - r) / kMapBlockSize;
    int right  = (pos.x + r) / kMapBlockSize;
    int top    = (pos.y - r) / kMapBlockSize;
    int bottom = (pos.y + r) / kMapBlockSize;

    for (int y = top; y <= bottom; y++)
    {
        for (int x = left; x <= right; x++)
        {
            if (IsWall(x, y))
            {
                return true;
            }
        }
    }

    return false;
}

//void Map::DebugDrawRect(float left, float top, float right, float bottom)
//{
//	for (int y = 0; y < m_mapBlockNumY; y++)
//	{
//		for (int x = 0; x < m_mapBlockNumX; x++)
//		{
//			// 壁だけ矩形表示
//			if (IsWall(x, y))
//			{
//				DrawBox(
//					x * kMapBlockSize,
//					y * kMapBlockSize,
//					(x + 1) * kMapBlockSize,
//					(y + 1) * kMapBlockSize,
//					GetColor(255, 0, 0), // 赤（壁）
//					FALSE
//				);
//			}
//		}
//	}
//}

//1行の文字列をカンマで分割する
std::vector<std::string>Map::Split(const std::string& str, char separate) {

	
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

