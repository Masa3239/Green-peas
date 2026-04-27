#include "Boomerang.h"
//#include"../../System/InputPad.h"
#include"RadToPos.h"
#include"../../Utility/Time.h"
#include"../../Utility/Color.h"
#include"../Osawa/Enemy/EnemyManager.h"
#include"../../System/InputManager.h"

namespace {
    constexpr float kSpeed = 50000;
    constexpr float kDeccel = kSpeed*1.5f;
    constexpr float kCatch = 25;
    constexpr float kCatchDistance = kCatch*kCatch;
    constexpr float kColRadius = 20;
    constexpr float kGraphScale = 1.4f;
    constexpr PlayerStatus kStatus = { 0,0,3,0,0,0,30,6 };
    //const char* const kFilePath = "Resource\\Boomerang.png";
    const char* const kGraphPath = "Resource\\Hammer.png";
    constexpr float kRotationSpeed = 1080;
    constexpr float kAttackInterval = 0.3f;

}

Boomerang::Boomerang(ObjectManager* objManager):
    Weapon(objManager),
    m_attack(),
    m_speed(0),
    m_circle(Collision::Circle(GetTransform().position,kColRadius)),
    m_drawAngle(0)
{
    m_attack.Reset();
    m_weaponStatus = kStatus;
    m_graphHandle = -1;
    m_graphHandle = LoadGraph(kGraphPath);
    m_scale = 1;
    m_active = true;
    m_chargeFlag = false;
    m_camUpdate = true;
}

Boomerang::~Boomerang()
{
    DeleteGraph(m_graphHandle);
}

void Boomerang::Init()
{
}

void Boomerang::End()
{
}

void Boomerang::Update()
{
    float time = Time::GetInstance().GetDeltaTime();
    // 移動量を格納する変数
    Vector3 moveVec = { 0.0f,0.0f,0.0f };
    m_speed -= kDeccel * time;
    // 移動速度がある時
    if (m_speed > 0) {
    }
    else {
        Vector3 rad = m_attack.position - GetTransform().position;
        m_attack.rotation.z = atan2(rad.y, rad.x);

        float distance = 0;
        distance = (rad.x * rad.x) + (rad.y * rad.y);
        if (distance < kCatchDistance) {
            m_attackFlag = false;
        }
    }
    if (m_attackFlag) {
        moveVec = RadToPos(m_attack.rotation.z, m_speed * time/**MyMath::Sign(m_speed)*/);
        m_attack.position += moveVec * time;
        m_drawAngle += kRotationSpeed * time;
    }
    else {
        m_attack = GetTransform();
        m_drawAngle = 0;
    }
    m_circle.SetPosition(m_attack.position);
    m_circle.SetRadius(kColRadius * m_scale);
    if (!m_catch)return;
    m_attackInterval += time;
    if (m_attackInterval >= kAttackInterval) {
        m_attackInterval = 0;
        m_pEnemyMgr->ResetEnemyDamageFlag(Weapon::Boomerang, 0);
    }
}

void Boomerang::Draw()
{
    if (!m_active&&!m_attackFlag)return;

    //DrawCircle(m_attack.position.x, m_attack.position.y, kColRadius*m_scale, Color::kMagenta);
   /* printfDx("ぼーーーーーーーーー\n");
    printfDx("m_tramsform.x : %f\n", m_attack.position.x);
    printfDx("m_tramsform.y : %f\n", m_attack.position.y);
    printfDx("m_tramsform.z : %f\n", m_attack.position.z);
    Vector3 debug = RadToPos(m_attack.rotation.z, 15, m_attack.position);
    DrawCircle(debug.x, debug.y, 5, Color::kGreen);*/
    DrawRotaGraph(m_attack.position.x, m_attack.position.y, kGraphScale*m_scale
        , m_drawAngle * MyMath::ToRadian, m_graphHandle, TRUE);
    m_circle.DebugDraw();
    m_catchCol.DebugDraw();
}

bool Boomerang::Attack()
{
    if (m_attackFlag)return false;
    if (!InputManager::GetInstance().IsPressed(Input::Action::Attack))return false;
    m_pEnemyMgr->ResetEnemyDamageFlag(Weapon::Boomerang, 0);
    m_attack.position = GetTransform().position;
    m_attack.rotation.z = GetTransform().rotation.z;
    m_speed = kSpeed;
    m_attackFlag = true;
    return true;
}

bool Boomerang::CheckAttack()
{
    return m_attackFlag;
}

void Boomerang::CheckCollision()
{
    if (!m_pEnemyMgr)return;
    if (!m_attackFlag)return;
    
    float damage = 0;
    damage = m_playerStatus.Attack * m_weaponStatus.Attack;
    float criticalRate = m_playerStatus.CriticalRate + m_weaponStatus.CriticalRate;
    float criticalDamage = m_weaponStatus.CriticalDamage * m_playerStatus.CriticalDamage;
    //m_pEnemyMgr->CheckHitEnemies(m_circle, damage);
    //m_pEnemyMgr->CheckHitEnemies(m_circle, damage, criticalRate, criticalDamage);
    m_pEnemyMgr->CheckHitEnemies(m_circle, damage, criticalRate, criticalDamage, Weapon::Boomerang, 0);

}
