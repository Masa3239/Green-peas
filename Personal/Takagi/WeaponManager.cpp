#include "WeaponManager.h"
#include<cassert>
#include"Player.h"
#include"Weapon.h"
#include"Sword.h"
#include"Katana.h"
#include"Boomerang.h"
#include"Bow.h"
#include"FlameWand.h"
#include"ThunderWand.h"
#include<vector>
#include<memory>
#include"../../Object/GameObject.h"
#include"../../System/ObjectManager.h"
#include"../../Utility/Time.h"
#include"../../Utility/MyRandom.h"
#include"../../Chara/Collision.h"
#include"../../System/InputPad.h"
#include"../../Utility/Input.h"
namespace {
	constexpr float kCreatae = 1.5f;
}
WeaponManager::WeaponManager():
	m_weapons(),
	m_pPlayer(nullptr)
{
}

WeaponManager::~WeaponManager()
{
}

void WeaponManager::Init()
{
	//// プレイヤーのポインタがないとき警告
	//if (!m_pPlayer) {

	//	assert(false && "playerのポインタがない");
	//}
	
	//m_weapons.push_back(std::make_unique<FlameWand>(m_objManager));
	//m_weapons.push_back(std::make_unique<Boomerang>(m_objManager));
	//for (auto& weapons : m_weapons) {
	//	weapons->SetEnemyManager(m_enemyManager);
	//	weapons->SetChatch(true);
	//}
	//m_pPlayer->SetWeapon(m_weapons[0].get());
	//m_pPlayer->SetWeapon(m_weapons[1].get());
	int weaponType = Weapon::Sword;
	switch (m_pPlayer->GetPlayerJob())
	{
	case Character::Job::Warrior:
		weaponType = Weapon::Sword;
		break;
	case Character::Job::Hunter:
		weaponType = Weapon::Bow;
		break;
	case Character::Job::Wizard:
		weaponType = Weapon::Flame;
		break;
	default:
		break;
	}
	Create(m_pPlayer->GetTransform().position, weaponType);
	CheckCanPick();



}

void WeaponManager::End()
{
}

void WeaponManager::Update()
{
	for (auto& weapon : m_weapons) {
		weapon->UpdateCatchCol();
	}
	float time = Time::GetInstance().GetDeltaTime();
	m_createCount += time;
	//if (Input::IsPressed(PAD_INPUT_5)) {
	//	m_createCount = 0;
	//	//int weaponType = Weapon::Bow;
	//	int weaponType = MyRandom::Int(0, Weapon::Max-1);
	//	Create(m_pPlayer->GetTransform().position, weaponType);
	//}
	if (Pad::IsPressed(Pad::Button::B)) {
		CheckCanPick();
	}
}

void WeaponManager::Draw()
{
	for (auto& weapon : m_weapons) {
		weapon->Draw();
	}
}

void WeaponManager::Create(const Vector3& pos, int weaponType)
{
	switch (weaponType)
	{
	case Weapon::Sword:
		m_weapons.push_back(std::make_unique<Sword>(m_objManager));
		break;
	case Weapon::Bow:
		m_weapons.push_back(std::make_unique<Bow>(m_objManager));
		break;
	case Weapon::Boomerang:
		m_weapons.push_back(std::make_unique<Boomerang>(m_objManager));
		break;
	case Weapon::Katana:
		m_weapons.push_back(std::make_unique<Katana>(m_objManager));
		break;
	case Weapon::Flame:
		m_weapons.push_back(std::make_unique<FlameWand>(m_objManager));
		break;
	case Weapon::Volt:
		m_weapons.push_back(std::make_unique<ThunderWand>(m_objManager));
		break;
	default:
		break;
	}
	m_weapons[m_weapons.size()-1]->SetEnemyManager(m_enemyManager);
	m_weapons[m_weapons.size()-1]->Init();
	m_weapons[m_weapons.size()-1]->SetPos(pos);
	m_weapons[m_weapons.size()-1]->SetChatch(false);

}

void WeaponManager::CreateRandom(const Vector3& pos)
{
	int weaponType = 0;
	weaponType = MyRandom::Int(0, Weapon::Max - 1);
	Create(pos, weaponType);
}

bool WeaponManager::CheckCanPick()
{
	if (!m_pPlayer)return false;
	bool pick = false;
	for (auto& weapons : m_weapons) {
		if (weapons->GetChatch())continue;
		pick = m_pPlayer->GetCircle().CheckCollision(weapons->GetCatchCol());
		if (!pick)continue;
		m_pPlayer->SetWeapon(weapons.get());
		weapons->SetChatch(true);
		return true;
	}

	return false;
}
