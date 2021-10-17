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
#include "ScoreComponent.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include <time.h>

using namespace std;
using namespace std::chrono;

void Minigin::Initialize()
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

	srand(int(time(nullptr)));
	
}

/**
 * Code constructing the scene world starts here
 */
void Minigin::LoadGame() const
{
	
}

void Minigin::Cleanup()
{
	delete ServiceLocator::GetSoundSystem();

	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Minigin::Run()
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
