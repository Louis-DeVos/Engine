#pragma once
#include <BaseComponent.h>
#include <memory>
#include "GraphComponent.h"

namespace dae
{
    class GameObject;
}

class GreenEnemyComponent final :
    public BaseComponent
{
public:
    GreenEnemyComponent(std::weak_ptr<dae::GameObject> pGameObject);
    ~GreenEnemyComponent();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(const glm::vec3& transform) const;

    void Die();

    GreenEnemyComponent(const GreenEnemyComponent& other) = delete;
    GreenEnemyComponent(GreenEnemyComponent&& other) = delete;
    GreenEnemyComponent& operator=(const GreenEnemyComponent& other) = delete;
    GreenEnemyComponent& operator=(GreenEnemyComponent&& other) = delete;

    void SetLocation(std::weak_ptr<GridNodeComponent> gridLocation);

    void SetTarget(std::weak_ptr<dae::GameObject> target) { m_pTarget = target; }

    void Move(Position pos);

private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    std::weak_ptr<dae::GameObject> m_pTarget{ std::shared_ptr<dae::GameObject>(nullptr) };
    std::weak_ptr<GridNodeComponent> m_pGridLocation{ std::shared_ptr<GridNodeComponent>(nullptr) };
    float m_DelayTimer{ 0.f };
    const float m_MoveDelay{ 0.5f };
};

