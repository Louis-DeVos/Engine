#include "MiniginPCH.h"
#include "SubjectComponent.h"
#include <memory>
#include <string>

SubjectComponent::SubjectComponent(std::weak_ptr<dae::GameObject> pGameObject)
	:m_pGameObject(pGameObject)
{
}

SubjectComponent::~SubjectComponent()
= default;

void SubjectComponent::Update(float)
{
}

void SubjectComponent::FixedUpdate(float)
{
}

void SubjectComponent::Render(const glm::vec3&) const
{
}

void SubjectComponent::Notify(Event event) const
{
	for (std::shared_ptr<Observer> observer : m_ObserverVector)
	{
		observer->OnNotify(m_pGameObject, event);
	}
}

void SubjectComponent::Notify(Event event, int num) const
{
	for (std::shared_ptr<Observer> observer : m_ObserverVector)
	{
		observer->OnNotify(m_pGameObject, event, num);
	}
}

void SubjectComponent::Notify(Event event, const std::string& str) const
{
	for (std::shared_ptr<Observer> observer : m_ObserverVector)
	{
		observer->OnNotify(m_pGameObject, event, str);
	}
}

void SubjectComponent::AddObserver(std::shared_ptr<Observer> observer)
{
	m_ObserverVector.push_back(observer);
}
