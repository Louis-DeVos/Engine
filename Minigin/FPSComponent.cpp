#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include <memory>
#include <string>

FPSComponent::FPSComponent(std::weak_ptr<GameObject> pGameObject)
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
			
		
		if (m_pTextComponent.expired())
		{
			m_pTextComponent = m_pGameObject.lock()->getComponent<TextComponent>();
		}

		if (!m_pTextComponent.expired())
		{
			m_pTextComponent.lock()->SetText(std::to_string(m_FPS) + " FPS");
		}
	}
}

void FPSComponent::FixedUpdate(float)
{
}

void FPSComponent::Render(const glm::vec3&) const
{

}
