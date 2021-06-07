#pragma once
#include <BaseComponent.h>
#include <memory>
#include "GridNodeComponent.h"

namespace dae
{
    class GameObject;
}
class QBertComponent;

class CoilyComponent final :
    public BaseComponent
{
public:
    CoilyComponent(std::weak_ptr<dae::GameObject> pGameObject);

    void Update(float dt) override;
    void FixedUpdate(float dt) override;
    void Render(const glm::vec3& transform) const override;
    std::weak_ptr<dae::GameObject> GetOwner() const override { return m_pGameObject; }

    void Die() const;

    CoilyComponent(const CoilyComponent& other) = delete;
    CoilyComponent(CoilyComponent&& other) = delete;
    CoilyComponent& operator=(const CoilyComponent& other) = delete;
    CoilyComponent& operator=(CoilyComponent&& other) = delete;

    void SetLocation(std::weak_ptr<GridNodeComponent> gridLocation);

    void SetTarget(std::weak_ptr<dae::GameObject> target) { m_pTarget = target; }

    void Move(Direction pos);
    void EggMove(Direction pos);

    bool CheckCollision(std::weak_ptr<QBertComponent> qbert) const;

    void SetControlledByPlayer(bool controlledByPlayer) { m_ControlledByPlayer = controlledByPlayer; }

private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    std::weak_ptr<dae::GameObject> m_pTarget{std::shared_ptr<dae::GameObject>(nullptr)};
    std::weak_ptr<GridNodeComponent> m_pGridLocation{ std::shared_ptr<GridNodeComponent>(nullptr) };
    bool m_Hatched{false};
    float m_DelayTimer{0.f};
    const float m_MoveDelay{ 1.f };
    bool m_ControlledByPlayer{ false };
};

