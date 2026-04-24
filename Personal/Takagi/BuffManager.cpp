#include "BuffManager.h"
#include"BuffType.h"
#include"../../Utility/MyRandom.h"
#include<DxLib.h>
#include"../../System/InputManager.h"
namespace {

}

BuffManager::BuffManager()
{
}

BuffManager::~BuffManager()
{
}

void BuffManager::Init()
{
}

void BuffManager::End()
{
}

void BuffManager::Update()
{
	if (InputManager::GetInstance().IsPressed(Input::Action::Cancel)) {
		RandomBuff();
	}
}


void BuffManager::Draw()
{
	for (int i = 0;i < kBuffSelectNum;i++) {
		printfDx("BuffType : %d\n", static_cast<int>(m_buffType[i]));
	}
}

void BuffManager::BuffSelectStart()
{
}
void BuffManager::RandomBuff()
{

	for (int i = 0;i < kBuffSelectNum;i++) {
		// すでに同じバフが選ばれたかどうか
		bool selected = true;
		// ランダムで抽選されたバフの種類
		int select = 0;
		// 選ばれていないバフがでるまで繰り返す
		while (selected)
		{
			select = MyRandom::Int(0, static_cast<int>(Buff::Type::Max) - 1);
			m_buffType[i] = static_cast<Buff::Type>(selected);
			for (int j = 0;j < kBuffSelectNum;j++) {
				selected = false;
				if (m_buffType[i] == m_buffType[j]) {
					selected = true;
					break;
				}
			}
		}
	}
}
