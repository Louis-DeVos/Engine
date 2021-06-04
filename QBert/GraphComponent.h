#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
}


enum class Position
{
	TopLeft,
	TopRight,
	BottomRight,
	BottomLeft
};


class GridNodeComponent final:
	public BaseComponent
{
public:
	GridNodeComponent(std::weak_ptr<dae::GameObject> pGameObject);
	~GridNodeComponent();

	void Update(float dt);
	void FixedUpdate(float dt);
	void Render(const glm::vec3& transform) const;

	void SetConnection(Position pos, std::weak_ptr<GridNodeComponent> connection);
	std::weak_ptr<GridNodeComponent> GetConnection(Position pos);
	std::weak_ptr<GridNodeComponent> GetLastConnection(Position pos);
	glm::vec3 GetWorldPosition();
	void ChangeState(int stateChange);

	void SetMaxState(int maxState) { m_MaxState = maxState; }
	void SetCycle(bool cycle) { m_Cycle = cycle; }

private:
	std::string m_TextureName;
	std::weak_ptr<dae::GameObject> m_pGameObject;
	std::weak_ptr<GridNodeComponent> m_pTopLeft{ std::shared_ptr<GridNodeComponent>(nullptr) };
	std::weak_ptr<GridNodeComponent> m_pTopRight{ std::shared_ptr<GridNodeComponent>(nullptr) };
	std::weak_ptr<GridNodeComponent> m_pBottomRight{ std::shared_ptr<GridNodeComponent>(nullptr) };
	std::weak_ptr<GridNodeComponent> m_pBottomLeft{ std::shared_ptr<GridNodeComponent>(nullptr) };
	int m_State{ 0 };
	int m_MaxState{ 1 };
	bool m_Cycle{ true };
};



//class GraphComponent final :
//	public BaseComponent
//{
//public:
//	GraphComponent();
//	~GraphComponent();
//
//	void AddNode(GridNodeComponent node) { m_Nodes.push_back(node); };
//
//private:
//	std::vector<GridNodeComponent> m_Nodes;
//};




