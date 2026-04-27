#include "BuffManager.h"
#include"BuffType.h"
#include"../../Utility/MyRandom.h"
#include<DxLib.h>
#include"../../System/InputManager.h"
#include"../../Utility/MyMath.h"
#include<string>
#include"../../System/PauseManager.h"
#include"PlayerBuff.h"
#include"PlayerStatus.h"
#include"Player.h"
#include"../../Utility/Vector3.h"
#include<string>
#include"../../Utility/Game.h"
namespace{
	const char* const kIconPath = "Resource\\Iccons\\skill_";
	const char* const kPing = ".png";
	const char* const kTextPath = "Resource\\Text\\";
	const char* const kBuffName[kBuffMax] = {
		"ATK",
		"DEF",
		"SPD",
		"CRT",
		"CRD",
		"ALL",
		"EXP",
		"HEAL",
	};
	const char* const kBuffSelectPath = "Resource\\BuffSelect\\";
	const char* const kProceedName[static_cast<int>(BuffManager::Phase::Max)] = {
		"STOP",
		"SELECT",
		"OK",
	};
	const char* const kButtonPath = "Button";
	const char* const kSelectPath = "Resource\\Iccons\\IconSelect.png";
	const char* const kBackPath = "Resource\\Iccons\\IconBack.png";
	constexpr PlayerStatus kBuffs[static_cast<int>(Buff::Type::Max)] = { 
		{0,0,0.1f,0,0,0,0,0},
		{0,0,0,0.1f,0,0,0,0},
		{0,0,0,0,0,0.06f,0,0},
		{0,0,0,0,0,0,10,0},
		{0,0,0,0,0,0,0,0.1f},
		{0,0,0.02f,0.02f,0.02f,0.02f,0.02f,0.02f},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	};
	constexpr int kMaxLevel[kBuffMax] = {5,5,5,5,5,1000,0,0};
	constexpr int kDistance = 200;
	constexpr int kBackHeight = 250;
	constexpr int kTextHeight = 250;
	constexpr int kLevelHeight = 350;
	constexpr int kIconHeight = 150;
	constexpr int kProceedHeight = 500;
	constexpr int kButtonHeight = 550;
	constexpr float kExpUp = 0.5f;

}

BuffManager::BuffManager() :
	m_pPlayer(nullptr),
	m_buffType(),
	m_selected(Buff::Type::Max),
	m_phase(Phase::Max),
	m_proceedHandle(-1),
	m_buttonHandle(-1),
	m_iconHandle(-1),
	m_textHandle(-1),
	m_backHandle(-1),
	m_selectHandle(-1),
	m_select(0),
	m_buff(),
	m_fontHandle(-1)
{
	// アイコン・テキスト画像の読み込み
	std::string path = kIconPath;
	for (int i = 0;i < kBuffMax;i++) {
		path = kIconPath;
		path += kBuffName[i];
		path += kPing;
		m_iconHandle[i] = LoadGraph(path.c_str());
		path = kTextPath;
		path += kBuffName[i];
		path += kPing;
		m_textHandle[i] = LoadGraph(path.c_str());

	}
	for (int i = 0; i < static_cast<int>(Phase::Max); i++) {
		path = kBuffSelectPath;
		path += kProceedName[i];
		path += kPing;
		m_proceedHandle[i] = LoadGraph(path.c_str());
	}
	path = kBuffSelectPath;
	path += kButtonPath;
	path += kPing;
	m_buttonHandle = LoadGraph(path.c_str());
	m_selectHandle = LoadGraph(kSelectPath);
	m_backHandle = LoadGraph(kBackPath);
	m_fontHandle = CreateFontToHandle(NULL, 18, 3, DX_FONTTYPE_EDGE);
	m_buff.Reset();

	m_buff.level[static_cast<int>(Buff::Type::Heal)] = -1;
	m_buff.level[static_cast<int>(Buff::Type::Exp)] = -1;
}

BuffManager::~BuffManager()
{
	for (int& handle:m_iconHandle) {
		DeleteGraph(handle);
	}
	DeleteGraph(m_selectHandle);
	DeleteFontToHandle(m_fontHandle);
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
			m_select = 0;
		}
		break;
	case Phase::Select:
		{
		if (!InputManager::GetInstance().IsPressed(Input::Action::Confirm)) {
			break;
		}
		m_selected = BuffSelect();
		AdaptBuff(m_selected);
		m_phase = Phase::End;
		if (kMaxLevel[static_cast<int>(m_selected)] <= 0)break;
		m_buff.level[static_cast<int>(m_selected)]++;
		break;
		}
	case Phase::End:
		if (!InputManager::GetInstance().IsPressed(Input::Action::Confirm)) {
			break;
		}
		PauseManager::GetInstance().TogglePause();
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
	m_select = (kBuffSelectNum + m_select) % kBuffSelectNum;
	if (!PauseManager::GetInstance().IsPause()) return;
}


