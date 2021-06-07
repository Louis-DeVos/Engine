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
#include "DiskComponent.h"
#include "MenuComponent.h"

GameManagerComponent::GameManagerComponent(std::weak_ptr<dae::GameObject> pGameObject)
	:m_pGameObject{pGameObject}
{

	using namespace dae;

	auto scene = m_pGameObject.lock()->GetScene();


	



	auto go = std::make_shared<dae::GameObject>(scene);
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

	m_pScoreCounter = scoreCounter->getComponent<ScoreComponent>();
	m_pLifeCounter = lifeCounter->getComponent<LifeComponent>();
	m_pLifeCounter2 = lifeCounter2->getComponent<LifeComponent>();

	//m_Coop = true;
	//LoadLevel("");



	std::cout << "Player1 movement: qwas/dpad\nPlayer2 movement: iokl/face buttons\n";



	ServiceLocator::GetSoundSystem()->AddEffect("./../data/Q-bert_Death_Sound.wav", 1);



}


void GameManagerComponent::Update(float dt)
{
	m_GreenEnemies.erase(std::remove_if(m_GreenEnemies.begin(), m_GreenEnemies.end(), [](std::weak_ptr<GreenEnemyComponent> enemy) {return enemy.expired(); }), m_GreenEnemies.end());

	m_PurpleEnemies.erase(std::remove_if(m_PurpleEnemies.begin(), m_PurpleEnemies.end(), [](std::weak_ptr<PurpleEnemyComponent> enemy) {return enemy.expired(); }), m_PurpleEnemies.end());

	m_Disks.erase(std::remove_if(m_Disks.begin(), m_Disks.end(), [](std::weak_ptr<DiskComponent> enemy) {return enemy.expired(); }), m_Disks.end());



	if (m_pMenu.expired())
	{
		std::shared_ptr<dae::GameObject> menuObject = std::make_shared<dae::GameObject>(m_pGameObject.lock()->GetScene());
		std::shared_ptr<MenuComponent> menuComponent = std::make_shared<MenuComponent>(std::weak_ptr<dae::GameObject>(menuObject), m_pGameObject.lock()->getComponent<GameManagerComponent>());
		menuObject->AddComponent(menuComponent);
		m_pMenu = menuComponent;
		m_pGameObject.lock()->GetScene().lock()->Add(menuObject);
	}



	if (m_EnemiesCleared)
	{
		LoadLevel();
		m_EnemiesCleared = false;
	}

	CheckCollisions();

	m_EnemySpawnTimer += dt;
	if (m_EnemySpawnTimer >= m_EnemySpawnDelay && !m_pStartNode.expired())
	{
		if (m_pCoily.expired() && !m_pPlayer.expired())
		{
			SpawnCoily();
		}
		else if(rand()%2==0)
		{
			SpawnGreenEnemy();
		}
		else
		{
			SpawnPurpleEnemy();
		}
		m_EnemySpawnTimer = 0.f;
	}



	if (!m_pStartNode.expired() && m_Nodes.size() > 0 && std::all_of(m_Nodes.begin(), m_Nodes.end(), [](std::weak_ptr<GridNodeComponent> node) {return node.lock()->OnLastState(); }))
	{
		reset();
		if (m_Currentlevel != m_maxLevel)
		{
			++m_Currentlevel;
			m_EnemiesCleared = true;
		}
	}

	
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

	std::for_each(m_GreenEnemies.begin(), m_GreenEnemies.end(), [qbert](std::weak_ptr<GreenEnemyComponent> greenEnemy)
		{
			if (!qbert.expired() && greenEnemy.lock()->CheckCollision(qbert))
			{
				qbert.lock()->GainScore(300);
				greenEnemy.lock()->Die();
			}
		});

	std::for_each(m_PurpleEnemies.begin(), m_PurpleEnemies.end(), [this, qbert, startNode](std::weak_ptr<PurpleEnemyComponent> purpleEnemy)
		{
			if (!qbert.expired() && purpleEnemy.lock()->CheckCollision(qbert))
			{
				OnQBertDeath(qbert);
			}
		});


	if (!m_pCoily.expired() && !qbert.expired() && m_pCoily.lock()->CheckCollision(qbert))
	{
		OnQBertDeath(qbert);
	}



	qbert = m_pPlayer2;

	std::for_each(m_GreenEnemies.begin(), m_GreenEnemies.end(), [qbert](std::weak_ptr<GreenEnemyComponent> greenEnemy)
		{
			if (!qbert.expired() && greenEnemy.lock()->CheckCollision(qbert))
			{
				qbert.lock()->GainScore(300);
				greenEnemy.lock()->Die();
			}
		});

	std::for_each(m_PurpleEnemies.begin(), m_PurpleEnemies.end(), [this, qbert, startNode](std::weak_ptr<PurpleEnemyComponent> purpleEnemy)
		{
			if (!qbert.expired() && purpleEnemy.lock()->CheckCollision(qbert))
			{
				OnQBertDeath(qbert);
			}
		});


	if (!m_pCoily.expired() && !qbert.expired() && m_pCoily.lock()->CheckCollision(qbert))
	{
		OnQBertDeath(qbert);
	}
}

