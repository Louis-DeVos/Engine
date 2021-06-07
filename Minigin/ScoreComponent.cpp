#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include <memory>
#include <mutex>
#include <string>

ScoreComponent::ScoreComponent(std::weak_ptr<dae::GameObject> pGameObject)
	:m_pGameObject{pGameObject}
	, m_Score{0}
{
}

ScoreComponent::~ScoreComponent()
{
}

void ScoreComponent::Update(float)
{
	if (m_NeedsUpdate)
	{
		if (m_pTextComponent.expired())
		{
			m_pTextComponent = m_pGameObject.lock()->getComponent<dae::TextComponent>();
		}


		if (!m_pTextComponent.expired())
		{
			m_pTextComponent.lock()->SetText("Score " + std::to_string(m_Score));
			m_NeedsUpdate = false;
		}

	}
}

void ScoreComponent::FixedUpdate(float )
{
}

void ScoreComponent::Render(const glm::vec3&) const
{
}

void ScoreComponent::AddScore(int score)
{
	m_Score += score;
	m_NeedsUpdate = true;
}
