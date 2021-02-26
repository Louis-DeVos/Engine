#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "SubjectComponent.h"
#include "GameObject.h"

PlayerComponent::PlayerComponent(std::weak_ptr<dae::GameObject> pGameObject)
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

void PlayerComponent::GainScore(int score)
{
	m_pGameObject.lock()->getComponent<SubjectComponent>().lock()->Notify(Event::ChangeScoreEvent,score);
}

void PlayerComponent::Die()
{
	--m_Lives;
	m_pGameObject.lock()->getComponent<SubjectComponent>().lock()->Notify(Event::KillEvent);
	if (m_Lives==0)
	{
		m_pGameObject.lock()->SetToBeDestroyed();
	}
}

int PlayerComponent::GetLives()
{
	return m_Lives;
}
