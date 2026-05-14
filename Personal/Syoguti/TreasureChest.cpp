#include "TreasureChest.h"
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include "DxLib.h"
#include "../../Utility/Time.h"
#include "../../System/SoundManager.h"

namespace {

    // 画像のサイズ
    constexpr float kGraphScale = 1.5f;

    // 円の当たり判定の半径
    constexpr float kCircleRadius = 20.0f * kGraphScale;

    // 画像の位置を調整するオフセットYの値
    constexpr int kOffsetPosY = 10;

}

TreasureChest::TreasureChest(ObjectManager* objectMgr) :
	GameObject(objectMgr),
   m_motionCounter(0),
    m_motionFrame(0),
    m_isOpen(false),
    m_isOpened(false),
    m_openedTimer(0.0f),
    m_isSpawned(false)
{
    for (int i = 0; i < kTreasureChestMotionNum; i++) {

        m_graphHandle[i] = -1;
    }

    m_collision = Collision::Circle(GetTransform().position, kCircleRadius);
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

    OpenAnimation();

    // 座標の更新
    m_collision.SetPosition(GetTransform().position);
}

void TreasureChest::Draw()
{

    // 画像の描画
    DrawRotaGraph(static_cast<int>(GetTransform().position.x),
        static_cast<int>(GetTransform().position.y) - kOffsetPosY,
        kGraphScale, 0.0f, m_graphHandle[m_motionFrame],TRUE);

    // 当たり判定の描画
    m_collision.DebugDraw();

}

void TreasureChest::Open()
{
    m_isOpen = true;
    SoundManager::GetInstance().PlaySe(Sound::SE::Chest);
}

void TreasureChest::OpenAnimation()
{
    // 宝箱が開かれていなければreturn
    if (!m_isOpen) return;

     // アニメーションを再生するためのカウンターをプラス
    m_motionCounter++;

    // カウントが5以下ならreturn
    if (m_motionCounter < 5) return;

    // カウンターをリセット
    m_motionCounter = 0;

    // アニメーションを再生
    m_motionFrame++;

    // アニメーションフレームがkTreasureChestMotionNumより小さければreturn
    if (m_motionFrame < kTreasureChestMotionNum) return;

    // アニメーションを止める(宝箱が開いた状態)
    m_motionFrame = kTreasureChestMotionNum - 1;

    // 宝箱が空き終わったのでtrue
    m_isOpened = true;
    
}

