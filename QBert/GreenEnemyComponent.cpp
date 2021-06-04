#include "GreenEnemyComponent.h"
#include "GameObject.h"
#include <RenderComponent.h>
#include <ResourceManager.h>

GreenEnemyComponent::GreenEnemyComponent(std::weak_ptr<dae::GameObject> pGameObject)
	:m_pGameObject(pGameObject)
{
}

GreenEnemyComponent::~GreenEnemyComponent()
{
}

void GreenEnemyComponent::Update(float dt)
{
	m_DelayTimer += dt;
	if (m_DelayTimer >= m_MoveDelay)
	{
		if (rand() % 2 == 0)
		{
			Move(Position::BottomLeft);
		}
		else
		{
			Move(Position::BottomRight);
		}
		m_DelayTimer = 0;
	}
}

void GreenEnemyComponent::FixedUpdate(float)
{
}

void GreenEnemyComponent::Render(const glm::vec3&) const
{
}

void GreenEnemyComponent::SetLocation(std::weak_ptr<GridNodeComponent> gridLocation)
{
	m_pGridLocation = gridLocation;
	m_pGameObject.lock()->SetPosition(m_pGridLocation.lock()->GetWorldPosition().x + 8, m_pGridLocation.lock()->GetWorldPosition().y - 8);
}

void GreenEnemyComponent::Move(Position pos)
{
	std::weak_ptr<GridNodeComponent> node = m_pGridLocation.lock()->GetConnection(pos);

	if (!node.expired())
	{
		SetLocation(node);
		node.lock()->ChangeState(-1);
	}

}
