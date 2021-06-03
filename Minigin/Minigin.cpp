#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "FPSComponent.h"
#include "SubjectComponent.h"
#include "PlayerComponent.h"
#include "PlayerDeathObserver.h"
#include "LifeComponent.h"
#include "ScoreComponent.h"
#include "ScoreObserver.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "GraphComponent.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	_putenv("SDL_AUDIODRIVER=DirectSound");


	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	if (SDL_Init(SDL_INIT_AUDIO) != 0)
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "Core::Initialize( ), error when calling Mix_OpenAudio: " << Mix_GetError() << std::endl;
		return;
	}

	const int mixerFlags{ MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG };
	if ((Mix_Init(mixerFlags) & mixerFlags) != mixerFlags)
		std::cerr << "SDL Mixer failed to initialize! Cause of the error: " << Mix_GetError();


	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);


	ServiceLocator::RegisterSoundSystem(new SoundSystem());
	
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//std::shared_ptr<dae::GameObject> go = std::make_shared<GameObject>();
	//std::shared_ptr<RenderComponent> render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(go));
	//render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.jpg"));
	//go->AddComponent(render);
	//scene.Add(go);

	//go = std::make_shared<GameObject>();
	//render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(go) );
	//render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("logo.png"));
	//go->AddComponent(render);
	//go->SetPosition(216, 180);
	//scene.Add(go);

	//std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//go = std::make_shared<GameObject>();
	//go->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", font,std::weak_ptr<GameObject>(go)));
	//go->AddComponent(std::make_shared<RenderComponent>( std::weak_ptr<GameObject>(go)));
	//go->SetPosition(80, 20);
	//scene.Add(go);

	//std::shared_ptr<dae::GameObject> fps = std::make_shared<GameObject>();
	//fps->AddComponent(std::make_shared<FPSComponent>(std::weak_ptr<GameObject>(fps) ));
	//fps->AddComponent(std::make_shared<TextComponent>(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), std::weak_ptr<GameObject>(fps)));
	//fps->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(fps)));
	//scene.Add(fps);

	//std::shared_ptr<dae::GameObject> lifeCounter = std::make_shared<GameObject>();
	//lifeCounter->AddComponent(std::make_shared<LifeComponent>(std::weak_ptr<GameObject>(lifeCounter)));
	//lifeCounter->AddComponent(std::make_shared<TextComponent>(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), std::weak_ptr<GameObject>(lifeCounter) ));
	//lifeCounter->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(lifeCounter )));
	//lifeCounter->SetPosition(200, 0);
	//scene.Add(lifeCounter);
	//
	//std::shared_ptr<dae::GameObject> lifeCounter2 = std::make_shared<GameObject>();
	//lifeCounter2->AddComponent(std::make_shared<LifeComponent>(std::weak_ptr<GameObject>(lifeCounter2)));
	//lifeCounter2->AddComponent(std::make_shared<TextComponent>(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), std::weak_ptr<GameObject>(lifeCounter2) ));
	//lifeCounter2->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(lifeCounter2)));
	//lifeCounter2->SetPosition(200, 10);
	//scene.Add(lifeCounter2);
	//
	//std::shared_ptr<dae::GameObject> scoreCounter = std::make_shared<GameObject>();
	//scoreCounter->AddComponent(std::make_shared<ScoreComponent>(std::weak_ptr<GameObject>(scoreCounter)));
	//scoreCounter->AddComponent(std::make_shared<TextComponent>(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), std::weak_ptr<GameObject>(scoreCounter) ));
	//scoreCounter->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(scoreCounter)));
	//scoreCounter->SetPosition(300, 0);
	//scene.Add(scoreCounter);
	//
	//std::shared_ptr<dae::GameObject> scoreCounter2 = std::make_shared<GameObject>();
	//scoreCounter2->AddComponent(std::make_shared<ScoreComponent>(std::weak_ptr<GameObject>(scoreCounter2)));
	//scoreCounter2->AddComponent(std::make_shared<TextComponent>(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), std::weak_ptr<GameObject>(scoreCounter2) ));
	//scoreCounter2->AddComponent(std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(scoreCounter2)));
	//scoreCounter2->SetPosition(300, 10);
	//scene.Add(scoreCounter2);

	//std::shared_ptr<dae::GameObject> QBert = std::make_shared<GameObject>();
	////QBert->AddComponent(new RenderComponent{ QBert });
	////render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.jpg"));
	//QBert->AddComponent(std::make_shared<PlayerComponent>(QBert));
	//QBert->AddComponent(std::make_shared<SubjectComponent>(QBert));
	//QBert->getComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<PlayerDeathObserver>(lifeCounter->getComponent<LifeComponent>()));
	//QBert->getComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<ScoreObserver>(scoreCounter->getComponent<ScoreComponent>()));
	//scene.Add(QBert);
	//
	//std::shared_ptr<dae::GameObject> QBert2 = std::make_shared<GameObject>();
	////QBert->AddComponent(new RenderComponent{ QBert });
	////render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.jpg"));
	//QBert2->AddComponent(std::make_shared<PlayerComponent>(QBert2));
	//QBert2->AddComponent(std::make_shared<SubjectComponent>(QBert2));
	//QBert2->getComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<PlayerDeathObserver>(lifeCounter2->getComponent<LifeComponent>()));
	//QBert2->getComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<ScoreObserver>(scoreCounter2->getComponent<ScoreComponent>()));
	//scene.Add(QBert2);



	//std::shared_ptr<dae::GameObject> Node = std::make_shared<GameObject>();
	//Node->AddComponent(std::make_shared<RenderComponent>( Node ));
	//Node->AddComponent(std::make_shared<GridNodeComponent>(Node));



	//InputManager::GetInstance().AddCommand(new PlayerDieCommand{ QBert->getComponent<PlayerComponent>() }, VK_PAD_LSHOULDER, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new PlayerDieCommand{ QBert2->getComponent<PlayerComponent>() }, VK_PAD_RSHOULDER, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert->getComponent<PlayerComponent>(), 25 }, VK_PAD_A, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert->getComponent<PlayerComponent>(), 500 }, VK_PAD_B, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert->getComponent<PlayerComponent>(), 50 }, VK_PAD_X, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert->getComponent<PlayerComponent>(), 300 }, VK_PAD_Y, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert2->getComponent<PlayerComponent>(), 25 }, VK_PAD_DPAD_DOWN, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert2->getComponent<PlayerComponent>(), 500 }, VK_PAD_DPAD_RIGHT, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert2->getComponent<PlayerComponent>(), 50 }, VK_PAD_DPAD_LEFT, XINPUT_KEYSTROKE_KEYDOWN);
	//InputManager::GetInstance().AddCommand(new GainScoreCommand{ QBert2->getComponent<PlayerComponent>(), 300 }, VK_PAD_DPAD_UP, XINPUT_KEYSTROKE_KEYDOWN);

	//std::cout << "LShoulder: Kill player1\nRShoulder: Kill player2\nA: Player1 Gains 25 score\nB: Player1 Gains 500 score\nX: Player1 Gains 50 score\nY: Player2 Gains 300 score\nDpadDown: Player2 Gains 25 score\nDpadRight: Player2 Gains 500 score\nDpadLeft: Player2 Gains 50 score\nDpadUp: Player2 Gains 300 score\n";


	//
	//ServiceLocator::GetSoundSystem()->AddEffect("./../data/Q-bert_Death_Sound.wav",1);
}

void dae::Minigin::Cleanup()
{
	delete ServiceLocator::GetSoundSystem();

	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		auto lastTime = high_resolution_clock::now();

		float lag = 0.0f;

		bool doContinue = true;
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;

			doContinue = input.ProcessInput();

			lag += deltaTime;

			float targetFrameTime = MsPerFrame / 1000.f;

			while (lag >= targetFrameTime)
			{
				sceneManager.FixedUpdate(targetFrameTime);
				lag -= targetFrameTime;
			}

			sceneManager.Update(deltaTime);
			renderer.Render();

			sceneManager.DestroyObjects();
		}
	}

	Cleanup();
}
