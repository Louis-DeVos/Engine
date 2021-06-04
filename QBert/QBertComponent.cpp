#include "MiniginPCH.h"
#include "QBertComponent.h"
#include "SubjectComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"

QBertComponent::QBertComponent(std::weak_ptr<dae::GameObject> pGameObject)
	:m_pGameObject(pGameObject)
	, m_Lives{ 3 }
{
}

QBertComponent::~QBertComponent()
{
}

void QBertComponent::Update(float)
{
}

void QBertComponent::FixedUpdate(float)
{
}

void QBertComponent::Render(const glm::vec3&) const
{
}

void QBertComponent::GainScore(int score)
{
	m_pGameObject.lock()->getComponent<SubjectComponent>().lock()->Notify(Event::ChangeScoreEvent, score);
}

void QBertComponent::Die()
{
	ServiceLocator::GetSoundSystem()->Play(1, false);


	--m_Lives;
	m_pGameObject.lock()->getComponent<SubjectComponent>().lock()->Notify(Event::KillEvent);
	if (m_Lives == 0)
	{
		m_pGameObject.lock()->SetToBeDestroyed();
	}
}

int QBertComponent::GetLives()
{
	return m_Lives;
}

void QBertComponent::SetLocation(std::weak_ptr<GridNodeComponent> gridLocation)
{
	m_pGridLocation = gridLocation;
	m_pGameObject.lock()->SetPosition(m_pGridLocation.lock()->GetWorldPosition().x+8, m_pGridLocation.lock()->GetWorldPosition().y-8);
	m_pGridLocation.lock()->ChangeState(1);
}

void QBertComponent::Move(Position pos)
{
	std::weak_ptr<GridNodeComponent> node = m_pGridLocation.lock()->GetConnection(pos);
	if (!node.expired())
	{
		SetLocation(node);
	}

}
