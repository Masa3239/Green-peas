#include "TreasureChest.h"
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include "DxLib.h"
#include "../../Utility/Time.h"



TreasureChest::TreasureChest(ObjectManager* objectMgr) :
	GameObject(objectMgr)
{

}

TreasureChest::~TreasureChest()
{
}

void TreasureChest::Init()
{


}

void TreasureChest::End()
{


	
}

void TreasureChest::Update()
{
}

void TreasureChest::Draw()
{

    auto pos = GetTransform().position;

    DrawGraph(
        static_cast<int>(pos.x),
        static_cast<int>(pos.y),
        m_graphHandle[m_frame],
        TRUE
    );
}
