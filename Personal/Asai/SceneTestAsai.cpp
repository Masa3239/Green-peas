#include "SceneTestAsai.h"
#include <DxLib.h>
#include"../Asai/Camera.h"
#include"../../Utility/Transform.h"
#include"../../Utility/Time.h"
#include"../Asai/UIManager.h"
#include"../Asai/Arrow.h"
#include"../Asai/FireBall.h"
#include"../Asai/Minimap.h"
#include"../Asai/Thunder.h"
#include"../Osawa/Enemy/EnemyManager.h"
#include"../Takagi/Player.h"
#include"../Kimura/Map/Map.h"
#include"../Syoguti/ItemManager.h"
#include"../Takagi/WeaponManager.h"
#include"../Takagi/BuffManager.h"
#include"../../System/PauseManager.h"
#include"../Takagi/Warrior.h"
#include"../Takagi/Hunter.h"
#include"../Takagi/Wizard.h"
#include"../Osawa/PauseMenu.h"
#include"../Syoguti/ChestManager.h"

UIManager* uiMgr;
Arrow* arrow;
FireBall* fire;
Camera* camera;
Thunder* thunder;
ItemManager* ItemMgr;
EnemyManager* enemyMgr;
Player* pPlayer;
Map* map;
WeaponManager* weaponMgr;
BuffManager* buffMgr;
PauseMenu* pause;
ChestManager* chestMgr;
Transform transform;

SceneTestAsai::SceneTestAsai()
{
}

SceneTestAsai::~SceneTestAsai()
{
}

void SceneTestAsai::Init()
{

	pPlayer = new Player(GetObjectManager());
	switch (GetCarryOver().characterJob)
	{
	case Character::Job::Warrior:
		pPlayer = new Warrior(GetObjectManager());
		break;
	case Character::Job::Hunter:
		pPlayer = new Hunter(GetObjectManager());
		break;
	case Character::Job::Wizard:
		pPlayer = new Wizard(GetObjectManager());
		break;
	default:
		pPlayer = new Warrior(GetObjectManager());
		break;
	}

	pPlayer->Init();

	uiMgr = new UIManager();
	uiMgr->Init();

	arrow = new Arrow(GetObjectManager());
	arrow->Init();

	fire = new FireBall(GetObjectManager());
	fire->Init();

	thunder = new Thunder(GetObjectManager());
	thunder->Init();

	map = new Map();
	map->Init();

	camera = new Camera();
	camera->Init();
	camera->SetMap(map);
	camera->GenerateWorldScreen();

	ItemMgr = new ItemManager();
	ItemMgr->SetObjectManager(GetObjectManager());
	ItemMgr->SetPlayer(pPlayer);
	ItemMgr->Init();

	enemyMgr = new EnemyManager(GetObjectManager());
	enemyMgr->Init();
	enemyMgr->SetPlayer(pPlayer);
	enemyMgr->SetUIManager(uiMgr);
	
	weaponMgr = new WeaponManager();
	weaponMgr->SetObjManager(GetObjectManager());
	weaponMgr->SetPlayer(pPlayer);
	weaponMgr->Init();

	chestMgr = new ChestManager();
	chestMgr->SetObjectManager(GetObjectManager());
	chestMgr->Init();

	buffMgr = new BuffManager();
	buffMgr->SetPlayer(pPlayer);
	buffMgr->Init();

	pause = new PauseMenu();
	pause->Init();

	pPlayer->SetCamera(camera);
	pPlayer->SetEnemyManager(enemyMgr);
	pPlayer->SetItemManager(ItemMgr);
	pPlayer->SetBuffManager(buffMgr);
	thunder->SetEnemyManager(enemyMgr);
	//pPlayer->SetWeapon()

	uiMgr->SetEnemyManager(enemyMgr);
	uiMgr->GenerateMinimap(camera, map);
	uiMgr->SetPlayer(pPlayer);
	uiMgr->SetItemManager(ItemMgr);

	PauseManager::GetInstance().SetObjectManager(GetObjectManager());

}

void SceneTestAsai::End()
{
	pPlayer->End();
}

SceneBase* SceneTestAsai::Update()
{

	uiMgr->SetPlayer(pPlayer);
	uiMgr->Update();

	ItemMgr->Update();

	map->Update();
	pPlayer->Update();
	//thunder->Update();

	//enemyMgr->Update();

	if (CheckHitKey(KEY_INPUT_1)) {
		transform.position.x++;
		transform.position.y++;
		transform.rotation.z += 0.1f;
		//pPlayer->Damage(1);
		//camera->StartDamage(1.0f);
		//thunder->SetScale(transform.rotation.z);
		fire->Shot(pPlayer->GetTransform());
	}

	if (CheckHitKey(KEY_INPUT_2)) {

		uiMgr->CreatePopUpText(transform.position, 5, PopUpUI::TextType::Critical);
		thunder->Shot(pPlayer->GetTransform());
		ItemMgr->Create(ItemBase::ItemType::Heal, pPlayer->GetTransform().position);

	}
	if (CheckHitKey(KEY_INPUT_3)) {

		enemyMgr->GenerateEnemy(EnemyManager::EnemyType::Miniboss, 1);

	}

	if (CheckHitKey(KEY_INPUT_0)) {
		Time::GetInstance().SetTimeScale(0);
	}
	else {
		Time::GetInstance().SetTimeScale(1);
	}
	
	printfDx(" deg %f\n", MyMath::RadToDeg(transform.rotation.z));
	printfDx(" rad %f\n", transform.rotation.z);

	//arrow->DebugDraw();

	//thunder->DebugDraw();

	printfDx("%f", Time::GetInstance().GetDeltaTime());

	return this;

}

void SceneTestAsai::Draw()
{

	printfDx("x %f\n", transform.position.x);
	printfDx("y %f\n",transform.position.y);

	printfDx("SceneTestAsai\n");

	fire->DebugDraw();

}

void SceneTestAsai::PreDraw()
{

	SetDrawScreen(camera->GetWorldScreen());
	ClearDrawScreen();
	map->Draw();

}

void SceneTestAsai::PostDraw()
{
	uiMgr->WorldDraw();
	SetDrawScreen(DX_SCREEN_BACK);
	camera->Draw();
	uiMgr->ScreenDraw();

	//clsDx();

	thunder->DebugDraw();
	//camera->DebugDraw();

}
