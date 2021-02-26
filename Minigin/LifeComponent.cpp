#include "MiniginPCH.h"
#include "LifeComponent.h"
#include "TextComponent.h"
#include "GameObject.h"

LifeComponent::LifeComponent(std::weak_ptr<dae::GameObject> pGameObject)
	: m_pGameObject(pGameObject)
	, m_Lives{3}
{
}

LifeComponent::~LifeComponent()
{
}

void LifeComponent::Update(float)
{
	if (m_NeedsUpdate)
	{
		std::weak_ptr<dae::TextComponent> pTextComponent = m_pGameObject.lock()->getComponent<dae::TextComponent>();
		if (!pTextComponent.expired())
		{
			pTextComponent.lock()->SetText(std::to_string(m_Lives) + " lives");
			m_NeedsUpdate = false;
		}
	}
}

void LifeComponent::FixedUpdate(float)
{
}

void LifeComponent::Render(const glm::vec3&) const
{
}

void LifeComponent::SetLives(int lives)
{
	m_Lives = lives;
	m_NeedsUpdate = true;
}
