#include "TitleBackground.h"
#include <DxLib.h>
#include "../Utility/Time.h"

namespace
{
	const char* const kGraphPath = "Resource\\grass.png";

	constexpr float kScrollSpeed = 50.0f;

	constexpr int kTileSize = 32;
}

TitleBackground::TitleBackground(ObjectManager* objManager) :
	GameObject(objManager),
	m_tileGraph(-1),
	m_scrollPos(0)
{
}

TitleBackground::~TitleBackground()
{
}

void TitleBackground::Init()
{
	m_tileGraph = LoadGraph(kGraphPath);
}

void TitleBackground::End()
{
	DeleteGraph(m_tileGraph);
}

void TitleBackground::Update()
{
	m_scrollPos += kScrollSpeed * Time::GetInstance().GetDeltaTime();

	if (m_scrollPos > 0) m_scrollPos = -kTileSize;
}

void TitleBackground::Draw()
{
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			DrawGraph(m_scrollPos + i * kTileSize, j * kTileSize, m_tileGraph, 0);
		}
	}
}
