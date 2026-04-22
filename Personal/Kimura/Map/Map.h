#pragma once

#include "../Map/MapManager.h"
#include"../Chara/Collision.h"

#include"../Utility/Vector3.h"

#include<vector>//Split関数で使用する
#include<string>//Split関数で使用する

class Map {

public:

	Map();
    ~Map();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 後処理
	/// </summary>
	void End();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <returns></returns>
	Map* Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	void Finalize();

	void DebugShow();

	//CSVデータをマップデータとして読み込む
	bool LoadCSVToMapData(int worldNum, int stageNum);

	//CSVデータを読み込んでマップのサイズをしらべる
	bool CheckMapSize(const char* fileName);

	//マップの横サイズを取得する
	int GetMapBlockNumX() { return m_mapBlockNumX; }

	//マップの縦サイズを取得する
	int GetMapBlockNumY() { return m_mapBlockNumY; }
	//指定マップ座標が壁かどうか判定
	bool IsWall(int mapX, int mapY);
	//ワールド座標から壁判定
	bool IsWallByWorld(float worldX, float worldY);
	//矩形による壁判定
	bool IsWallRect(float left, float top, float right, float bottom);
	void DebugDrawRect(float left, float top, float right, float bottom);

	std::vector<std::string>Split(const std::string& str, char separate);

private:

	//===============================
	//メンバ変数
	//===============================
	int m_graphHandle[kMapTypeNum];   //グラフィックハンドル
	float m_chipScaleRate;   //マップチップの拡大率

	int m_mapBlockNumX;     //マップの横サイズ
	int m_mapBlockNumY;     //マップの縦サイズ

	//読み込んだデータの大きさによってマップサイズを決めるのでポインタを用意
	std::vector<std::vector<MapChip>> m_mapData;    //マップデータ
	
	int m_worldid;          //読み込むマップのワールドID
	int m_stageid;          //読み込むマップのステージID

	Vector3 m_prevPlayerPos;

};