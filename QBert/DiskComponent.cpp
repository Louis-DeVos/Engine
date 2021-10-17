#include "MiniginPCH.h"
#include "DiskComponent.h"
#include "GameObject.h"

DiskComponent::DiskComponent(std::weak_ptr<GameObject> pGameObject)
	:m_pGameObject{pGameObject}
{

}


void DiskComponent::Update(float )
{

}

void DiskComponent::FixedUpdate(float )
{
}

void DiskComponent::Render(const glm::vec3& ) const
{
}

glm::vec3 DiskComponent::GetWorldPosition() const
{
	return m_pGameObject.lock()->GetTransform().GetPosition();
}
