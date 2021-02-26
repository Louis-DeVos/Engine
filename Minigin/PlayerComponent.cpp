#include "MiniginPCH.h"
#include "PlayerComponent.h"

PlayerComponent::PlayerComponent(dae::GameObject* pGameObject)
	:m_pGameObject(pGameObject)
	, m_Lives{3}
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Update(float)
{
}

void PlayerComponent::FixedUpdate(float)
{
}

void PlayerComponent::Render(const glm::vec3&) const
{
}
