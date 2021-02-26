#include "MiniginPCH.h"
#include "SubjectComponent.h"

SubjectComponent::SubjectComponent(dae::GameObject* pGameObject)
	:m_pGameObject(pGameObject)
{
}

SubjectComponent::~SubjectComponent()
{
}

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
	for (Observer* observer : m_ObserverVector)
	{
		observer->OnNotify(m_pGameObject, event);
	}
}

void SubjectComponent::AddObserver(Observer* observer)
{
	m_ObserverVector.push_back(observer);
}

void SubjectComponent::RemoveObserver(Observer*)
{
}
