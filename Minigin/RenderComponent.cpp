#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"

RenderComponent::RenderComponent(std::weak_ptr<dae::GameObject> pGameObject)
	:m_pTexture{nullptr}
	, m_pGameObject{ pGameObject }
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::Update(float)
{
}

void RenderComponent::FixedUpdate(float)
{

}

void RenderComponent::Render(const glm::vec3& transform)const
{
	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, transform.x, transform.y);
}

void RenderComponent::SetTexture(std::shared_ptr<dae::Texture2D> pTexture)
{
	m_pTexture = pTexture;
}
