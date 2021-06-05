#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <memory>
#include <string>

void dae::SceneManager::Update(float dt)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(dt);
	}
}

void dae::SceneManager::FixedUpdate(float dt)
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate(dt);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::DestroyObjects()
{
	for (const auto& scene : m_Scenes)
	{
		scene->DestroyObjects();
	}
}

dae::SceneManager::~SceneManager()
{

}

std::weak_ptr<dae::Scene> dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return scene;
}
