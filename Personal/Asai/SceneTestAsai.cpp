#include "SceneTestAsai.h"
#include <DxLib.h>
#include"../Asai/Camera.h"
#include"../../Utility/Transform.h"
#include"../../Utility/Time.h"
#include"../Asai/UIManager.h"

UIManager* uiMgr;

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

}

void SceneTestAsai::End()
{
}

SceneBase* SceneTestAsai::Update()
{

	if (CheckHitKey(KEY_INPUT_1)) {

		transform.position.x++;
		transform.position.y++;

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
	uiMgr->DebugDraw();

	//printfDx("x %f\n", transform.position.x);
	//printfDx("y %f\n",transform.position.y);

	printfDx("SceneTestAsai\n");
}
