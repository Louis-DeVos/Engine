#include "MiniginPCH.h"
#include "LifeComponent.h"

LifeComponent::LifeComponent(dae::GameObject* pGameObject)
	: m_pGameObject(pGameObject)
	, m_Lives{3}
{
}

LifeComponent::~LifeComponent()
{
}

void LifeComponent::Update(float)
{
}

void LifeComponent::FixedUpdate(float)
{
}

void LifeComponent::Render(const glm::vec3&) const
{
}
