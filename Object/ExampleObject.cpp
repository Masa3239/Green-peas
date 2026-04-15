#include "ExampleObject.h"

ExampleObject::ExampleObject(ObjectManager* objManager) :
	GameObject(objManager)	// ここでGameObjectクラスのコンストラクタにもObjectManagerを渡す
{
}

ExampleObject::~ExampleObject()
{
}

void ExampleObject::Init()
{
	// 初期化処理
	// ...
}

void ExampleObject::End()
{
	// 後処理
	// ...
}

void ExampleObject::Update()
{
	// 更新処理
	// ...
}

void ExampleObject::Draw()
{
	// 描画処理
	// ...
}
