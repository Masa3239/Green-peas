#pragma once
typedef struct Buff {
	enum class Type {
		Attack,
		Defence,
		CriticalRate,
		CriticalDamage,
		ExpUp,
		Max
	};
	int buffLevel[static_cast<int>(Type::Max)];
};
namespace {
	constexpr int kBuffMax = static_cast<int>(Buff::Type::Max);

}