void GameManagerComponent::SpawnCoily()
{
	auto scene = m_pGameObject.lock()->GetScene();

	std::shared_ptr<dae::GameObject> Coily = std::make_shared<dae::GameObject>(scene);
	Coily->AddComponent(std::make_shared<CoilyComponent>(Coily));
	auto render = std::make_shared<RenderComponent>(std::weak_ptr<dae::GameObject>(Coily));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Egg.png"));
	Coily->AddComponent(render);

	m_pCoily = Coily->getComponent<CoilyComponent>();


	Coily->getComponent<CoilyComponent>().lock()->SetTarget(m_pPlayer.lock()->GetOwner());
	Coily->getComponent<CoilyComponent>().lock()->SetLocation(m_pStartNode.lock()->GetConnection((rand()%2 == 0)? Direction::BottomRight : Direction::BottomLeft));
	scene.lock()->Add(Coily);

	if (m_Versus)
	{
		m_pCoily.lock()->SetControlledByPlayer(true);
		dae::InputManager::GetInstance().AddKeyboardCommand(new CoilyMoveCommand{ m_pCoily, Direction::TopLeft }, SDLK_i, SDL_KEYDOWN);
		dae::InputManager::GetInstance().AddKeyboardCommand(new CoilyMoveCommand{ m_pCoily, Direction::TopRight }, SDLK_o, SDL_KEYDOWN);
		dae::InputManager::GetInstance().AddKeyboardCommand(new CoilyMoveCommand{ m_pCoily, Direction::BottomLeft }, SDLK_k, SDL_KEYDOWN);
		dae::InputManager::GetInstance().AddKeyboardCommand(new CoilyMoveCommand{ m_pCoily, Direction::BottomRight }, SDLK_l, SDL_KEYDOWN);


		dae::InputManager::GetInstance().AddControllerCommand(new CoilyMoveCommand{ m_pCoily, Direction::TopLeft }, VK_PAD_X, XINPUT_KEYSTROKE_KEYDOWN);
		dae::InputManager::GetInstance().AddControllerCommand(new CoilyMoveCommand{ m_pCoily, Direction::TopRight }, VK_PAD_Y, XINPUT_KEYSTROKE_KEYDOWN);
		dae::InputManager::GetInstance().AddControllerCommand(new CoilyMoveCommand{ m_pCoily, Direction::BottomLeft }, VK_PAD_A, XINPUT_KEYSTROKE_KEYDOWN);
		dae::InputManager::GetInstance().AddControllerCommand(new CoilyMoveCommand{ m_pCoily, Direction::BottomRight }, VK_PAD_B, XINPUT_KEYSTROKE_KEYDOWN);
	}
}

void GameManagerComponent::SpawnPurpleEnemy()
{
	auto scene = m_pGameObject.lock()->GetScene();

	int randomNum = rand() % 2;

	std::shared_ptr<dae::GameObject> purpleEnemy = std::make_shared<dae::GameObject>(scene);
	purpleEnemy->AddComponent(std::make_shared<PurpleEnemyComponent>(purpleEnemy, (randomNum == 0) ? -1 : 1));
	auto render = std::make_shared<RenderComponent>(std::weak_ptr<dae::GameObject>(purpleEnemy));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture((randomNum == 0) ? "Ugg.png" : "Wrongway.png"));
	purpleEnemy->AddComponent(render);

	purpleEnemy->getComponent<PurpleEnemyComponent>().lock()->SetLocation(m_pStartNode.lock()->GetLastConnection((randomNum == 0) ? Direction::BottomRight : Direction::BottomLeft));
	m_PurpleEnemies.push_back(purpleEnemy->getComponent<PurpleEnemyComponent>());
	scene.lock()->Add(purpleEnemy);
}

