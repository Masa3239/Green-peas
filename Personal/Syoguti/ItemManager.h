#pragma once

#include<vector>
#include<memory>
#include "ItemBase.h"

class ItemManager
{

public:

	ItemManager();
	~ItemManager() = default;

	void Init();

	void End();

	void Update();

	void Draw();

private:

	std::vector<std::unique_ptr<ItemBase>> m_items;

	int m_hpHealItemGraphHandle;

};

