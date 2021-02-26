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
#include "LifeComponent.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

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
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	GameObject* go = new GameObject{};
	RenderComponent* render = new RenderComponent{go};
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.jpg"));
	go->AddComponent(render);
	scene.Add(go);

	go = new GameObject{};
	render = new RenderComponent{go};
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("logo.png"));
	go->AddComponent(render);
	go->SetPosition(216, 180);
	scene.Add(go);

	Font* font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = new GameObject{};
	go->AddComponent(new TextComponent{ "Programming 4 Assignment", font,go });
	go->AddComponent(new RenderComponent{go });
	go->SetPosition(80, 20);
	scene.Add(go);

	GameObject* fps = new GameObject{};
	fps->AddComponent(new FPSComponent{fps});
	fps->AddComponent(new TextComponent{ "", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12), fps});
	fps->AddComponent(new RenderComponent{fps});
	scene.Add(fps);



	//GameObject* QBert = new GameObject{};
	//QBert->AddComponent(new RenderComponent{ QBert });
	//QBert->AddComponent(new PlayerComponent{ QBert });
	//QBert->AddComponent(new SubjectComponent{ QBert });
	//scene.Add(QBert);

	InputManager::GetInstance().AddCommand(new PlayerDieCommand{ QBert->getComponent<PlayerComponent>() }, VK_GAMEPAD_A, XINPUT_KEYSTROKE_KEYDOWN);
}

void dae::Minigin::Cleanup()
{
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
		}
	}

	Cleanup();
}
