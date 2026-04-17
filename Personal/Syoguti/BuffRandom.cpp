#include "BuffRandom.h"

#include "../../Utility/MyRandom.h"
#include "../../Utility/Color.h"
#include "Dxlib.h"

namespace {

    // テキストの座標
    constexpr int kLeftBuffTextPosX = 50;
    constexpr int kCenterBuffTextPosX = 300;
    constexpr int kRightBuffTextPosX = 500;
    constexpr int kBuffTextPosY = 300;

}

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

void BuffRandom::Draw(const std::vector<Buff::BuffType>& buffs)
{

    
    for (int i = 0; i < buffs.size(); i++) {

        int drawX = 0;
        int drawY = kBuffTextPosY;

        if (i == 0) {

            drawX = kLeftBuffTextPosX;
        }
        else if (i == 1) {

            drawX = kCenterBuffTextPosX;
        }
        else if (i == 2) {

            drawX = kRightBuffTextPosX;
        }
        const char* text = GetBuffText(buffs[i]);

        DrawFormatString(drawX, drawY, Color::kBlue, "%s", text);
    }
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

const char* BuffRandom::GetBuffText(Buff::BuffType type)
{

    // 引数で渡されたバフのtypeを調べる
    // returnで表示する文字を返す
    switch (type)
    {
    case Buff::BuffType::HpUpBuff:
        return "HPを回復するバフ";
    case Buff::BuffType::AttackUpBuff:
        return "攻撃力";
    case Buff::BuffType::TestBuff1:
        return "Test";
    case Buff::BuffType::TestBuff2:
        return "テスト2";
    case Buff::BuffType::TestBuff3:
        return "テスト3";
    case Buff::BuffType::TestBuff4:
        return "テスト4";
    case Buff::BuffType::TestBuff5:
        return "テスト5";
    case Buff::BuffType::Max:
        return "";
    default:
        return "エラー";
    }
}
    //m_level[static_cast<int>(type)] += 1;
