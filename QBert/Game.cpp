#include "Game.h"
#include "MiniginPCH.h"
#include "../Minigin/InputManager.h"
#include "../Minigin/SceneManager.h"
#include "../Minigin/Renderer.h"
#include "../Minigin/ResourceManager.h"
#include "../Minigin/TextComponent.h"
#include "../Minigin/GameObject.h"
#include "../Minigin/Scene.h"
#include "../Minigin/FPSComponent.h"
#include "../Minigin/SubjectComponent.h"
#include "../Minigin/PlayerComponent.h"
#include "../Minigin/LifeComponent.h"
#include "../Minigin/ScoreComponent.h"
#include "../Minigin/ServiceLocator.h"
#include "../Minigin/SoundSystem.h"
#include "GridNodeComponent.h"
#include "QBertComponent.h"
#include <SDL.h>
#include "Command.h"
#include "LevelConstructor.h"
#include "CoilyComponent.h"
#include "GreenEnemyComponent.h"
#include "PurpleEnemyComponent.h"
#include "GameManagerComponent.h"

using namespace dae;

void Game::LoadGame() const
{
	auto scene = SceneManager::GetInstance().CreateScene("QBert");

	std::shared_ptr<GameObject> manager = std::make_shared<GameObject>(scene);
	manager->AddComponent(std::make_shared<GameManagerComponent>(std::weak_ptr<GameObject>(manager)));
	scene.lock()->Add(manager);



}

void Game::Cleanup()
{
	Minigin::Cleanup();
}
