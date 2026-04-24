#pragma once
typedef struct Buff {
public:
	enum class Type {
		Attack,
		Defence,
		CriticalRate,
		CriticalDamage,
		ExpUp,
		Max
	};
	int level[static_cast<int>(Type::Max)];
	void Reset() { for (int& levels : level)levels = 0; }
};
namespace {
	constexpr int kBuffMax = static_cast<int>(Buff::Type::Max);

}