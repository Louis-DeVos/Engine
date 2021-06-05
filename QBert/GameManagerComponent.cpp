#include "GameManagerComponent.h"
#include <RenderComponent.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <Scene.h>
#include <Font.h>
#include <TextComponent.h>
#include <FPSComponent.h>
#include <LifeComponent.h>
#include <ScoreComponent.h>
#include <SubjectComponent.h>
#include "ScoreObserver.h"
#include "PlayerDeathObserver.h"
#include "CoilyComponent.h"
#include "GreenEnemyComponent.h"
#include "PurpleEnemyComponent.h"
#include "LevelConstructor.h"
#include "QBertComponent.h"
#include "InputManager.h"
#include "Command.h"
#include <ServiceLocator.h>
#include <algorithm>
#include "PlayerDeathObserver.h"
#include "ScoreObserver.h"
#include <SDL.h>

GameManagerComponent::GameManagerComponent(std::weak_ptr<dae::GameObject> pGameObject)
	:m_pGameObject{pGameObject}
{

	using namespace dae;

	auto scene = m_pGameObject.lock()->GetScene();

	std::shared_ptr<dae::GameObject> go = std::make_shared<dae::GameObject>(scene);
	std::shared_ptr<RenderComponent> render = std::make_shared<RenderComponent>(std::weak_ptr<dae::GameObject>(go));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.jpg"));
	go->AddComponent(render);
	scene.lock()->Add(go);

	go = std::make_shared<dae::GameObject>(scene);
	render = std::make_shared<RenderComponent>(std::weak_ptr<dae::GameObject>(go));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("logo.png"));
	go->AddComponent(render);
	go->SetPosition(216, 180);
	scene.lock()->Add(go);

	std::shared_ptr<dae::Font> font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>(scene);
	go->AddComponent(std::make_shared<dae::TextComponent>("Programming 4 Assignment", font, std::weak_ptr<GameObject>(go)));
	go->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<dae::GameObject>(go)));
	go->SetPosition(80, 20);
	scene.lock()->Add(go);

	std::shared_ptr<dae::GameObject> fps = std::make_shared<GameObject>(scene);
	fps->AddComponent(std::make_shared<FPSComponent>(std::weak_ptr<GameObject>(fps)));
	fps->AddComponent(std::make_shared<TextComponent>(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), std::weak_ptr<GameObject>(fps)));
	fps->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(fps)));
	scene.lock()->Add(fps);

	std::shared_ptr<dae::GameObject> lifeCounter = std::make_shared<GameObject>(scene);
	lifeCounter->AddComponent(std::make_shared<LifeComponent>(std::weak_ptr<GameObject>(lifeCounter)));
	lifeCounter->AddComponent(std::make_shared<TextComponent>(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), std::weak_ptr<GameObject>(lifeCounter)));
	lifeCounter->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(lifeCounter)));
	lifeCounter->SetPosition(200, 0);
	scene.lock()->Add(lifeCounter);

	std::shared_ptr<dae::GameObject> lifeCounter2 = std::make_shared<GameObject>(scene);
	lifeCounter2->AddComponent(std::make_shared<LifeComponent>(std::weak_ptr<GameObject>(lifeCounter2)));
	lifeCounter2->AddComponent(std::make_shared<TextComponent>(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), std::weak_ptr<GameObject>(lifeCounter2)));
	lifeCounter2->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(lifeCounter2)));
	lifeCounter2->SetPosition(200, 10);
	scene.lock()->Add(lifeCounter2);

	std::shared_ptr<dae::GameObject> scoreCounter = std::make_shared<GameObject>(scene);
	scoreCounter->AddComponent(std::make_shared<ScoreComponent>(std::weak_ptr<GameObject>(scoreCounter)));
	scoreCounter->AddComponent(std::make_shared<TextComponent>(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), std::weak_ptr<GameObject>(scoreCounter)));
	scoreCounter->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(scoreCounter)));
	scoreCounter->SetPosition(300, 0);
	scene.lock()->Add(scoreCounter);

	std::shared_ptr<dae::GameObject> scoreCounter2 = std::make_shared<GameObject>(scene);
	scoreCounter2->AddComponent(std::make_shared<ScoreComponent>(std::weak_ptr<GameObject>(scoreCounter2)));
	scoreCounter2->AddComponent(std::make_shared<TextComponent>(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), std::weak_ptr<GameObject>(scoreCounter2)));
	scoreCounter2->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(scoreCounter2)));
	scoreCounter2->SetPosition(300, 10);
	scene.lock()->Add(scoreCounter2);

	std::shared_ptr<dae::GameObject> QBert = std::make_shared<GameObject>(scene);
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

	std::shared_ptr<dae::GameObject> QBert2 = std::make_shared<GameObject>(scene);
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





	std::shared_ptr<dae::GameObject> Coily = std::make_shared<GameObject>(scene);
	Coily->AddComponent(std::make_shared<CoilyComponent>(Coily));
	render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(Coily));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Egg.png"));
	Coily->AddComponent(render);



	std::shared_ptr<dae::GameObject> Slick = std::make_shared<GameObject>(scene);
	Slick->AddComponent(std::make_shared<GreenEnemyComponent>(Slick));
	render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(Slick));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Slick.png"));
	Slick->AddComponent(render);

	std::shared_ptr<dae::GameObject> ugg = std::make_shared<GameObject>(scene);
	ugg->AddComponent(std::make_shared<PurpleEnemyComponent>(ugg, -1));
	render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(ugg));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Ugg.png"));
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

	m_pStartNode = levelConstructor.CreateLevel(scene, "../Data/Level1.txt");


	m_pPlayer = qbertComponent;

	m_pCoily = Coily->getComponent<CoilyComponent>();

	qbertComponent->SetLocation(m_pStartNode);
	qbert2Component->SetLocation(m_pStartNode.lock()->GetConnection(Position::BottomLeft));
	Coily->getComponent<CoilyComponent>().lock()->SetTarget(QBert);
	Coily->getComponent<CoilyComponent>().lock()->SetLocation(m_pStartNode.lock()->GetConnection(Position::BottomRight));
	Slick->getComponent<GreenEnemyComponent>().lock()->SetLocation(m_pStartNode.lock()->GetConnection(Position::BottomLeft));
	ugg->getComponent<PurpleEnemyComponent>().lock()->SetLocation(m_pStartNode.lock()->GetLastConnection(Position::BottomRight));

	scene.lock()->Add(QBert);
	//scene.lock()->Add(QBert2);
	scene.lock()->Add(Coily);
	scene.lock()->Add(Slick);
	scene.lock()->Add(ugg);

	m_GreenEnemies.push_back(Slick->getComponent<GreenEnemyComponent>());
	m_PurpleEnemies.push_back(ugg->getComponent<PurpleEnemyComponent>());



	InputManager::GetInstance().AddKeyboardCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Position::TopLeft }, SDLK_q, SDL_KEYDOWN);
	InputManager::GetInstance().AddKeyboardCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Position::TopRight }, SDLK_w, SDL_KEYDOWN);
	InputManager::GetInstance().AddKeyboardCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Position::BottomLeft }, SDLK_a, SDL_KEYDOWN);
	InputManager::GetInstance().AddKeyboardCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Position::BottomRight }, SDLK_s, SDL_KEYDOWN);


	InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Position::TopLeft }, VK_PAD_LTHUMB_UPLEFT, XINPUT_KEYSTROKE_KEYDOWN);
	InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Position::TopRight }, VK_PAD_LTHUMB_UPRIGHT, XINPUT_KEYSTROKE_KEYDOWN);
	InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Position::BottomLeft }, VK_PAD_LTHUMB_DOWNLEFT, XINPUT_KEYSTROKE_KEYDOWN);
	InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Position::BottomRight }, VK_PAD_LTHUMB_DOWNRIGHT, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Position::TopLeft }, VK_PAD_Y, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Position::TopRight }, VK_PAD_B, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Position::BottomLeft }, VK_PAD_X, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Position::BottomRight }, VK_PAD_A, XINPUT_KEYSTROKE_KEYDOWN);
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

