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

UIManager* uiMgr;
Arrow* arrow;
FireBall* fire;
Camera* camera;
Minimap* miniMap;
Thunder* thunder;
ItemManager* ItemMgr;
EnemyManager* enemyMgr;
Player* pPlayer;
Map* map;

Transform transform;

SceneTestAsai::SceneTestAsai()
{
}

SceneTestAsai::~SceneTestAsai()
{
}

void SceneTestAsai::Init()
{

	uiMgr = new UIManager();
	uiMgr->Init();

	pPlayer = new Player(GetObjectManager());
	pPlayer->Init();

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

	miniMap = new Minimap();
	miniMap->SetCamera(camera);
	miniMap->SetPlayer(pPlayer);
	miniMap->SetItemManager(ItemMgr);
	miniMap->Init();

	enemyMgr = new EnemyManager(GetObjectManager());
	enemyMgr->Init();
	enemyMgr->SetPlayer(pPlayer);
	enemyMgr->SetUIManager(uiMgr);

	pPlayer->SetCamera(camera);
	pPlayer->SetEnemyManager(enemyMgr);
	pPlayer->SetItemManager(ItemMgr);

	thunder->SetEnemyManager(enemyMgr);

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

	enemyMgr->Update();

	if (CheckHitKey(KEY_INPUT_1)) {
		transform.position.x++;
		transform.position.y++;
		transform.rotation.z += 0.1f;
		pPlayer->Damage(1);
		thunder->SetScale(transform.rotation.z);
	}

	if (CheckHitKey(KEY_INPUT_2)) {

		uiMgr->CreateDamagePopUpText(transform.position,5);
		thunder->Shot(pPlayer->GetTransform());
		//ItemMgr->Create(ItemBase::ItemType::Heal, pPlayer->GetTransform().position);
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
	miniMap->Draw();

	//clsDx();

	thunder->DebugDraw();

}
