#include "SceneTestAsai.h"
#include <DxLib.h>
#include"../Asai/Camera.h"
#include"../../Utility/Transform.h"
#include"../../Utility/Time.h"
#include"../Asai/UIManager.h"
#include"../Asai/Arrow.h"

#include"../Takagi/Player.h"

UIManager* uiMgr;
Arrow* arrow;

Player* pPlayer;

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

}

void SceneTestAsai::End()
{
}

SceneBase* SceneTestAsai::Update()
{

	uiMgr->SetPlayer(pPlayer);
	uiMgr->Update();

	if (CheckHitKey(KEY_INPUT_1)) {
		transform.position.x++;
		transform.position.y++;

		pPlayer->Damage(1);
	}

	if (CheckHitKey(KEY_INPUT_2)) {

		uiMgr->CreateDamagePopUpText(transform.position,5);

	}

	if (CheckHitKey(KEY_INPUT_0)) {
		Time::GetInstance().SetTimeScale(0);
	}
	else {
		Time::GetInstance().SetTimeScale(1);
	}
	
	printfDx("%f", Time::GetInstance().GetDeltaTime());

	return this;

}

void SceneTestAsai::Draw()
{

	uiMgr->ScreenDraw();
	uiMgr->WorldDraw();
	uiMgr->DebugDraw();

	arrow->DebugDraw();

	//printfDx("x %f\n", transform.position.x);
	//printfDx("y %f\n",transform.position.y);

	printfDx("SceneTestAsai\n");

}
