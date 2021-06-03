#include "MiniginPCH.h"
#include "GraphComponent.h"
#include "GameObject.h"

//GraphComponent::GraphComponent()
//{
//}
//
//GraphComponent::~GraphComponent()
//{
//}

GridNodeComponent::GridNodeComponent(std::weak_ptr<dae::GameObject> pGameObject)
	:m_pGameObject{pGameObject}
{

}

GridNodeComponent::~GridNodeComponent()
{
}

void GridNodeComponent::Update(float )
{
}

void GridNodeComponent::FixedUpdate(float )
{
}

void GridNodeComponent::Render(const glm::vec3& ) const
{
}

void GridNodeComponent::SetConnection(Position pos, std::weak_ptr<GridNodeComponent> connection)
{
	switch (pos)
	{
	case Position::TopLeft:
		m_pTopLeft = connection;
		break;
	case Position::TopRight:
		m_pTopRight = connection;
		break;
	case Position::BottomRight:
		m_pBottomRight = connection;
		break;
	case Position::BottomLeft:
		m_pBottomLeft = connection;
		break;
	default:
		break;
	}

	if (connection.lock()->GetConnection(Position(int(pos) + 2 % 4 )).expired())
	{
		connection.lock()->SetConnection(Position(int(pos) + 2 % 4), m_pGameObject.lock()->getComponent<GridNodeComponent>());
	}

}

std::weak_ptr<GridNodeComponent> GridNodeComponent::GetConnection(Position pos)
{
	switch (pos)
	{
	case Position::TopLeft:
		return m_pTopLeft;
		break;
	case Position::TopRight:
		return m_pTopRight;
		break;
	case Position::BottomRight:
		return m_pBottomRight;
		break;
	case Position::BottomLeft:
		return m_pBottomLeft;
		break;
	default:
		break;
	}
	return std::shared_ptr<GridNodeComponent>(nullptr);
}

glm::vec3 GridNodeComponent::GetWorldPosition()
{
	return m_pGameObject.lock()->GetTransform().GetPosition();
}
