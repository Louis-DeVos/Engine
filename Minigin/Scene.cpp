#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <Algorithm>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{

}

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float dt)
{
	for(auto& object : m_Objects)
	{
		object->Update(dt);
	}
}

void dae::Scene::FixedUpdate(float dt)
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate(dt);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void dae::Scene::DestroyObjects()
{
	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [](std::shared_ptr<GameObject> pObject) {return pObject->ToBeDestroyed(); }),m_Objects.end());
}

