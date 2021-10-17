#include "Game.h"
#include "../Minigin/SceneManager.h"
#include "../Minigin/GameObject.h"

void Game::LoadGame() const
{
	auto scene = SceneManager::GetInstance().CreateScene("EngineTest");
}

void Game::Cleanup()
{
	Minigin::Cleanup();
}
