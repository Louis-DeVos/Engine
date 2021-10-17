#include "MiniginPCH.h"
#include "LifeComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include <string>

LifeComponent::LifeComponent(std::weak_ptr<GameObject> pGameObject)
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
		if (m_pTextComponent.expired())
		{
			m_pTextComponent = m_pGameObject.lock()->getComponent<TextComponent>();
		}


		if (!m_pTextComponent.expired())
		{
			m_pTextComponent.lock()->SetText(std::to_string(m_Lives) + " lives");
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
