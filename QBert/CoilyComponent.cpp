#include "CoilyComponent.h"
#include "GameObject.h"
#include <RenderComponent.h>
#include <ResourceManager.h>

CoilyComponent::CoilyComponent(std::weak_ptr<dae::GameObject> pGameObject)
	:m_pGameObject(pGameObject)
{
}

CoilyComponent::~CoilyComponent()
{
}

void CoilyComponent::Update(float dt)
{
	m_DelayTimer += dt;
	if (m_DelayTimer >= m_MoveDelay)
	{
		if (m_Hatched)
		{
			glm::vec3 pos = m_pGameObject.lock()->GetTransform().GetPosition();
			glm::vec3 targetPos = m_pTarget.lock()->GetTransform().GetPosition();


			if (pos.x > targetPos.x)
			{
				if (pos.y < targetPos.y)
				{
					Move(Position::BottomLeft);
				}
				else
				{
					Move(Position::TopLeft);
				}
			}
			else
			{
				if (pos.y < targetPos.y)
				{
					Move(Position::BottomRight);
				}
				else
				{
					Move(Position::TopRight);
				}
			}


		}
		else
		{
			if (rand() % 2 == 0)
			{
				Move(Position::BottomLeft);
			}
			else
			{
				Move(Position::BottomRight);
			}
		}
		m_DelayTimer = 0;
	}
}

void CoilyComponent::FixedUpdate(float )
{
}

void CoilyComponent::Render(const glm::vec3& ) const
{
}

void CoilyComponent::SetLocation(std::weak_ptr<GridNodeComponent> gridLocation)
{
	m_pGridLocation = gridLocation;
	m_pGameObject.lock()->SetPosition(m_pGridLocation.lock()->GetWorldPosition().x + 8, m_pGridLocation.lock()->GetWorldPosition().y - 8);
}

void CoilyComponent::Move(Position pos)
{
	std::weak_ptr<GridNodeComponent> node = m_pGridLocation.lock()->GetConnection(pos);
	
	if (!node.expired())
	{
		SetLocation(node);
	}
	else if (!m_Hatched)
	{
		m_Hatched = true;
		m_pGameObject.lock()->getComponent<RenderComponent>().lock()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Coily.png"));
	}	
}
