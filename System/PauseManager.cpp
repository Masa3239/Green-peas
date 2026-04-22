#include "PauseManager.h"

PauseManager& PauseManager::GetInstance()
{
	static PauseManager instance;
	
	return instance;
}

void PauseManager::Update()
{

}

void PauseManager::OnPause()
{

}
