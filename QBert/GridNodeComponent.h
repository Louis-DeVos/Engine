#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
}
class DiskComponent;


enum class Direction
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
	~GridNodeComponent() override;

	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Render(const glm::vec3& transform) const override;
	std::weak_ptr<dae::GameObject> GetOwner() const override { return m_pGameObject; }

	void SetConnection(Direction pos, std::weak_ptr<GridNodeComponent> connection);
	std::weak_ptr<GridNodeComponent> GetConnection(Direction pos) const;
	std::weak_ptr<GridNodeComponent> GetLastConnection(Direction pos) const;
	glm::vec3 GetWorldPosition() const;
	bool ChangeState(int stateChange);

	void SetMaxState(int maxState) { m_MaxState = maxState; }
	void SetCycle(bool cycle) { m_Cycle = cycle; }

	bool OnLastState() const { return m_State == m_MaxState; };


	void SetLeftDisk(std::weak_ptr<DiskComponent> disk) { m_DiskPair.first = disk; }
	void SetRightDisk(std::weak_ptr<DiskComponent> disk) { m_DiskPair.second = disk; }

	std::weak_ptr<DiskComponent> GetDisk(Direction direction) const;

	GridNodeComponent(const GridNodeComponent& other) = delete;
	GridNodeComponent(GridNodeComponent&& other) = delete;
	GridNodeComponent& operator=(const GridNodeComponent& other) = delete;
	GridNodeComponent& operator=(GridNodeComponent&& other) = delete;
	

private:
	std::string m_TextureName;
	std::weak_ptr<dae::GameObject> m_pGameObject;
	std::weak_ptr<GridNodeComponent> m_pTopLeft{ std::shared_ptr<GridNodeComponent>(nullptr) };
	std::weak_ptr<GridNodeComponent> m_pTopRight{ std::shared_ptr<GridNodeComponent>(nullptr) };
	std::weak_ptr<GridNodeComponent> m_pBottomRight{ std::shared_ptr<GridNodeComponent>(nullptr) };
	std::weak_ptr<GridNodeComponent> m_pBottomLeft{ std::shared_ptr<GridNodeComponent>(nullptr) };
	std::pair<std::weak_ptr<DiskComponent>, std::weak_ptr<DiskComponent>> m_DiskPair{ std::make_pair<std::weak_ptr<DiskComponent>, std::weak_ptr<DiskComponent>>(std::shared_ptr<DiskComponent>(nullptr),std::shared_ptr<DiskComponent>(nullptr)) };
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