void GameManagerComponent::SpawnGreenEnemy()
{
	auto scene = m_pGameObject.lock()->GetScene();

	std::shared_ptr<dae::GameObject> greenEnemy = std::make_shared<dae::GameObject>(scene);
	greenEnemy->AddComponent(std::make_shared<GreenEnemyComponent>(greenEnemy));
	auto render = std::make_shared<RenderComponent>(std::weak_ptr<dae::GameObject>(greenEnemy));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture((rand() % 2 == 0) ? "Slick.png" : "Sam.png"));
	greenEnemy->AddComponent(render);


	greenEnemy->getComponent<GreenEnemyComponent>().lock()->SetLocation(m_pStartNode.lock()->GetConnection((rand() % 2 == 0) ? Direction::BottomRight : Direction::BottomLeft));
	m_GreenEnemies.push_back(greenEnemy->getComponent<GreenEnemyComponent>());
	scene.lock()->Add(greenEnemy);
}

void GameManagerComponent::OnQBertDeath(std::weak_ptr<QBertComponent> qbert)
{
	if (!qbert.expired())
	{
		qbert.lock()->SetLocation(m_pStartNode);
		qbert.lock()->Die();

		if (!m_pCoily.expired())
		{
			m_pCoily.lock()->Die();
		}

		std::for_each(m_GreenEnemies.begin(), m_GreenEnemies.end(), [](std::weak_ptr<GreenEnemyComponent> greenEnemy)
			{
				if (!greenEnemy.expired())
				{
					greenEnemy.lock()->Die();
				}
			});
		std::for_each(m_PurpleEnemies.begin(), m_PurpleEnemies.end(), [](std::weak_ptr<PurpleEnemyComponent> purpleEnemy)
			{
				if (!purpleEnemy.expired())
				{
					purpleEnemy.lock()->Die();
				}
			});


	}

	if (qbert.expired() || qbert.lock()->GetLives() == 0)
	{
		reset();
	}
	//else if(m_pPlayer.lock()->GetLives() == 0)
	//{
	//	reset();
	//}

}

void GameManagerComponent::reset()
{
	std::for_each(m_Nodes.begin(), m_Nodes.end(), [](std::weak_ptr<GridNodeComponent> node) {node.lock()->GetOwner().lock()->SetToBeDestroyed(); });
	std::for_each(m_Disks.begin(), m_Disks.end(), [](std::weak_ptr<DiskComponent> disk) {if(!disk.expired())disk.lock()->GetOwner().lock()->SetToBeDestroyed(); });
	std::for_each(m_GreenEnemies.begin(), m_GreenEnemies.end(), [](std::weak_ptr<GreenEnemyComponent> enemy) {enemy.lock()->GetOwner().lock()->SetToBeDestroyed(); });
	std::for_each(m_PurpleEnemies.begin(), m_PurpleEnemies.end(), [](std::weak_ptr<PurpleEnemyComponent> enemy) {enemy.lock()->GetOwner().lock()->SetToBeDestroyed(); });
	m_Nodes.clear();
	m_Disks.clear();
	m_GreenEnemies.clear();
	m_PurpleEnemies.clear();

	if (!m_pCoily.expired())
	{
		m_pCoily.lock()->GetOwner().lock()->SetToBeDestroyed();
	}
	if (!m_pPlayer.expired())
	{
		m_pPlayer.lock()->GetOwner().lock()->SetToBeDestroyed();
	}
	if (!m_pPlayer2.expired())
	{
		m_pPlayer2.lock()->GetOwner().lock()->SetToBeDestroyed();
	}
	
	dae::InputManager::GetInstance().Clear();

	m_LevelLoaded= false;
}

void GameManagerComponent::StartSinglePlayer()
{
	m_Currentlevel = 1;
	m_Coop = false;
	m_Versus = false;
	LoadLevel();
}

void GameManagerComponent::StartCoop()
{
	m_Currentlevel = 1;
	m_Coop = true;
	m_Versus = false;
	LoadLevel();
}

void GameManagerComponent::StartVersus()
{
	m_Currentlevel = 1;
	m_Coop = false;
	m_Versus = true;
	LoadLevel();
}

