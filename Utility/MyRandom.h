#pragma once

#include <random>

/// <summary>
/// 乱数を生成するクラス
/// 以下のページを参考に作成
/// https://cpprefjp.github.io/reference/random.html
/// </summary>
class MyRandom
{
public:

	/// <summary>
	/// 乱数クラスの初期化（起動時に一回）
	/// </summary>
	static void Init();

	/// <summary>
	/// 引数の範囲内での整数乱数を生成（引数を含む）
	/// </summary>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>生成乱数</returns>
	static int Int(int min, int max);

	/// <summary>
	/// 引数の範囲内での実数乱数を生成（引数を含む）
	/// </summary>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>生成乱数</returns>
	static float Float(float min, float max);

	/// <summary>
	/// 0.0f～1.0fの実数の乱数生成
	/// </summary>
	/// <returns>生成乱数</returns>
	static float Float01();

	/// <summary>
	/// 確率判定
	/// </summary>
	/// <param name="percent">確率</param>
	/// <returns>確率内ならtrue</returns>
	static bool Judge(float percent);

private:

	/// <summary>
	/// 乱数を生成する mt19937は擬似乱数生成エンジン
	/// </summary>
	/// <returns></returns>
	static std::mt19937& Engine();
};
