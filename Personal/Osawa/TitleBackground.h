#pragma once

#include "../Object/GameObject.h"

class TitleBackground : public GameObject
{
public:

	TitleBackground(ObjectManager* objManager);
	~TitleBackground();

	void Init() override;

	void End() override;

	void Update() override;

	void Draw() override;

private:

	int m_tileGraph;

	float m_scrollPos;
};

