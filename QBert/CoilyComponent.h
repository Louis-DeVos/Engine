#pragma once
#include <BaseComponent.h>
#include <memory>
#include "GraphComponent.h"

namespace dae
{
    class GameObject;
}

class CoilyComponent final :
    public BaseComponent
{
public:
    CoilyComponent(std::weak_ptr<dae::GameObject> pGameObject);
    ~CoilyComponent();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(const glm::vec3& transform) const;

    void Die();

    CoilyComponent(const CoilyComponent& other) = delete;
    CoilyComponent(CoilyComponent&& other) = delete;
    CoilyComponent& operator=(const CoilyComponent& other) = delete;
    CoilyComponent& operator=(CoilyComponent&& other) = delete;

    void SetLocation(std::weak_ptr<GridNodeComponent> gridLocation);

    void SetTarget(std::weak_ptr<dae::GameObject> target) { m_pTarget = target; }

    void Move(Position pos);

private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    std::weak_ptr<dae::GameObject> m_pTarget{std::shared_ptr<dae::GameObject>(nullptr)};
    std::weak_ptr<GridNodeComponent> m_pGridLocation{ std::shared_ptr<GridNodeComponent>(nullptr) };
    bool m_Hatched{false};
    float m_DelayTimer{0.f};
    const float m_MoveDelay{ 0.5f };
};

