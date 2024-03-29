#include "PurpleEnemyComponent.h"
#include "GameObject.h"
#include <RenderComponent.h>
#include <ResourceManager.h>
#include "QBertComponent.h"

PurpleEnemyComponent::PurpleEnemyComponent(std::weak_ptr<GameObject> pGameObject, int movementDirection)
	:m_pGameObject(pGameObject)
	,m_MovementDirection{movementDirection}
{
}

PurpleEnemyComponent::~PurpleEnemyComponent()
= default;

void PurpleEnemyComponent::Update(float dt)
{
	m_DelayTimer += dt;
	if (m_DelayTimer >= m_MoveDelay)
	{
		if (rand() % 2 == 0)
		{
			if (m_MovementDirection > 0)
			{
				Move(Direction::TopRight);
			}
			else
			{
				Move(Direction::TopLeft);
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

void PurpleEnemyComponent::Die() const
{
	m_pGameObject.lock()->SetToBeDestroyed();
}

void PurpleEnemyComponent::SetLocation(std::weak_ptr<GridNodeComponent> gridLocation)
{
	m_pGridLocation = gridLocation;
	m_pGameObject.lock()->SetPosition(m_pGridLocation.lock()->GetWorldPosition().x + 12 - 12*m_MovementDirection, m_pGridLocation.lock()->GetWorldPosition().y + 16);
}

void PurpleEnemyComponent::Move(Direction pos)
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

void PurpleEnemyComponent::MoveSideways()
{
	std::weak_ptr<GridNodeComponent> node{};

	if (m_MovementDirection > 0)
	{
		node = m_pGridLocation.lock()->GetConnection(Direction::TopRight);
		if (!node.expired())
		{
			node = node.lock()->GetConnection(Direction::BottomRight);
		}
		else
		{
			Die();
			return;
		}

	}
	else
	{
		node = m_pGridLocation.lock()->GetConnection(Direction::TopLeft);
		if (!node.expired())
		{
			node = node.lock()->GetConnection(Direction::BottomLeft);
		}
		else
		{
			Die();
			return;
		}
	}


	if (!node.expired())
	{
		SetLocation(node);
	}
	else
	{
		Die();
	}
}

bool PurpleEnemyComponent::CheckCollision(std::weak_ptr<QBertComponent> qbert) const
{
	if (!qbert.expired() && !m_pGameObject.expired())
	{
		if (m_MovementDirection > 0 && !m_pGridLocation.expired() && !m_pGridLocation.lock()->GetConnection(Direction::BottomLeft).expired())
		{
			return(m_pGridLocation.lock()->GetConnection(Direction::BottomLeft).lock() == qbert.lock()->GetGridLocation().lock());
		}
		else if (m_MovementDirection < 0 && !m_pGridLocation.lock()->GetConnection(Direction::BottomRight).expired())
		{
			return(m_pGridLocation.lock()->GetConnection(Direction::BottomRight).lock() == qbert.lock()->GetGridLocation().lock());
		}
	}
	return false;
}
