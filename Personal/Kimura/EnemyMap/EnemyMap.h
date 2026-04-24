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

	// CSVを読み込んで敵配置データを作成
	bool LoadCSVToMapData(int worldNum, int stageNum);


    // CSVから読み込んだ敵スポーンデータ一覧を取得する
    //敵の種類と座標が入ったリスト
	const std::vector<EnemySpawnData>& GetSpawnList() const { return m_spawnList; }

	std::vector<std::string>Split(const std::string& str, char separate);

private:

	//===============================
	//メンバ変数
	//===============================

	int m_worldid;          //読み込むマップのワールドID
	int m_stageid;          //読み込むマップのステージID

	std::vector<EnemySpawnData> m_spawnList;


};