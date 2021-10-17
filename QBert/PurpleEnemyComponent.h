#pragma once
#include <BaseComponent.h>
#include <memory>
#include "GridNodeComponent.h"

class GameObject;
class QBertComponent;

class PurpleEnemyComponent final :
    public BaseComponent
{
public:
    PurpleEnemyComponent(std::weak_ptr<GameObject> pGameObject, int movementDirection);
    ~PurpleEnemyComponent() override;

    void Update(float dt) override;
    void FixedUpdate(float dt) override;
    void Render(const glm::vec3& transform) const override;
    std::weak_ptr<GameObject> GetOwner() const override { return m_pGameObject; }

    void Die() const;

    PurpleEnemyComponent(const PurpleEnemyComponent& other) = delete;
    PurpleEnemyComponent(PurpleEnemyComponent&& other) = delete;
    PurpleEnemyComponent& operator=(const PurpleEnemyComponent& other) = delete;
    PurpleEnemyComponent& operator=(PurpleEnemyComponent&& other) = delete;

    void SetLocation(std::weak_ptr<GridNodeComponent> gridLocation);

    void SetTarget(std::weak_ptr<GameObject> target) { m_pTarget = target; }

    void Move(Direction pos);
    void MoveSideways();
    bool CheckCollision(std::weak_ptr<QBertComponent> qbert) const;

private:
    std::weak_ptr<GameObject> m_pGameObject;
    std::weak_ptr<GameObject> m_pTarget{ std::shared_ptr<GameObject>(nullptr) };
    std::weak_ptr<GridNodeComponent> m_pGridLocation{ std::shared_ptr<GridNodeComponent>(nullptr) };
    float m_DelayTimer{ 0.f };
    const float m_MoveDelay{ 1.f };
    int m_MovementDirection{ 0 };
};