void BuffManager::Draw()
{
	//for (int i = 0;i < kBuffSelectNum;i++) {
	//	printfDx("BuffType[%d] : %d\n",i, static_cast<int>(m_buffType[i]));
	//}
	//printfDx("選択中    : %d\n", static_cast<int>(m_select));
	//printfDx("選択段階  : %d\n", static_cast<int>(m_phase));

	if (!IsSelect())return;
	for (int i = 0;i < kBuffSelectNum;i++) {
		// 選択中の場所へ表示
		if(i == m_select&& m_phase == Phase::Select)
		DrawRotaGraph((Game::kScreenWidth * 0.5f) + kDistance * (i-1), kBackHeight, 6, 0, m_selectHandle, TRUE);
		// バフの背景を表示
		DrawRotaGraph((Game::kScreenWidth * 0.5f) + kDistance * (i - 1), kBackHeight, 6, 0, m_backHandle, TRUE);
		if (m_phase >= Phase::Select && IsSelect() && kMaxLevel[static_cast<int>(m_buffType[i])]>0) {
			std::string level = "Lv." + std::to_string(m_buff.level[static_cast<int>(m_buffType[i])]) + " -> Lv." + std::to_string(m_buff.level[static_cast<int>(m_buffType[i])] + 1);
			int offset = -65;
			if (m_buffType[i] == m_selected) {
				level = "Lv." + std::to_string(m_buff.level[static_cast<int>(m_buffType[i])]);
				offset = -25;
			}
			// レベルを表示
			DrawStringToHandle((Game::kScreenWidth * 0.5f+ offset) + kDistance * (i - 1), kLevelHeight, level.c_str(), 0x000000, m_fontHandle);
		}
		// バフの説明テキストを表示
		DrawRotaGraph((Game::kScreenWidth * 0.5f) + kDistance * (i - 1), kTextHeight, 0.03f, 0, m_textHandle[static_cast<int>(m_buffType[i])], TRUE);
		// バフのアイコンを表示
		DrawRotaGraph((Game::kScreenWidth * 0.5f) + kDistance * (i - 1), kIconHeight, 0.15f, 0, m_iconHandle[static_cast<int>(m_buffType[i])], FALSE);
	}

	// 進行テキストの表示
	DrawRotaGraph((Game::kScreenWidth * 0.5f) , kProceedHeight, 0.15f, 0, m_proceedHandle[static_cast<int>(m_phase)], TRUE);
	// 進行ボタンの表示
	DrawRotaGraph((Game::kScreenWidth * 0.5f) , kButtonHeight, 0.8f, 0, m_buttonHandle, TRUE);
}

void BuffManager::BuffSelectStart()
{
	if (!PauseManager::GetInstance().IsPause()) {
		PauseManager::GetInstance().TogglePause();
		PauseManager::GetInstance().SetAlpha(127);
	}
	m_phase = Phase::Start;
	m_buffType[0] = Buff::Type::Max;
	m_buffType[1] = Buff::Type::Max;
	m_buffType[2] = Buff::Type::Max;
	m_selected = Buff::Type::Max;
}
Buff::Type BuffManager::BuffSelect()
{
	return m_buffType[m_select];
}
void BuffManager::RandomBuff()
{

	for (int i = 0;i < kBuffSelectNum;i++) {
		// すでに同じバフが選ばれたかどうか
		bool selected = true;
		// ランダムで抽選されたバフの種類
		int select = 0;
		// 最大レベルでないバフの中で
		// 選ばれていないものがでるまで繰り返す
		while (selected)
		{
			// バフをランダムで抽選
			select = MyRandom::Int(0, static_cast<int>(Buff::Type::Max) - 1);
			m_buffType[i] = static_cast<Buff::Type>(select);
			//if (kMaxLevel[static_cast<int>(m_buffType[i])]<=0)break;
			// 抽選されたバフがが最大レベルの時
			if (m_buff.level[static_cast<int>(m_buffType[i])] >= kMaxLevel[static_cast<int>(m_buffType[i])]&&
				kMaxLevel[static_cast<int>(m_buffType[i])] > 0)continue;
			for (int j = 0;j < kBuffSelectNum;j++) {
				if (i == j)continue;
				// すでに選択されているとき
				if (m_buffType[i] == m_buffType[j]) {
					// 選択されている
					selected = true;
					break;
				}
				// 選択されていないことにする
				selected = false;
			}
		}
	}
}

bool BuffManager::IsSelect()
{
	if (m_phase >= Phase::Max)return false;
	return true;
}

void BuffManager::AdaptBuff(const Buff::Type& buffType)
{
	switch (buffType)
	{
		case Buff::Type::Attack:
		case Buff::Type::Defence:
		case Buff::Type::Speed:
		case Buff::Type::CriticalRate:
		case Buff::Type::CriticalDamage:
		case Buff::Type::All:
		{
			// ステータス強化系はプレイヤーのポインタがないときreturn
			if (!m_pPlayer)return;
			// 永続のバフを付与
			PlayerBuff buff = { kBuffs[static_cast<int>(buffType)],1, false };
			m_pPlayer->AddBuff(buff);
			break;
		}
		case Buff::Type::Exp:
		{
			// 経験値はプレイヤーのポインタがないときreturn
			float exp = m_pPlayer->GetExp() + kExpUp;
			m_pPlayer->SetExp(exp);
			break;
		}
		case Buff::Type::Heal:
		{
			// 回復はプレイヤーのポインタがないときreturn
			if (!m_pPlayer)return;
			float value = m_pPlayer->GetGaugeMaxValue(Player::GaugeType::Hp);
			value *= 0.4f;
			m_pPlayer->Heal(value);
			break;
		}
	default:
		break;
	}
}
