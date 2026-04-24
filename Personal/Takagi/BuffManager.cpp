#include "BuffManager.h"
#include"BuffType.h"
#include"../../Utility/MyRandom.h"
#include<DxLib.h>
#include"../../System/InputManager.h"
#include"../../Utility/MyMath.h"
#include<string>
#include"../../System/PauseManager.h"
namespace {
	const char* const kIconPath = "Resource\\Iccons\\skill_";
	const char* const kPing = ".png";
	const char* const kSelectPath = "Resource\\Iccons\\select.png";

}

BuffManager::BuffManager() :
	m_pPlayer(nullptr),
	m_buffType(),
	m_phase(Phase::Start),
	m_select(0),
	m_selected(Buff::Type::Max)
{
	// アイコン画像の読み込み
	std::string path = kIconPath;
	for (int i = 0;i < kBuffMax;i++) {
		path = kIconPath + std::to_string(i) + kPing;
		m_iconHandle[i] = LoadGraph(path.c_str());
	}
	m_selectHandle = -1;
	m_selectHandle = LoadGraph(kSelectPath);
}

BuffManager::~BuffManager()
{
	for (int& handle:m_iconHandle) {
		DeleteGraph(handle);
	}
	DeleteGraph(m_selectHandle);
}

void BuffManager::Init()
{
}

void BuffManager::End()
{
}

void BuffManager::Update()
{



		switch (m_phase)
		{
		case Phase::Start:

			RandomBuff();
			if (InputManager::GetInstance().IsPressed(Input::Action::Confirm)) {
			m_phase = Phase::Select;
			}
			break;
		case Phase::Select:
			if (!InputManager::GetInstance().IsPressed(Input::Action::Confirm)) {
				break;
			}
			m_selected = BuffSelect();
			if (PauseManager::GetInstance().IsPause()) {
				PauseManager::GetInstance().TogglePause();
			}
			m_phase = Phase::Max;
			break;
		default:
			break;
		}

	if (InputManager::GetInstance().IsPressed(Input::Action::Left)) {
		m_select--;
	}
	if (InputManager::GetInstance().IsPressed(Input::Action::Right)) {

		m_select++;
	}
	m_select = MyMath::Clamp(m_select, 0, kBuffSelectNum - 1);
	if (!PauseManager::GetInstance().IsPause()) return;
}


void BuffManager::Draw()
{
	for (int i = 0;i < kBuffSelectNum;i++) {
		printfDx("BuffType[%d] : %d\n",i, static_cast<int>(m_buffType[i]));
	}
	printfDx("選択された: %d\n", static_cast<int>(m_selected));
	printfDx("選択中    : %d\n", static_cast<int>(m_select));
	printfDx("選択段階  : %d\n", static_cast<int>(m_phase));
	if (m_selected != Buff::Type::Max) {
		DrawRotaGraph(400, 450, 0.2f, 0, m_iconHandle[static_cast<int>(m_selected)], TRUE);
	}
	for (int i = 0;i < kBuffSelectNum;i++) {
		if(i==m_select&&m_phase==Phase::Select)
		DrawRotaGraph(150+150*i, 200, 0.05f, 0, m_selectHandle, TRUE);
		DrawRotaGraph(150+150*i, 200, 0.2f, 0, m_iconHandle[static_cast<int>(m_buffType[i])], TRUE);
	}
	if (!IsSelect())return;
}

void BuffManager::BuffSelectStart()
{
	if (!PauseManager::GetInstance().IsPause()) {
		PauseManager::GetInstance().TogglePause();
	}
	m_phase = Phase::Start;
}
Buff::Type BuffManager::BuffSelect()
{
	return m_buffType[m_select];
}
void BuffManager::RandomBuff()
{
	m_buffType[0] = Buff::Type::Max;
	m_buffType[1] = Buff::Type::Max;
	m_buffType[2] = Buff::Type::Max;
	for (int i = 0;i < kBuffSelectNum;i++) {
		// すでに同じバフが選ばれたかどうか
		bool selected = true;
		// ランダムで抽選されたバフの種類
		int select = 0;
		// 選ばれていないバフがでるまで繰り返す
		while (selected)
		{
			select = MyRandom::Int(0, static_cast<int>(Buff::Type::Max) - 1);
			m_buffType[i] = static_cast<Buff::Type>(select);
			for (int j = 0;j < kBuffSelectNum;j++) {
				if (i == j)continue;
				selected = false;
				if (m_buffType[i] == m_buffType[j]) {
					selected = true;
					break;
				}
			}
		}
	}
}

bool BuffManager::IsSelect()
{
	if (m_phase >= Phase::Max)return false;
	return true;
}
