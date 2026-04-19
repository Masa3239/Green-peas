#include "Boomerang.h"
#include"../../System/InputPad.h"
#include"RadToPos.h"
#include"../../Utility/Time.h"
#include"../../Utility/Color.h"
#include"../Osawa/Enemy/EnemyManager.h"

namespace {
    constexpr float kSpeed = 30000;
    constexpr float kDeccel = kSpeed*0.7f;
    constexpr float kCatch = 15;
    constexpr float kCatchDistance = kCatch*kCatch;
    constexpr float kColRadius = 15;
    constexpr PlayerStatus kStatus = { 0,0,10,0,0,0,10,2 };
}

Boomerang::Boomerang(ObjectManager* objManager):
    Weapon(objManager),
    m_attack(),
    m_speed(0),
    m_circle(Collision::Circle(GetTransform().position,kColRadius))
{
    m_attack.Reset();
    m_weaponStatus = kStatus;
}

Boomerang::~Boomerang()
{
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
        m_attack.rotation.z = atan2(-rad.x, rad.y) + DX_PI_F;

        float distance = 0;
        distance = (rad.x * rad.x) + (rad.y * rad.y);
        if (distance < kCatchDistance) {
            m_attackFlag = false;
        }
    }
    if (m_attackFlag) {
        moveVec = RadToPos(m_attack.rotation.z, m_speed*time/**MyMath::Sign(m_speed)*/);
        m_attack.position += moveVec * time;
    }
    else {
        m_attack = GetTransform();
    }
    m_circle.SetPosition(m_attack.position);
}

void Boomerang::Draw()
{
    DrawCircle(m_attack.position.x, m_attack.position.y, 10, Color::kMagenta);
    printfDx("ぼーーーーーーーーー\n");
    printfDx("m_tramsform.x : %f\n", m_attack.position.x);
    printfDx("m_tramsform.y : %f\n", m_attack.position.y);
    printfDx("m_tramsform.z : %f\n", m_attack.position.z);
    Vector3 debug = RadToPos(m_attack.rotation.z, 15, m_attack.position);
    DrawCircle(debug.x, debug.y, 5, Color::kGreen);
}

void Boomerang::Attack()
{
    if (m_attackFlag)return;
    if (!Pad::IsPressed(Pad::Button::X))return;
    m_attack.position = GetTransform().position;
    m_attack.rotation.z = GetTransform().rotation.z;
    m_speed = kSpeed;
    m_attackFlag = true;
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
    damage = m_playerStatus.Attack + m_weaponStatus.Attack;
    float criticalRate = m_playerStatus.CriticalRate + m_weaponStatus.CriticalRate;
    if (GetRand(100) < criticalRate) {
        damage *= m_weaponStatus.CriticalDamage;
    }
    m_pEnemyMgr->CheckHitEnemies(m_circle, damage);
}
