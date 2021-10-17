#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <memory>

void SceneManager::Update(float dt)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(dt);
	}
}

void SceneManager::FixedUpdate(float dt)
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate(dt);
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

void SceneManager::DestroyObjects()
{
	for (const auto& scene : m_Scenes)
	{
		scene->DestroyObjects();
	}
}

SceneManager::~SceneManager()
{

}

std::weak_ptr<Scene> SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return scene;
}