GameManagerComponent::~GameManagerComponent()
{
}

void GameManagerComponent::Update(float )
{
	CheckCollisions();
}

void GameManagerComponent::FixedUpdate(float )
{
}

void GameManagerComponent::Render(const glm::vec3& ) const
{
}

void GameManagerComponent::CheckCollisions()
{
	m_GreenEnemies.erase(std::remove_if(m_GreenEnemies.begin(), m_GreenEnemies.end(), [](std::weak_ptr<GreenEnemyComponent> enemy) {return enemy.expired(); }), m_GreenEnemies.end());

	m_PurpleEnemies.erase(std::remove_if(m_PurpleEnemies.begin(), m_PurpleEnemies.end(), [](std::weak_ptr<PurpleEnemyComponent> enemy) {return enemy.expired(); }), m_PurpleEnemies.end());

	std::weak_ptr<QBertComponent> qbert = m_pPlayer;
	std::weak_ptr<GridNodeComponent> startNode = m_pStartNode;

	std::for_each(m_GreenEnemies.begin(), m_GreenEnemies.end(), [qbert](std::weak_ptr<GreenEnemyComponent> greenEnemy) {if (greenEnemy.lock()->CheckCollision(qbert)) greenEnemy.lock()->Die(); });

	std::for_each(m_PurpleEnemies.begin(), m_PurpleEnemies.end(), [qbert, startNode](std::weak_ptr<PurpleEnemyComponent> purpleEnemy)
		{
			if (purpleEnemy.lock()->CheckCollision(qbert))
			{
				qbert.lock()->SetLocation(startNode);
				qbert.lock()->Die();
			}
		});


	if (!m_pCoily.expired() && m_pCoily.lock()->CheckCollision(qbert))
	{
		qbert.lock()->SetLocation(startNode);
		qbert.lock()->Die();
	}
}
