#include "CoilyComponent.h"
#include "GameObject.h"
#include <RenderComponent.h>
#include <ResourceManager.h>
#include "QBertComponent.h"

CoilyComponent::CoilyComponent(std::weak_ptr<GameObject> pGameObject)
	:m_pGameObject(pGameObject)
{
}


void CoilyComponent::Update(float dt)
{
	m_DelayTimer += dt;


	if (m_Hatched && !m_pTarget.expired() && !m_ControlledByPlayer)
	{
		glm::vec3 pos = m_pGameObject.lock()->GetTransform().GetPosition();
		glm::vec3 targetPos = m_pTarget.lock()->GetTransform().GetPosition();


		if (pos.x > targetPos.x)
		{
			if (pos.y < targetPos.y)
			{
				Move(Direction::BottomLeft);
			}
			else
			{
				Move(Direction::TopLeft);
			}
		}
		else
		{
			if (pos.y < targetPos.y)
			{
				Move(Direction::BottomRight);
			}
			else
			{
				Move(Direction::TopRight);
			}
		}


	}
	else if (!m_Hatched)
	{
		if (rand() % 2 == 0)
		{
			EggMove(Direction::BottomLeft);
		}
		else
		{
			EggMove(Direction::BottomRight);
		}
	}
	
	
}

void CoilyComponent::FixedUpdate(float )
{
}

void CoilyComponent::Render(const glm::vec3& ) const
{
}

void CoilyComponent::Die() const
{
	m_pGameObject.lock()->SetToBeDestroyed();
}

void CoilyComponent::SetLocation(std::weak_ptr<GridNodeComponent> gridLocation)
{
	m_pGridLocation = gridLocation;
	m_pGameObject.lock()->SetPosition(m_pGridLocation.lock()->GetWorldPosition().x + 8, m_pGridLocation.lock()->GetWorldPosition().y - 8);
}

void CoilyComponent::Move(Direction pos)
{
	if (m_DelayTimer >= m_MoveDelay)
	{
		if (m_Hatched)
		{
			std::weak_ptr<GridNodeComponent> node = m_pGridLocation.lock()->GetConnection(pos);
			if (!node.expired())
			{
				SetLocation(node);
			}
			else
			{
				Die();
			}
		}
		m_DelayTimer = 0;
	}
}

void CoilyComponent::EggMove(Direction pos)
{
	if (m_DelayTimer >= m_MoveDelay)
	{
		std::weak_ptr<GridNodeComponent> node = m_pGridLocation.lock()->GetConnection(pos);
		if (!node.expired())
		{
			SetLocation(node);
		}
		else if (!m_Hatched)
		{
			m_Hatched = true;
			m_pGameObject.lock()->getComponent<RenderComponent>().lock()->SetTexture(ResourceManager::GetInstance().LoadTexture("Coily.png"));
		}
		m_DelayTimer = 0;
	}
}

bool CoilyComponent::CheckCollision(std::weak_ptr<QBertComponent> qbert) const
{
	if (!qbert.expired() && !m_pGridLocation.expired())
	{
		return (m_pGridLocation.lock() == qbert.lock()->GetGridLocation().lock());
	}
	else
	{
		return false;
	}
}
