#include "PlayerStatus.h"
#include<cassert>
PlayerStatus PlayerStatus::operator-() const
{

    return PlayerStatus(-Level,-HP,-Attack,-Defence,-Speed,-Stamina,-CriticalRate,-CriticalDamage);
}

PlayerStatus PlayerStatus::operator+(const PlayerStatus& status) const
{
    return PlayerStatus(
        Level + status.Level,
        HP + status.HP,
        Attack + status.Attack,
        Defence + status.Defence,
        Speed + status.Speed,
        Stamina + status.Stamina,
        CriticalRate + status.CriticalRate,
        CriticalDamage + status.CriticalDamage);
}

PlayerStatus PlayerStatus::operator-(const PlayerStatus& status) const
{
    return PlayerStatus(
        Level - status.Level,
        HP - status.HP,
        Attack - status.Attack,
        Defence - status.Defence,
        Speed - status.Speed,
        Stamina - status.Stamina,
        CriticalRate - status.CriticalRate,
        CriticalDamage - status.CriticalDamage);
}

PlayerStatus PlayerStatus::operator*(const PlayerStatus& status) const
{
    return PlayerStatus(
        Level * status.Level,
        HP * status.HP,
        Attack * status.Attack,
        Defence * status.Defence,
        Speed * status.Speed,
        Stamina * status.Stamina,
        CriticalRate * status.CriticalRate,
        CriticalDamage * status.CriticalDamage);
}

PlayerStatus PlayerStatus::operator/(const PlayerStatus& status) const
{

    return PlayerStatus(
        Level / status.Level,
        HP / status.HP,
        Attack / status.Attack,
        Defence / status.Defence,
        Speed / status.Speed,
        Stamina / status.Stamina,
        CriticalRate / status.CriticalRate,
        CriticalDamage / status.CriticalDamage);
}

PlayerStatus PlayerStatus::operator*(float scale) const
{
    return PlayerStatus(
        Level * scale,
        HP * scale,
        Attack * scale,
        Defence * scale,
        Speed * scale,
        Stamina * scale,
        CriticalRate * scale,
        CriticalDamage * scale);
}
PlayerStatus PlayerStatus::operator/(float scale) const
{
    if (scale == 0)
    {
        assert(false && "Vector3：0除算が行われました");
    }
    return PlayerStatus(
        Level / scale,
        HP / scale,
        Attack / scale,
        Defence / scale,
        Speed / scale,
        Stamina / scale,
        CriticalRate / scale,
        CriticalDamage / scale);
}

PlayerStatus& PlayerStatus::operator+=(const PlayerStatus& status)
{
    Level += status.Level;
    HP += status.HP;
    Attack += status.Attack;
    Defence += status.Defence;
    Speed += status.Speed;
    Stamina += status.Stamina;
    CriticalRate += status.CriticalRate;
    CriticalDamage += status.CriticalDamage;
    return *this;
}

PlayerStatus& PlayerStatus::operator-=(const PlayerStatus& status)
{
    Level -= status.Level;
    HP -= status.HP;
    Attack -= status.Attack;
    Defence -= status.Defence;
    Speed -= status.Speed;
    Stamina -= status.Stamina;
    CriticalRate -= status.CriticalRate;
    CriticalDamage -= status.CriticalDamage;
    return *this;
}

PlayerStatus& PlayerStatus::operator*=(const PlayerStatus& status)
{
    Level *= status.Level;
    HP *= status.HP;
    Attack *= status.Attack;
    Defence *= status.Defence;
    Speed *= status.Speed;
    Stamina *= status.Stamina;
    CriticalRate *= status.CriticalRate;
    CriticalDamage *= status.CriticalDamage;
    return *this;
}

PlayerStatus& PlayerStatus::operator/=(const PlayerStatus& status)
{
    Level /= status.Level;
    HP /= status.HP;
    Attack /= status.Attack;
    Defence /= status.Defence;
    Speed /= status.Speed;
    Stamina /= status.Stamina;
    CriticalRate /= status.CriticalRate;
    CriticalDamage /= status.CriticalDamage;
    return *this;
}

PlayerStatus& PlayerStatus::operator*=(float scale)
{
    Level *= scale;
    HP *= scale;
    Attack *= scale;
    Defence *= scale;
    Speed *= scale;
    Stamina *= scale;
    CriticalRate *= scale;
    CriticalDamage *= scale;
    return *this;
}

PlayerStatus& PlayerStatus::operator/=(float scale)
{
    Level /= scale;
    HP /= scale;
    Attack /= scale;
    Defence /= scale;
    Speed /= scale;
    Stamina /= scale;
    CriticalRate /= scale;
    CriticalDamage /= scale;
    return *this;
}

bool PlayerStatus::operator==(const PlayerStatus& status) const
{
    if(Level != status.Level)return false;
    if(HP != status.HP)return false;
    if(Attack != status.Attack)return false;
    if(Defence != status.Defence)return false;
    if(Speed != status.Speed)return false;
    if(Stamina != status.Stamina)return false;
    if(CriticalRate != status.CriticalRate)return false;
    if(CriticalDamage != status.CriticalDamage)return false;
    return true;
}

bool PlayerStatus::operator!=(const PlayerStatus& status) const
{
    if (Level == status.Level)return false;
    if (HP == status.HP)return false;
    if (Attack == status.Attack)return false;
    if (Defence == status.Defence)return false;
    if (Speed == status.Speed)return false;
    if (Stamina == status.Stamina)return false;
    if (CriticalRate == status.CriticalRate)return false;
    if (CriticalDamage == status.CriticalDamage)return false;
    return true;
}

void PlayerStatus::Reset()
{
    Level =0;
        HP =0;
        Attack =0;
        Defence =0;
        Speed =0;
        Stamina =0;
        CriticalRate =0;
        CriticalDamage = 0;
}
