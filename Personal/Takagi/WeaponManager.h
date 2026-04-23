#pragma once
#include<Vector>
#include<memory>
#include"../../Utility/Vector3.h"
#include"Weapon.h"
class Weapon;
class Player;
class EnemyManager;

class WeaponManager
{
public:
	WeaponManager();
	~WeaponManager();

	void Init();
	void End();
	void Update();
	void Draw();
	const void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	void SetObjManager(ObjectManager* objManager) { m_objManager = objManager; }
	void SetEnemyManager(EnemyManager* enemyManager) { m_enemyManager = enemyManager; }
	void Create(const Vector3& pos, int weaponType);
	void CreateRandom(const Vector3& pos);
	bool CheckCanPick();
private:
	std::vector<std::unique_ptr<Weapon>> m_weapons;
	Player* m_pPlayer;
	ObjectManager* m_objManager;
	EnemyManager* m_enemyManager;
	float m_createCount;
};

