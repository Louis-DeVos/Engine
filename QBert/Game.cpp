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
#include "../Minigin/PlayerDeathObserver.h"
#include "../Minigin/LifeComponent.h"
#include "../Minigin/ScoreComponent.h"
#include "../Minigin/ScoreObserver.h"
#include "../Minigin/ServiceLocator.h"
#include "../Minigin/SoundSystem.h"
#include "GraphComponent.h"
#include "QBertComponent.h"
#include <SDL.h>
#include "Command.h"
#include "LevelConstructor.h"
#include "CoilyComponent.h"
#include "GreenEnemyComponent.h"
#include "PurpleEnemyComponent.h"

using namespace dae;

void Game::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	std::shared_ptr<dae::GameObject> go = std::make_shared<GameObject>();
	std::shared_ptr<RenderComponent> render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(go));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.jpg"));
	go->AddComponent(render);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(go));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("logo.png"));
	go->AddComponent(render);
	go->SetPosition(216, 180);
	scene.Add(go);

	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", font, std::weak_ptr<GameObject>(go)));
	go->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(go)));
	go->SetPosition(80, 20);
	scene.Add(go);

	std::shared_ptr<dae::GameObject> fps = std::make_shared<GameObject>();
	fps->AddComponent(std::make_shared<FPSComponent>(std::weak_ptr<GameObject>(fps)));
	fps->AddComponent(std::make_shared<TextComponent>(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), std::weak_ptr<GameObject>(fps)));
	fps->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(fps)));
	scene.Add(fps);

	std::shared_ptr<dae::GameObject> lifeCounter = std::make_shared<GameObject>();
	lifeCounter->AddComponent(std::make_shared<LifeComponent>(std::weak_ptr<GameObject>(lifeCounter)));
	lifeCounter->AddComponent(std::make_shared<TextComponent>(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), std::weak_ptr<GameObject>(lifeCounter)));
	lifeCounter->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(lifeCounter)));
	lifeCounter->SetPosition(200, 0);
	scene.Add(lifeCounter);

	std::shared_ptr<dae::GameObject> lifeCounter2 = std::make_shared<GameObject>();
	lifeCounter2->AddComponent(std::make_shared<LifeComponent>(std::weak_ptr<GameObject>(lifeCounter2)));
	lifeCounter2->AddComponent(std::make_shared<TextComponent>(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), std::weak_ptr<GameObject>(lifeCounter2)));
	lifeCounter2->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(lifeCounter2)));
	lifeCounter2->SetPosition(200, 10);
	scene.Add(lifeCounter2);

	std::shared_ptr<dae::GameObject> scoreCounter = std::make_shared<GameObject>();
	scoreCounter->AddComponent(std::make_shared<ScoreComponent>(std::weak_ptr<GameObject>(scoreCounter)));
	scoreCounter->AddComponent(std::make_shared<TextComponent>(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), std::weak_ptr<GameObject>(scoreCounter)));
	scoreCounter->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(scoreCounter)));
	scoreCounter->SetPosition(300, 0);
	scene.Add(scoreCounter);

	std::shared_ptr<dae::GameObject> scoreCounter2 = std::make_shared<GameObject>();
	scoreCounter2->AddComponent(std::make_shared<ScoreComponent>(std::weak_ptr<GameObject>(scoreCounter2)));
	scoreCounter2->AddComponent(std::make_shared<TextComponent>(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), std::weak_ptr<GameObject>(scoreCounter2)));
	scoreCounter2->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(scoreCounter2)));
	scoreCounter2->SetPosition(300, 10);
	scene.Add(scoreCounter2);

	std::shared_ptr<dae::GameObject> QBert = std::make_shared<GameObject>();
	//QBert->AddComponent(new RenderComponent{ QBert });
	//render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.jpg"));
	std::shared_ptr<QBertComponent> qbertComponent = std::make_shared<QBertComponent>(QBert);
	QBert->AddComponent(qbertComponent);
	QBert->AddComponent(std::make_shared<SubjectComponent>(QBert));
	render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(QBert));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("QBert.png"));
	QBert->AddComponent(render);
	QBert->getComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<PlayerDeathObserver>(lifeCounter->getComponent<LifeComponent>()));
	QBert->getComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<ScoreObserver>(scoreCounter->getComponent<ScoreComponent>()));

	std::shared_ptr<dae::GameObject> QBert2 = std::make_shared<GameObject>();
	//QBert->AddComponent(new RenderComponent{ QBert });
	//render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.jpg"));
	std::shared_ptr<QBertComponent> qbert2Component = std::make_shared<QBertComponent>(QBert2);
	QBert2->AddComponent(qbert2Component);
	QBert2->AddComponent(std::make_shared<SubjectComponent>(QBert2));
	render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(QBert2));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("QBert.png"));
	QBert2->AddComponent(render);
	QBert2->getComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<PlayerDeathObserver>(lifeCounter->getComponent<LifeComponent>()));
	QBert2->getComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<ScoreObserver>(scoreCounter->getComponent<ScoreComponent>()));





	std::shared_ptr<dae::GameObject> Coily = std::make_shared<GameObject>();
	Coily->AddComponent(std::make_shared<CoilyComponent>(Coily));
	render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(Coily));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Egg.png"));
	Coily->AddComponent(render);



	std::shared_ptr<dae::GameObject> Slick = std::make_shared<GameObject>();
	Slick->AddComponent(std::make_shared<GreenEnemyComponent>(Slick));
	render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(Slick));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Slick.png"));
	Slick->AddComponent(render);

	std::shared_ptr<dae::GameObject> ugg = std::make_shared<GameObject>();
	ugg->AddComponent(std::make_shared<PurpleEnemyComponent>(ugg,1));
	render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(ugg));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Wrongway.png"));
	ugg->AddComponent(render);

	
	//std::shared_ptr<dae::GameObject> Node = std::make_shared<GameObject>();
	//render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(Node));
	//render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Block_1.png"));
	//Node->AddComponent(render);
	//Node->AddComponent(std::make_shared<GridNodeComponent>(Node));
	//Node->SetPosition(320, 100);
	//

	//std::shared_ptr<dae::GameObject> Node1 = std::make_shared<GameObject>();
	//render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(Node1));
	//render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Block_1.png"));
	//Node1->AddComponent(render);
	//Node1->AddComponent(std::make_shared<GridNodeComponent>(Node1));
	//Node1->SetPosition(336, 124);
	//

	//std::shared_ptr<dae::GameObject> Node2 = std::make_shared<GameObject>();
	//render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(Node2));
	//render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Block_1.png"));
	//Node2->AddComponent(render);
	//Node2->AddComponent(std::make_shared<GridNodeComponent>(Node2));
	//Node2->SetPosition(304, 124);
	//

	//

	//scene.Add(Node);
	//scene.Add(Node1);
	//scene.Add(Node2);

	LevelConstructor levelConstructor{};

	auto node = levelConstructor.CreateLevel(scene, "../Data/Level1.txt");


	qbertComponent->SetLocation(node);
	qbert2Component->SetLocation(node.lock()->GetConnection(Position::BottomLeft));
	Coily->getComponent<CoilyComponent>().lock()->SetTarget(QBert);
	Coily->getComponent<CoilyComponent>().lock()->SetLocation(node.lock()->GetConnection(Position::BottomRight));
	Slick->getComponent<GreenEnemyComponent>().lock()->SetLocation(node.lock()->GetConnection(Position::BottomLeft));
	ugg->getComponent<PurpleEnemyComponent>().lock()->SetLocation(node.lock()->GetLastConnection(Position::BottomLeft));

	scene.Add(QBert);
	//scene.Add(QBert2);
	scene.Add(Coily);
	scene.Add(Slick);
	scene.Add(ugg);


	InputManager::GetInstance().AddCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Position::TopLeft }, VK_PAD_LTHUMB_UPLEFT, XINPUT_KEYSTROKE_KEYDOWN);
	InputManager::GetInstance().AddCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Position::TopRight }, VK_PAD_LTHUMB_UPRIGHT, XINPUT_KEYSTROKE_KEYDOWN);
	InputManager::GetInstance().AddCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Position::BottomLeft }, VK_PAD_LTHUMB_DOWNLEFT, XINPUT_KEYSTROKE_KEYDOWN);
	InputManager::GetInstance().AddCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Position::BottomRight }, VK_PAD_LTHUMB_DOWNRIGHT, XINPUT_KEYSTROKE_KEYDOWN);
	InputManager::GetInstance().AddCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Position::TopLeft }, VK_PAD_Y, XINPUT_KEYSTROKE_KEYDOWN);
	InputManager::GetInstance().AddCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Position::TopRight }, VK_PAD_B, XINPUT_KEYSTROKE_KEYDOWN);
	InputManager::GetInstance().AddCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Position::BottomLeft }, VK_PAD_X, XINPUT_KEYSTROKE_KEYDOWN);
	InputManager::GetInstance().AddCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Position::BottomRight }, VK_PAD_A, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new PlayerDieCommand{ QBert2->getComponent<PlayerComponent>() }, VK_PAD_RSHOULDER, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert->getComponent<PlayerComponent>(), 25 }, VK_PAD_A, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert->getComponent<PlayerComponent>(), 500 }, VK_PAD_B, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert->getComponent<PlayerComponent>(), 50 }, VK_PAD_X, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert->getComponent<PlayerComponent>(), 300 }, VK_PAD_Y, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert2->getComponent<PlayerComponent>(), 25 }, VK_PAD_DPAD_DOWN, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert2->getComponent<PlayerComponent>(), 500 }, VK_PAD_DPAD_RIGHT, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert2->getComponent<PlayerComponent>(), 50 }, VK_PAD_DPAD_LEFT, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert2->getComponent<PlayerComponent>(), 300 }, VK_PAD_DPAD_UP, XINPUT_KEYSTROKE_KEYDOWN);

	std::cout << "LShoulder: Kill player1\nRShoulder: Kill player2\nA: Player1 Gains 25 score\nB: Player1 Gains 500 score\nX: Player1 Gains 50 score\nY: Player2 Gains 300 score\nDpadDown: Player2 Gains 25 score\nDpadRight: Player2 Gains 500 score\nDpadLeft: Player2 Gains 50 score\nDpadUp: Player2 Gains 300 score\n";



	ServiceLocator::GetSoundSystem()->AddEffect("./../data/Q-bert_Death_Sound.wav", 1);
}

void Game::Cleanup()
{
	//Renderer::GetInstance().Destroy();
	Minigin::Cleanup();
}
