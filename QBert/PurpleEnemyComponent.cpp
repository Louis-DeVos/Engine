#include "PurpleEnemyComponent.h"
#include "GameObject.h"
#include <RenderComponent.h>
#include <ResourceManager.h>

PurpleEnemyComponent::PurpleEnemyComponent(std::weak_ptr<dae::GameObject> pGameObject, int movementDirection)
	:m_pGameObject(pGameObject)
	,m_MovementDirection{movementDirection}
{
}

PurpleEnemyComponent::~PurpleEnemyComponent()
{
}

void PurpleEnemyComponent::Update(float dt)
{
	m_DelayTimer += dt;
	if (m_DelayTimer >= m_MoveDelay)
	{
		if (rand() % 2 == 0)
		{
			if (m_MovementDirection > 0)
			{
				Move(Position::TopRight);
			}
			else
			{
				Move(Position::TopLeft);
			}
		}
		else
		{
			MoveSideways();
		}
		m_DelayTimer = 0;
	}
}

void PurpleEnemyComponent::FixedUpdate(float)
{
}

void PurpleEnemyComponent::Render(const glm::vec3&) const
{
}

void PurpleEnemyComponent::SetLocation(std::weak_ptr<GridNodeComponent> gridLocation)
{
	m_pGridLocation = gridLocation;
	m_pGameObject.lock()->SetPosition(m_pGridLocation.lock()->GetWorldPosition().x + 12 - 12*m_MovementDirection, m_pGridLocation.lock()->GetWorldPosition().y + 16);
}

void PurpleEnemyComponent::Move(Position pos)
{
	std::weak_ptr<GridNodeComponent> node = m_pGridLocation.lock()->GetConnection(pos);

	if (!node.expired())
	{
		SetLocation(node);
	}

}

void PurpleEnemyComponent::MoveSideways()
{
	std::weak_ptr<GridNodeComponent> node{};

	if (m_MovementDirection > 0)
	{
		node = m_pGridLocation.lock()->GetConnection(Position::TopRight);
		if (!node.expired())
		{
			 node = node.lock()->GetConnection(Position::BottomRight);
		}
		else
		{
			return;
		}
			 
	}
	else
	{
		node = m_pGridLocation.lock()->GetConnection(Position::TopLeft);
		if (!node.expired())
		{
			node = node.lock()->GetConnection(Position::BottomLeft);
		}
		else
		{
			return;
		}
	}


	if (!node.expired())
	{
		SetLocation(node);
	}

}
