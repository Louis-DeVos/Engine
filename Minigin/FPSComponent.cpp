#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"

FPSComponent::FPSComponent(dae::GameObject* pGameObject)
	:m_pGameObject{pGameObject}
	, m_FPS{}
{
}

FPSComponent::~FPSComponent()
{
}

void FPSComponent::Update(float dt)
{
	int newFps = int(1 / dt);
	if (newFps != m_FPS)
	{
		m_FPS = newFps;
		dae::TextComponent* pTextComponent = m_pGameObject->getComponent<dae::TextComponent>();
		if (pTextComponent != nullptr)
		{
			pTextComponent->SetText(std::to_string(m_FPS) + " FPS");
		}
	}
}

void FPSComponent::FixedUpdate(float)
{
}

void FPSComponent::Render(const glm::vec3&) const
{

}
