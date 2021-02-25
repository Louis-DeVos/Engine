#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

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

dae::SceneManager::~SceneManager()
{
	for (Scene* pScene : m_Scenes)
	{
		delete pScene;
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	Scene* scene = new Scene(name);
	m_Scenes.push_back(scene);
	return *scene;
}
