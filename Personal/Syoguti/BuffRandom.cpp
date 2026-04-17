#include "BuffRandom.h"

#include "../../Utility/MyRandom.h"

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

        // ランダムインデックス
        int index = MyRandom::Int(0, static_cast<int>(temp.size()) - 1);

        result.push_back(temp[index]);

        // 重複防止（削除）
        temp.erase(temp.begin() + index);
    }

    return result;
}