void GameManagerComponent::LoadLevel( )
{
	auto scene = m_pGameObject.lock()->GetScene();


	LevelConstructor levelConstructor{};

	auto pair = levelConstructor.CreateLevel(scene, "../Data/Level" + std::to_string(m_Currentlevel) + ".txt");
	
	std::for_each(m_Nodes.begin(), m_Nodes.end(), [](std::weak_ptr<GridNodeComponent> node) {node.lock()->GetOwner().lock()->SetToBeDestroyed(); });
	std::for_each(m_Disks.begin(), m_Disks.end(), [](std::weak_ptr<DiskComponent> disk) {if (!disk.expired())disk.lock()->GetOwner().lock()->SetToBeDestroyed(); });

	m_Nodes = pair.first;
	m_Disks = pair.second;

	m_pStartNode = m_Nodes[0];

	std::shared_ptr<dae::GameObject> QBert = std::make_shared<dae::GameObject>(scene);
	std::shared_ptr<QBertComponent> qbertComponent = std::make_shared<QBertComponent>(QBert);
	QBert->AddComponent(qbertComponent);
	QBert->AddComponent(std::make_shared<SubjectComponent>(QBert));
	auto render = std::make_shared<RenderComponent>(std::weak_ptr<dae::GameObject>(QBert));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("QBert.png"));
	QBert->AddComponent(render);
	QBert->getComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<PlayerDeathObserver>(m_pLifeCounter));
	QBert->getComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<ScoreObserver>(m_pScoreCounter));
	m_pLifeCounter.lock()->SetLives(qbertComponent->GetLives());
	if (m_Coop)
	{
		qbertComponent->SetStartLocation(m_pStartNode.lock()->GetLastConnection(Direction::BottomLeft));
	}
	else
	{
		qbertComponent->SetStartLocation(m_pStartNode);
	}
	scene.lock()->Add(QBert);
	m_pPlayer = qbertComponent;

	dae::InputManager::GetInstance().AddKeyboardCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Direction::TopLeft }, SDLK_q, SDL_KEYDOWN);
	dae::InputManager::GetInstance().AddKeyboardCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Direction::TopRight }, SDLK_w, SDL_KEYDOWN);
	dae::InputManager::GetInstance().AddKeyboardCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Direction::BottomLeft }, SDLK_a, SDL_KEYDOWN);
	dae::InputManager::GetInstance().AddKeyboardCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Direction::BottomRight }, SDLK_s, SDL_KEYDOWN);


	dae::InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Direction::TopLeft }, VK_PAD_DPAD_LEFT, XINPUT_KEYSTROKE_KEYDOWN);
	dae::InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Direction::TopRight }, VK_GAMEPAD_DPAD_UP, XINPUT_KEYSTROKE_KEYDOWN);
	dae::InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Direction::BottomLeft }, VK_PAD_DPAD_DOWN, XINPUT_KEYSTROKE_KEYDOWN);
	dae::InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert->getComponent<QBertComponent>(), Direction::BottomRight }, VK_PAD_DPAD_RIGHT, XINPUT_KEYSTROKE_KEYDOWN);


	if (m_Coop)
	{

		std::shared_ptr<dae::GameObject> QBert2 = std::make_shared<dae::GameObject>(scene);
		std::shared_ptr<QBertComponent> qbert2Component = std::make_shared<QBertComponent>(QBert2);
		QBert2->AddComponent(qbert2Component);
		QBert2->AddComponent(std::make_shared<SubjectComponent>(QBert2));
		 render = std::make_shared<RenderComponent>(std::weak_ptr<dae::GameObject>(QBert2));
		render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("QBert.png"));
		QBert2->AddComponent(render);
		QBert2->getComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<PlayerDeathObserver>(m_pLifeCounter2));
		QBert2->getComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<ScoreObserver>(m_pScoreCounter));
		m_pLifeCounter2.lock()->SetLives(qbert2Component->GetLives());
		qbert2Component->SetStartLocation(m_pStartNode.lock()->GetLastConnection(Direction::BottomRight));
		scene.lock()->Add(QBert2);
		m_pPlayer2 = qbert2Component;

		dae::InputManager::GetInstance().AddKeyboardCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Direction::TopLeft }, SDLK_i, SDL_KEYDOWN);
		dae::InputManager::GetInstance().AddKeyboardCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Direction::TopRight }, SDLK_o, SDL_KEYDOWN);
		dae::InputManager::GetInstance().AddKeyboardCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Direction::BottomLeft }, SDLK_k, SDL_KEYDOWN);
		dae::InputManager::GetInstance().AddKeyboardCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Direction::BottomRight }, SDLK_l, SDL_KEYDOWN);


		dae::InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Direction::TopLeft }, VK_PAD_X, XINPUT_KEYSTROKE_KEYDOWN);
		dae::InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Direction::TopRight }, VK_GAMEPAD_Y, XINPUT_KEYSTROKE_KEYDOWN);
		dae::InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Direction::BottomLeft }, VK_PAD_A, XINPUT_KEYSTROKE_KEYDOWN);
		dae::InputManager::GetInstance().AddControllerCommand(new MoveCommand{ QBert2->getComponent<QBertComponent>(), Direction::BottomRight }, VK_PAD_B, XINPUT_KEYSTROKE_KEYDOWN);


	}


	std::cout << "Load level";

	m_LevelLoaded = true;
}
