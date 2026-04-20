#include "SceneTestAsai.h"
#include <DxLib.h>
#include"../Asai/Camera.h"
#include"../../Utility/Transform.h"
#include"../../Utility/Time.h"
#include"../Asai/UIManager.h"
#include"../Asai/Arrow.h"
#include"../Asai/FireBall.h"
#include"../Asai/Minimap.h"

#include"../Takagi/Player.h"
#include"../Kimura/Map/Map.h"

UIManager* uiMgr;
Arrow* arrow;
FireBall* fire;
Camera* camera;
Minimap* miniMap;

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

	map = new Map();
	map->Init();

	camera = new Camera();
	camera->Init();
	camera->SetMap(map);
	camera->GenerateWorldScreen();

	miniMap = new Minimap();
	miniMap->Init();

	pPlayer->SetCamera(camera);

}

void SceneTestAsai::End()
{
}

SceneBase* SceneTestAsai::Update()
{

	uiMgr->SetPlayer(pPlayer);
	uiMgr->Update();

	pPlayer->Update();

	fire->Update();

	if (CheckHitKey(KEY_INPUT_1)) {
		transform.position.x++;
		transform.position.y++;
		transform.rotation.z += 0.1f;
		pPlayer->Damage(1);
		fire->SetScale(transform.rotation.z);
	}

	if (CheckHitKey(KEY_INPUT_2)) {

		uiMgr->CreateDamagePopUpText(transform.position,5);
		fire->Shot(pPlayer->GetTransform());

	}

	if (CheckHitKey(KEY_INPUT_0)) {
		Time::GetInstance().SetTimeScale(0);
	}
	else {
		Time::GetInstance().SetTimeScale(1);
	}
	
	printfDx(" deg %f\n", MyMath::RadToDeg(transform.rotation.z));
	printfDx(" rad %f\n", transform.rotation.z);

	arrow->DebugDraw();

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

	SetDrawScreen(DX_SCREEN_BACK);

	camera->Draw();
	miniMap->Draw();

}
