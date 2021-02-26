#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{

}

void dae::GameObject::Update(float dt)
{
	for (std::shared_ptr<BaseComponent> component: m_ComponentList)
	{
		component->Update(dt);
	}
}

void dae::GameObject::FixedUpdate(float dt)
{
	for (std::shared_ptr<BaseComponent> component : m_ComponentList)
	{
		component->FixedUpdate(dt);
	}
}

void dae::GameObject::Render() const
{
	const auto pos = m_Transform.GetPosition();
	for (std::shared_ptr<BaseComponent> component : m_ComponentList)
	{
		component->Render(pos);
	}
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
//}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

bool dae::GameObject::ToBeDestroyed()
{
	return m_ToBeDestroyed;
}

void dae::GameObject::SetToBeDestroyed()
{
	m_ToBeDestroyed = true;
}
