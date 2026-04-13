#include "MyRandom.h"
#include <random>

void MyRandom::Init()
{
	Engine().seed(std::random_device{}());
}

int MyRandom::Int(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(Engine());
}

float MyRandom::Float(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(Engine());
}

float MyRandom::Float01()
{
	return Float(0.0f, 1.0f);
}

bool MyRandom::Judge(float percent)
{
	return Float(0.0f, 100.0f) < percent;
}

std::mt19937& MyRandom::Engine()
{
	static std::mt19937 engine{ std::random_device{}() };
	return engine;
}
