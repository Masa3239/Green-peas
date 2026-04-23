#pragma once

#include"../EnemyMap/EnemySpawnData.h"
#include"../Utility/Vector3.h"

#include<vector>//Split関数で使用する
#include<string>//Split関数で使用する

class EnemyMap {


public:

	EnemyMap();
	~EnemyMap();

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
	EnemyMap* Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	void Finalize();

	void DebugShow();

	//CSVデータをマップデータとして読み込む
	bool LoadCSVToMapData(int worldNum, int stageNum);

	std::vector<std::string>Split(const std::string& str, char separate);

private:

	//===============================
	//メンバ変数
	//===============================

	int m_worldid;          //読み込むマップのワールドID
	int m_stageid;          //読み込むマップのステージID

	std::vector<EnemySpawnData> m_spawnList;


};