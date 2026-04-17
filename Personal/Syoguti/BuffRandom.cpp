#include "BuffRandom.h"

#include "../../Utility/MyRandom.h"
#include "Dxlib.h"

BuffRandom::BuffRandom()
{
}

BuffRandom::~BuffRandom()
{
}

void BuffRandom::Init()
{
    m_buffs.clear();

    // バフを格納
    for (int i = 0; i < static_cast<int>(Buff::BuffType::Max); i++) {
        m_buffs.push_back(static_cast<Buff::BuffType>(i));
    }
}

void BuffRandom::End()
{
}

void BuffRandom::Update()
{
}

void BuffRandom::Draw()
{
}

// ランダムでバフ取得
std::vector<Buff::BuffType> BuffRandom::GetRandomBuffs(int count)
{
    std::vector<Buff::BuffType> result;
    std::vector<Buff::BuffType> temp = m_buffs;

    // 安全対策
    if (count > temp.size()) {
        count = static_cast<int>(temp.size());
    }

    for (int i = 0; i < count; i++) {

        // バフをランダムに決める
        int index = MyRandom::Int(0, static_cast<int>(temp.size()) - 1);

        // 選択されたバフを入れる
        result.push_back(temp[index]);

        // 選んだバフを削除(重複防止)
        temp.erase(temp.begin() + index);
    }

    return result;
}

void BuffRandom::CheckBuff(Buff::BuffType type)
{

    switch (type)
    {
    case Buff::BuffType::HpUpBuff:
        printfDx("回復バフ\n");
        break;
    case Buff::BuffType::AttackUpBuff:
        printfDx("攻撃バフ\n");
        break;
    case Buff::BuffType::TestBuff1:
        printfDx("テスト1バフ\n");
        break;
    case Buff::BuffType::TestBuff2:
        printfDx("テスト2バフ\n");
        break;
    case Buff::BuffType::TestBuff3:
        printfDx("テスト3バフ\n");
        break;
    case Buff::BuffType::TestBuff4:
        printfDx("テスト4バフ\n");
        break;
    case Buff::BuffType::TestBuff5:
        printfDx("テスト5バフ\n");
        break;
    case Buff::BuffType::Max:
        break;
    default:
        printfDx("エラー\n");
        break;
    }

}
