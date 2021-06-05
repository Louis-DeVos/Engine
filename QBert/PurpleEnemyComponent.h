#pragma once
#include <BaseComponent.h>
#include <memory>
#include "GraphComponent.h"

namespace dae
{
    class GameObject;
}
class QBertComponent;

class PurpleEnemyComponent final :
    public BaseComponent
{
public:
    PurpleEnemyComponent(std::weak_ptr<dae::GameObject> pGameObject, int movementDirection);
    ~PurpleEnemyComponent();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(const glm::vec3& transform) const;

    void Die();

    PurpleEnemyComponent(const PurpleEnemyComponent& other) = delete;
    PurpleEnemyComponent(PurpleEnemyComponent&& other) = delete;
    PurpleEnemyComponent& operator=(const PurpleEnemyComponent& other) = delete;
    PurpleEnemyComponent& operator=(PurpleEnemyComponent&& other) = delete;

    void SetLocation(std::weak_ptr<GridNodeComponent> gridLocation);

    void SetTarget(std::weak_ptr<dae::GameObject> target) { m_pTarget = target; }

    void Move(Position pos);
    void MoveSideways();
    bool CheckCollision(std::weak_ptr<QBertComponent> qbert);

private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    std::weak_ptr<dae::GameObject> m_pTarget{ std::shared_ptr<dae::GameObject>(nullptr) };
    std::weak_ptr<GridNodeComponent> m_pGridLocation{ std::shared_ptr<GridNodeComponent>(nullptr) };
    float m_DelayTimer{ 0.f };
    const float m_MoveDelay{ 0.5f };
    int m_MovementDirection{ 0 };
};

