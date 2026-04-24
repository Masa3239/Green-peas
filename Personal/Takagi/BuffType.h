#pragma once
typedef struct Buff {
	enum class Type {
		Attack,
		Defence,
		CriticalDamage,
		CriticalRate,
		ExpUp,
		Max
	};
	int buffLevel[static_cast<int>(Type::Max)];
};