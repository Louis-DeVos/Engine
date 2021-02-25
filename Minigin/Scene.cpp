#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	for (SceneObject* pObject : m_Objects)
	{
		delete pObject;
	}
}

void Scene::Add(SceneObject* object)
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
