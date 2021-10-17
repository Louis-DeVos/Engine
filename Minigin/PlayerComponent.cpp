#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "SubjectComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"

PlayerComponent::PlayerComponent(std::weak_ptr<GameObject> pGameObject)
	:m_pGameObject(pGameObject)
	, m_Lives{3}
{
}

PlayerComponent::~PlayerComponent()
= default;

void PlayerComponent::Update(float)
{
}

void PlayerComponent::FixedUpdate(float)
{
}

void PlayerComponent::Render(const glm::vec3&) const
{
}

void PlayerComponent::GainScore(int score) const
{
	m_pGameObject.lock()->getComponent<SubjectComponent>().lock()->Notify(Event::ChangeScoreEvent,score);
}

void PlayerComponent::Die()
{
	ServiceLocator::GetSoundSystem()->Play(1,false);


	--m_Lives;
	m_pGameObject.lock()->getComponent<SubjectComponent>().lock()->Notify(Event::KillEvent);
	if (m_Lives==0)
	{
		m_pGameObject.lock()->SetToBeDestroyed();
	}
}

int PlayerComponent::GetLives() const
{
	return m_Lives;
}
