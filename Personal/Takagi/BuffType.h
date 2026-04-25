#pragma once
typedef struct Buff {
public:
	enum class Type {
		Attack,
		Defence,
		Speed,
		CriticalRate,
		CriticalDamage,
		All,
		Exp,
		Heal,
		Max
	};
	int level[static_cast<int>(Type::Max)];
	void Reset() { for (int& levels : level)levels = 0; }
};
namespace {
	constexpr int kBuffMax = static_cast<int>(Buff::Type::Max);

}