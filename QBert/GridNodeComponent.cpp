#include "MiniginPCH.h"
#include "GridNodeComponent.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"

//GraphComponent::GraphComponent()
//{
//}
//
//GraphComponent::~GraphComponent()
//{
//}

GridNodeComponent::GridNodeComponent(std::weak_ptr<dae::GameObject> pGameObject)
	:m_pGameObject{pGameObject}
	,m_TextureName{"Block_"}
{

}

GridNodeComponent::~GridNodeComponent()
= default;

void GridNodeComponent::Update(float )
{
}

void GridNodeComponent::FixedUpdate(float )
{
}

void GridNodeComponent::Render(const glm::vec3& ) const
{
}

void GridNodeComponent::SetConnection(Direction pos, std::weak_ptr<GridNodeComponent> connection)
{
	switch (pos)
	{
	case Direction::TopLeft:
		m_pTopLeft = connection;
		break;
	case Direction::TopRight:
		m_pTopRight = connection;
		break;
	case Direction::BottomRight:
		m_pBottomRight = connection;
		break;
	case Direction::BottomLeft:
		m_pBottomLeft = connection;
		break;
	default:
		break;
	}

	if (connection.lock()->GetConnection(Direction((int(pos) + 2) % 4 )).expired())
	{
		connection.lock()->SetConnection(Direction((int(pos) + 2) % 4), m_pGameObject.lock()->getComponent<GridNodeComponent>());
	}

}

std::weak_ptr<GridNodeComponent> GridNodeComponent::GetConnection(Direction pos) const
{
	switch (pos)
	{
	case Direction::TopLeft:
		return m_pTopLeft;
		break;
	case Direction::TopRight:
		return m_pTopRight;
		break;
	case Direction::BottomRight:
		return m_pBottomRight;
		break;
	case Direction::BottomLeft:
		return m_pBottomLeft;
		break;
	default:
		break;
	}
	return std::shared_ptr<GridNodeComponent>(nullptr);
}

std::weak_ptr<GridNodeComponent> GridNodeComponent::GetLastConnection(Direction pos) const
{
	if (GetConnection(pos).expired())
	{
		return m_pGameObject.lock()->getComponent<GridNodeComponent>();
	}
	switch (pos)
	{
	case Direction::TopLeft:
		return m_pTopLeft.lock()->GetLastConnection(Direction::TopLeft);
		break;
	case Direction::TopRight:
		return m_pTopRight.lock()->GetLastConnection(Direction::TopRight);
		break;
	case Direction::BottomRight:
		return m_pBottomRight.lock()->GetLastConnection(Direction::BottomRight);
		break;
	case Direction::BottomLeft:
		return m_pBottomLeft.lock()->GetLastConnection(Direction::BottomLeft);
		break;
	default:
		break;
	}
	return std::shared_ptr<GridNodeComponent>(nullptr);
}

glm::vec3 GridNodeComponent::GetWorldPosition() const
{
	return m_pGameObject.lock()->GetTransform().GetPosition();
}

bool GridNodeComponent::ChangeState(int stateChange)
{
	m_State += stateChange;

	bool stateWentUp{ stateChange > 0 };

	if (m_State > m_MaxState)
	{
		if (m_Cycle)
		{
			m_State = m_MaxState-1;
		}
		else
		{
			m_State = m_MaxState;
		}
		stateWentUp = false;
	}
	if (m_State < 0)
	{
		m_State = 0;
	}
	m_pGameObject.lock()->getComponent<RenderComponent>().lock()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture(m_TextureName + std::to_string(m_State)+".png"));
	return stateWentUp;
}

std::weak_ptr<DiskComponent> GridNodeComponent::GetDisk(Direction direction) const
{
	switch (direction)
	{
	case Direction::TopLeft:
		return m_DiskPair.first;
		break;
	case Direction::TopRight:
		return m_DiskPair.second;
		break;
	default:
		return std::shared_ptr<DiskComponent>(nullptr);
		break;
	}
}
