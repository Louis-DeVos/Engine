#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <memory>

GameObject::GameObject(std::weak_ptr<Scene> pScene)
	:m_pScene{pScene}
{
}

GameObject::~GameObject()
{

}

void GameObject::Update(float dt)
{
	for (std::shared_ptr<BaseComponent> component: m_ComponentList)
	{
		component->Update(dt);
	}
}

void GameObject::FixedUpdate(float dt)
{
	for (std::shared_ptr<BaseComponent> component : m_ComponentList)
	{
		component->FixedUpdate(dt);
	}
}

void GameObject::Render() const
{
	const auto pos = m_Transform.GetPosition();
	for (const std::shared_ptr<BaseComponent>& component : m_ComponentList)
	{
		component->Render(pos);
	}
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

//void GameObject::SetTexture(const std::string& filename)
//{
//	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

bool GameObject::ToBeDestroyed() const
{
	return m_ToBeDestroyed;
}

void GameObject::SetToBeDestroyed()
{
	m_ToBeDestroyed = true;
}
